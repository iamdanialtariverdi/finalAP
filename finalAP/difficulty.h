#ifndef DIFFICULTY_H
#define DIFFICULTY_H
#include <QWidget>
class Ui_difficulty;
class difficulty : public QWidget {
    Q_OBJECT
public:
    explicit difficulty(QWidget *parent = nullptr);
    ~difficulty() override;
private:
    Ui_difficulty *ui = nullptr;

};
#endif
