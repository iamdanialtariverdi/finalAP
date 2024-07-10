#include "pvp_mode.h"
#include "ui_pvp_mode.h"
#include "quiz.h"
#include "ctgs.h"
#include "randstr.h"
#include <QTimer>
#include <QSound>
#include <algorithm>
#include <random>
using namespace std;
pvp_mode::pvp_mode(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::pvp_mode),
        is_p1(true),
        p1_score(0),
        p2_score(0),
        p1_score_t(0),
        p2_score_t(0),
        counter_1(0),
        counter_2(0)
{
    ui->setupUi(this);
    srand(time(0));
    ui->stacked->setGeometry(0, 0, this->width(), this->height());
}
pvp_mode::~pvp_mode()
{
    delete ui;
}
void pvp_mode::bring_difficulty()
{
    ui->stacked->setCurrentIndex(2);
}
void pvp_mode::bring_cat()
{
    ui->stacked->setCurrentIndex(3);
    ctgs ct;
    vector<string> temp_c = ct.get_rand(4); // modified ctgs.h to return a vector
    ui->cat_1->setText(QString::fromStdString(temp_c[0]));
    ui->cat_2->setText(QString::fromStdString(temp_c[1]));
    ui->cat_3->setText(QString::fromStdString(temp_c[2]));
    ui->cat_4->setText(QString::fromStdString(temp_c[3]));
}
void pvp_mode::bring_question()
{
    ctgs ct;
    int category_i = ct.get_index(category) + 9;
    Question question = fetchQuestion(10, difficulty, category_i);
    crt_ans = question.correct_answer;
    vector<int> nums = {0, 1, 2, 3};
    shuffle(nums.begin(), nums.end(), mt19937(random_device()()));
    updateScores();
    ui->q_box->setText(QString::fromStdString(question.question));
    ui->q_ans1->setText(QString::fromStdString(question.options[nums[0]]));
    ui->q_ans2->setText(QString::fromStdString(question.options[nums[1]]));
    ui->q_ans3->setText(QString::fromStdString(question.options[nums[2]]));
    ui->q_ans4->setText(QString::fromStdString(question.options[nums[3]]));
    start_timer();
    ui->stacked->setCurrentIndex(8);
}
void pvp_mode::start_timer()
{
    ui->timesh->setValue(0);

    connect(&timer, &QTimer::timeout, this, [this]() {
        bring_false(true);
        timer.stop();
    });

    timer.start(30000);
}
void pvp_mode::stop_timer()
{
    timer.stop();
}
void pvp_mode::bring_countdown()
{
    playSound("fx/wait.wav", 1000);
    QTimer::singleShot(1000, this, [this]() {
        ui->stacked->setCurrentIndex(6);
        playSound("fx/wait.wav", 1000);
    });
    QTimer::singleShot(2000, this, [this]() {
        ui->stacked->setCurrentIndex(7);
        playSound("fx/wait.wav", 1000);
    });
    QTimer::singleShot(3000, this, [this]() {
        playSound("fx/start.wav", 1000);
        bring_question();
    });
}
void pvp_mode::bring_turn()
{
    string temp = (is_p1 ? player_1 : player_2);
    ui->turn->setText(QString::fromStdString("It's " + temp + "'s turn"));
    randstr rd;
    ui->hint_1->setText(QString::fromStdString(rd.getstr(0)));
    ui->stacked->setCurrentIndex(4);
    is_p1 = !is_p1;
}
void pvp_mode::bring_true()
{
    if (is_p1)
        p1_score_t++;
    else
        p2_score_t++;
    counter_2++;
    randstr rd;
    ui->hint_2->setText(QString::fromStdString(rd.getstr(1)));
    ui->stacked->setCurrentIndex(9);
    playSound("fx/correct.wav", 1000);
}
void pvp_mode::bring_false(bool flag)
{
    ui->f_disp->setText(flag ? "Time's up!" : "Wrong answer");
    counter_2++;
    randstr rd;
    ui->hint_3->setText(QString::fromStdString(rd.getstr(2)));
    ui->stacked->setCurrentIndex(10);
    playSound("fx/wrong.wav", 1000);
}
void pvp_mode::bring_r_finished()
{
    string round_num = "Round " + to_string(counter_1) + " finished";
    ui->rf_title->setText(QString::fromStdString(round_num));

    string score_str = to_string(p1_score_t) + " : " + to_string(p2_score_t);
    ui->rf_rscore->setText(QString::fromStdString(score_str));
    string winner_msg;
    if (p1_score_t > p2_score_t) {
        winner_msg = "The winner of this round is " + player_1;
        p1_score++;
    } else if (p1_score_t < p2_score_t) {
        winner_msg = "The winner of this round is " + player_2;
        p2_score++;
    } else {
        winner_msg = "The winner of this round is no one";
    }
    ui->rf_win->setText(QString::fromStdString(winner_msg));
    ui->rf_p1->setText(QString::fromStdString(player_1));
    ui->rf_p2->setText(QString::fromStdString(player_2));
    ui->rf_ms1->display(p1_score);
    ui->rf_ms2->display(p2_score);
    counter_2 = 0;
    p1_score_t = 0;
    p2_score_t = 0;
    ui->stacked->setCurrentIndex(11);
}
void pvp_mode::bring_fpage(bool is_golden)
{
    counter_1++;
    if (is_golden) {
        ui->gdround->show();
    }
    ui->round_counter->setText(QString::fromStdString("Round " + to_string(counter_1)));
    ui->stacked->setCurrentIndex(1);
}
void pvp_mode::bring_winner(string winner_name)
{
    playSound("fx/winning.wav", 1000);
    ui->winner_e->hide();
    ui->winner_b->hide();
    ui->stacked->setCurrentIndex(12);

    QStringList texts = {"winner", "chicken", "dinner", QString::fromStdString(winner_name)};
    QStringList::const_iterator it = texts.constBegin();
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this, &it, &texts, &timer]() {
        if (it != texts.constEnd()) {
            ui->winner_m->setText(*it);
            ++it;
            timer->start(1000);
        } else {
            ui->winner_e->show();
            ui->winner_b->show();
            timer->deleteLater();
        }
    });
    timer->start(1000);
}
void pvp_mode::playSound(const string &soundPath, int duration)
{
    QSound::play(QString::fromStdString(soundPath));
    QTimer::singleShot(duration, this, [this]() {
        QSound::play(QString::fromStdString(soundPath));
    });
}
void pvp_mode::updateScores()
{
    int main_score = is_p1 ? p1_score : p2_score;
    int round_score = is_p1 ? p1_score_t : p2_score_t;

    ui->m_score->setText(QString::fromStdString("Main score: " + to_string(main_score)));
    ui->r_score->setText(QString::fromStdString("Round score: " + to_string(round_score)));
}
void pvp_mode::on_pushButton_clicked()
{
    player_1 = ui->player_1_name->toPlainText().toStdString();
    player_2 = ui->player_2_name->toPlainText().toStdString();
    ui->stacked->setCurrentIndex(1);
    ui->gdround->hide();
}
void pvp_mode::on_round_btn_clicked()
{
    if (counter_1 < 5) {
        bring_difficulty();
    } else {
        difficulty = "medium";
        ctgs ct;
        category = ct.get_rand();
        bring_turn();
    }
}
void pvp_mode::on_dif_e_clicked()
{
    difficulty = ui->dif_e->text().toStdString();
    bring_cat();
}
void pvp_mode::on_dif_m_clicked()
{
    difficulty = ui->dif_m->text().toStdString();
    bring_cat();
}
void pvp_mode::on_dif_h_clicked()
{
    difficulty = ui->dif_h->text().toStdString();
    bring_cat();
}
void pvp_mode::on_cat_1_clicked()
{
    category = ui->cat_1->text().toStdString();
    bring_turn();
}
void pvp_mode::on_cat_2_clicked()
{
    category = ui->cat_2->text().toStdString();
    bring_turn();
}
void pvp_mode::on_cat_3_clicked()
{
    category = ui->cat_3->text().toStdString();
    bring_turn();
}
void pvp_mode::on_cat_4_clicked()
{
    category = ui->cat_4->text().toStdString();
    bring_turn();
}
void pvp_mode::on_turner_btn_clicked()
{
    bring_countdown();
}
void pvp_mode::on_q_ans1_clicked()
{
    stop_timer();
    string temp = ui->q_ans1->text().toStdString();
    if (temp == crt_ans) {
        bring_true();
    } else {
        bring_false(false);
    }
}
void pvp_mode::on_q_ans2_clicked()
{
    stop_timer();
    string temp = ui->q_ans2->text().toStdString();
    if (temp == crt_ans) {
        bring_true();
    } else {
        bring_false(false);
    }
}
void pvp_mode::on_q_ans3_clicked()
{
    stop_timer();
    string temp = ui->q_ans3->text().toStdString();
    if (temp == crt_ans) {
        bring_true();
    } else {
        bring_false(false);
    }
}
void pvp_mode::on_q_ans4_clicked()
{
    stop_timer();
    string temp = ui->q_ans4->text().toStdString();
    if (temp == crt_ans) {
        bring_true();
    } else {
        bring_false(false);
    }
}
void pvp_mode::on_t_wid_clicked()
{
    if (counter_2 < 5) {
        bring_question();
    } else if (is_p1) {
        bring_turn();
    } else {
        bring_r_finished();
    }
}
void pvp_mode::on_f_wid_clicked()
{
    if (counter_2 < 5) {
        bring_question();
    } else if (is_p1) {
        bring_turn();
    } else {
        bring_r_finished();
    }
}
void pvp_mode::on_rf_con_clicked()
{
    if (counter_1 < 4) {
        bring_fpage(false);
    } else if (p1_score > p2_score) {
        bring_winner(player_1);
    } else if (p1_score < p2_score) {
        bring_winner(player_2);
    } else {
        bring_fpage(true);
    }
}
