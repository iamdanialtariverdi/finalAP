#ifndef STARTING_H
#define STARTING_H
#include <QMainWindow>
namespace Ui {
    class Starting;
}
class Starting : public QMainWindow
{
    Q_OBJECT
public:
    explicit Starting(QWidget *parent = nullptr);
    ~Starting();
private:
    Ui::Starting *ui;
};
#endif
