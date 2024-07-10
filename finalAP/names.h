#ifndef NAMES_H
#define NAMES_H
#include <QWidget>
QT_BEGIN_NAMESPACE
namespace Ui { class names; }
QT_END_NAMESPACE
class names : public QWidget
{
    Q_OBJECT
public:
    explicit names(QWidget *parent = nullptr);
    ~names();
private slots:
            void on_pushButton_clicked();
private:
    Ui::names *ui;
};
#endif
