#include "survival_mode.h"
#include "ui_survival_mode.h"
#include <string>
#include <iostream>
#include "quiz2.h"
#include "ctgs.h"
#include "randstr.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <random>
#include <QSoundEffect>
#include <QTimer>
#include <QUrl>
using namespace std;
SurvivalMode::SurvivalMode(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::SurvivalMode),
        score(0),
        counter(3)
{
    ui->setupUi(this);
    ui->stacked->setGeometry(0, 0, this->width(), this->height());
}
void SurvivalMode::bringStart()
{
    RandStr rd;
    QString temp = QString::fromStdString(rd.getStr(0));
    ui->hint_1->setText(temp);
    ui->stacked->setCurrentIndex(1);
}
void SurvivalMode::bringQuestion()
{
    QString temp = QString("Score: %1").arg(score);
    ui->m_score->setText(temp);
    if (counter < 3) ui->heart3->hide();
    if (counter < 2) ui->heart2->hide();
    if (counter < 1) ui->heart1->hide();
    Question question = fetchQuestion(10, difficulty);
    crt_ans = question.correct_answer;
    vector<int> nums = {0, 1, 2, 3};
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(nums.begin(), nums.end(), default_random_engine(seed));
    ui->q_box->setText(QString::fromStdString(question.question));
    ui->q_ans1->setText(QString::fromStdString(question.options[nums[0]]));
    ui->q_ans2->setText(QString::fromStdString(question.options[nums[1]]));
    ui->q_ans3->setText(QString::fromStdString(question.options[nums[2]]));
    ui->q_ans4->setText(QString::fromStdString(question.options[nums[3]]));
    ui->stacked->setCurrentIndex(5);
    startTimer();
}
void SurvivalMode::bringTrue()
{
    score++;
    RandStr rd;
    ui->hint_2->setText(QString::fromStdString(rd.getStr(1)));
    ui->stacked->setCurrentIndex(6);
    playSound("fx/correct.wav");
}
void SurvivalMode::bringFalse(bool flag)
{
    counter--;
    ui->f_disp->setText(flag ? "Time's up!" : "Wrong answer");
    RandStr rd;
    ui->hint_3->setText(QString::fromStdString(rd.getStr(2)));
    ui->stacked->setCurrentIndex(7);
    playSound("fx/wrong.wav");
}
void SurvivalMode::bringGameOver()
{
    ui->go_l2->hide();
    ui->go_score->hide();
    ui->go_dif->hide();
    QString temp1 = QString("Your score: %1").arg(score);
    QString temp2 = QString("Difficulty: %1").arg(QString::fromStdString(difficulty));
    ui->go_score->setText(temp1);
    ui->go_dif->setText(temp2);
    playSound("fx/game_over.wav");
    QTimer::singleShot(1000, this, [this]() { ui->go_l2->show(); });
    QTimer::singleShot(2000, this, [this]() { ui->go_score->show(); });
    QTimer::singleShot(3000, this, [this]() { ui->go_dif->show(); });
    ui->stacked->setCurrentIndex(8);
}
void SurvivalMode::startTimer()
{
    ui->timesh->setValue(0);

    connect(&timer[0], &QTimer::timeout, this, [this]() {
        bringFalse(true);
        stopTimer(0);
    });
    timer[0].start(15000);

    for (int i = 1; i < 15; ++i) {
        connect(&timer[i], &QTimer::timeout, this, [this, i]() {
            ui->timesh->setValue(i);
            stopTimer(i);
        });
        timer[i].start(i * 1000);
    }
}
void SurvivalMode::stopTimer(int index)
{
    timer[index].stop();
}
void SurvivalMode::stopAllTimers()
{
    for (int i = 0; i < 15; ++i) {
        stopTimer(i);
    }
}
void SurvivalMode::playSound(const QString &path)
{
    QSoundEffect *effect = new QSoundEffect();
    effect->setSource(QUrl::fromLocalFile(path));
    effect->play();
}
SurvivalMode::~SurvivalMode()
{
    delete ui;
}
void SurvivalMode::on_dif_e_clicked()
{
    difficulty = ui->dif_e->text().toStdString();
    bringStart();
}
void SurvivalMode::on_dif_m_clicked()
{
    difficulty = ui->dif_m->text().toStdString();
    bringStart();
}
void SurvivalMode::on_dif_h_clicked()
{
    difficulty = ui->dif_h->text().toStdString();
    bringStart();
}
void SurvivalMode::on_turner_btn_clicked()
{
    playSound("fx/wait.wav");
    ui->stacked->setCurrentIndex(2);
    QTimer::singleShot(1000, this, [this]() {
        ui->stacked->setCurrentIndex(3);
        playSound("fx/wait.wav");
    });
    QTimer::singleShot(2000, this, [this]() {
        ui->stacked->setCurrentIndex(4);
        playSound("fx/wait.wav");
    });
    QTimer::singleShot(3000, this, [this]() {
        playSound("fx/start.wav");
        bringQuestion();
    });
}
void SurvivalMode::on_q_ans1_clicked()
{
    processAnswer(ui->q_ans1->text().toStdString());
}
void SurvivalMode::on_q_ans2_clicked()
{
    processAnswer(ui->q_ans2->text().toStdString());
}
void SurvivalMode::on_q_ans3_clicked()
{
    processAnswer(ui->q_ans3->text().toStdString());
}
void SurvivalMode::on_q_ans4_clicked()
{
    processAnswer(ui->q_ans4->text().toStdString());
}
void SurvivalMode::processAnswer(const string &answer)
{
    stopAllTimers();
    if (answer == crt_ans) {
        bringTrue();
    } else {
        bringFalse(false);
    }
}
void SurvivalMode::on_t_wid_clicked()
{
    bringQuestion();
}
void SurvivalMode::on_f_wid_clicked()
{
    if (counter == 0) {
        bringGameOver();
    } else {
        bringQuestion();
    }
}
