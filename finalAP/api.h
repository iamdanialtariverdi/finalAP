#ifndef CUSTOM_API_H
#define CUSTOM_API_H
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
using namespace std;
class CustomAPI {
public:
    CustomAPI();
    static nlohmann::json CustomFetchTriviaQuestions(const std::string& category, const string& difficulty, int amount);
private:
    static string CustomHttpGet(const string& url);
    static size_t CustomWriteCallback(void* contents, size_t size, size_t nmemb, string* s);
};
#endif
