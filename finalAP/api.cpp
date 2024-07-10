#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
using namespace std;
class CustomAPI {
public:
    static size_t CustomWriteCallback(void* contents, size_t size, size_t nmemb, string* s) {
        size_t newLength = size * nmemb;
        try {
            s->append(static_cast<char*>(contents), newLength);
        } catch (const bad_alloc& e) {
            return 0;
        }
        return newLength;
    }
    static string CustomHttpGet(const string& url) {
        CURL* curl = curl_easy_init();
        string readBuffer;
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CustomWriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            CURLcode res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
            if (res != CURLE_OK) {
                cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
            }
        }
        return readBuffer;
    }
    static nlohmann::json CustomFetchTriviaQuestions(const string& category, const string& difficulty, int amount) {
        string url = "https://opentdb.com/api.php?amount=" + to_string(amount) +
                     "&category=" + category +
                     "&difficulty=" + difficulty +
                     "&type=multiple";
        string response = CustomHttpGet(url);
        nlohmann::json jsonResponse;
        try {
            jsonResponse = nlohmann::json::parse(response);
        } catch (const nlohmann::json::parse_error& e) {
            cerr << "JSON parsing error: " << e.what() << endl;
        }
        return jsonResponse;
    }
};
//int main() {
//    nlohmann::json questions = CustomAPI::CustomFetchTriviaQuestions("18", "medium", 5); // Category: Science: Computers (category id: 18)
//    cout << questions.dump(4) << endl;
//    return 0;
//}
