#ifndef QUIZ2_H
#define QUIZ2_H
#include <string>
#include <queue>
#include <chrono>
#include <iostream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <algorithm>
#include <random>
using namespace std;
struct Question {
    string question;
    string options[4];
    string correct_answer;
};
static queue<Question> questionQueue;
static chrono::steady_clock::time_point lastFetchTime;
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}
void fetchQuestions(int amount, const string& difficulty) {
    string readBuffer;
    CURL* curl;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        string url = "https://opentdb.com/api.php?amount=" + to_string(amount)
                     + "&difficulty=" + difficulty + "&type=multiple";
        cout << "Fetching URL: " << url << endl;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        long response_code;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
        cout << "Response code: " << response_code << endl;
        curl_easy_cleanup(curl);
        if (res != CURLE_OK) {
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
            return;
        }
        cout << "Response content: " << readBuffer << endl;
    }
    curl_global_cleanup();
    try {
        auto jsonData = nlohmann::json::parse(readBuffer);

        if (jsonData["response_code"] != 0) {
            cerr << "Error: API returned a non-zero response code." << endl;
            return;
        }
        for (const auto& result : jsonData["results"]) {
            Question question;
            if (result.contains("question") && result["question"].is_string()) {
                question.question = result["question"].get<string>();
            } else {
                cerr << "Error: Question field is missing or not a string." << endl;
                continue;
            }
            if (result.contains("correct_answer") && result["correct_answer"].is_string()) {
                question.options[0] = result["correct_answer"].get<string>();
                question.correct_answer = question.options[0];
            } else {
                cerr << "Error: Correct answer field is missing or not a string." << endl;
                continue;
            }
            if (result.contains("incorrect_answers") && result["incorrect_answers"].is_array()) {
                int i = 1;
                for (const auto& incorrect : result["incorrect_answers"]) {
                    if (incorrect.is_string()) {
                        if (i < 4) {
                            question.options[i++] = incorrect.get<string>();
                        } else {
                            cerr << "Error: Too many incorrect answers." << endl;
                            continue;
                        }
                    } else {
                        cerr << "Error: An incorrect answer is not a string." << endl;
                        continue;
                    }
                }
            } else {
                cerr << "Error: Incorrect answers field is missing or not an array." << endl;
                continue;
            }
            shuffle(begin(question.options), begin(question.options) + 4, default_random_engine{});
            questionQueue.push(question);
        }
        lastFetchTime = chrono::steady_clock::now();
    } catch (const nlohmann::json::exception& e) {
        cerr << "JSON parse error: " << e.what() << endl;
    }
}
Question fetchQuestion(int amount, const string& difficulty) {
    if (questionQueue.empty()) {
        auto now = chrono::steady_clock::now();
        auto durationSinceLastFetch = chrono::duration_cast<chrono::seconds>(now - lastFetchTime).count();
        if (durationSinceLastFetch < 5) {
            cerr << "Error: Too soon to fetch new questions. Please wait." << endl;
            return {};
        }
        fetchQuestions(amount, difficulty);
    }
    if (!questionQueue.empty()) {
        Question question = questionQueue.front();
        questionQueue.pop();
        return question;
    } else {
        cerr << "Error: No questions available in the queue." << endl;
        return {};
    }
}
#endif
