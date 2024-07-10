#include "custom_page.h"
#include "ui_custom_page.h"
#include <QSoundEffect>
#include <QTimer>
CustomPage::CustomPage(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::CustomPage)
{
    ui->setupUi(this);
    ui->label_2->hide();
    ui->label_3->hide();
    QSoundEffect *start = new QSoundEffect();
    start->setSource(QUrl::fromLocalFile("custom/fx/starting.wav"));
    start->play();
    QTimer::singleShot(2000, this, &CustomPage::showLabel2);
    QTimer::singleShot(4000, this, &CustomPage::showLabel3);
    QTimer::singleShot(8000, this, &CustomPage::close);
}
void CustomPage::showLabel2() {
    ui->label_2->show();
}
void CustomPage::showLabel3() {
    ui->label_3->show();
}
CustomPage::~CustomPage()
{
    delete ui;
}
