#ifndef QST_H
#define QST_H
#include <string>
using namespace std;
struct Question {
    string question;
    string options[4];
    string correct_answer;
};
#endif
