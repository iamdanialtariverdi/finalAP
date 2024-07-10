#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;
class RandStr {
public:
    RandStr() {
        vec = {vec1, vec2, vec3};
        srand(time(nullptr));
    }
    string getStr(int index) {
        if (index < 0 || index >= vec.size()) {
            return "";
        }
        int temp = rand() % vec[index].size();
        return vec[index][temp];
    }
private:
    vector<vector<string>> vec;
    vector<string> vec1 = {
            "Seyed wants to ask you some questions, are you ready?",
            "Don't be afraid of Seyed, he's kind!",
            "Show everyone who you are!"
    };
    vector<string> vec2 = {
            "Awesome",
            "Excellent",
            "Perfect",
            "You did a great job!"
    };
    vector<string> vec3 = {
            "Be careful!",
            "Don't lose your hope",
            "Don't worry you can do that"
    };
};
