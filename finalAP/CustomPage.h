#ifndef CUSTOM_PAGE_H
#define CUSTOM_PAGE_H
#include <QDialog>
#include <QSoundEffect>
#include <QTimer>
class CustomPage : public QDialog {
    Q_OBJECT
public:
    explicit CustomPage(QWidget *parent = nullptr);
    ~CustomPage() override;
private slots:
            void showLabel2();
    void showLabel3();
private:
    Ui::CustomPage *ui;
};
#endif
