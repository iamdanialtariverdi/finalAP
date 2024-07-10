#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;
class Categories {
public:
    Categories() {
        srand(time(0));
        for (int i = 0; i < 24; ++i) {
            str_[i] = str[i];
        }
    }
    string getRand() {
        int temp = rand() % 24;
        if (str[temp] == "none") {
            return getRand();
        }
        string temp2 = str[temp];
        str[temp] = "none";
        return temp2;
    }
    int getIndex(string inp) {
        for (int i = 0; i < 24; ++i) {
            if (str_[i] == inp) {
                return i;
            }
        }
        return -1;
    }
private:
    string str_[24];
    string str[24] = {
            "General Knowledge",
            "Entertainment: Books",
            "Entertainment: Music",
            "Entertainment: Musicals & Theatres",
            "Entertainment: Television",
            "Entertainment: Video Games",
            "Entertainment: Board Games",
            "Science & Nature",
            "Science: Computers",
            "Science: Mathematics",
            "Mythology",
            "Sports",
            "Geography",
            "History",
            "Politics",
            "Art",
            "Celebrities",
            "Animals",
            "Vehicles",
            "Entertainment: Comics",
            "Science: Gadgets",
            "Entertainment: Japanese Anime & Manga",
            "Entertainment: Cartoon & Animations",
            "Science: Gadgets"
    };
};
//int main() {
//    Categories categories;
//    cout << "Random category: " << categories.getRand() << endl;
//    cout << "Index of 'Science: Computers': " << categories.getIndex("Science: Computers") << endl;
//    return 0;
//}
