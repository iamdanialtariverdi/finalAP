#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "CustomPage.h"
MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
{
    CustomPage cp;
    cp.setModal(true);
    cp.exec();
    ui->setupUi(this);
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_play_pvp_clicked()
{
    pvp_mode *pvp = new pvp_mode(this);
    pvp->setAttribute(Qt::WA_DeleteOnClose);
    pvp->show();
}
void MainWindow::on_play_survival_clicked()
{
    survival_mode *survival = new survival_mode(this);
    survival->setAttribute(Qt::WA_DeleteOnClose);
    survival->show();
}
