#include "starting.h"
#include "ui_starting.h"
Starting::Starting(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::Starting)
{
    ui->setupUi(this);
}
Starting::~Starting()
{
    delete ui;
}
