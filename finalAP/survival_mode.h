#ifndef SURVIVAL_MODE_H
#define SURVIVAL_MODE_H
#include <QWidget>
#include <QTimer>
#include <string>
using namespace std;
namespace Ui {
    class SurvivalMode;
}
class SurvivalMode : public QWidget
{
    Q_OBJECT
public:
    explicit SurvivalMode(QWidget *parent = nullptr);
    ~SurvivalMode();
private slots:
            void bringStart();
    void bringQuestion();
    void bringTrue();
    void bringFalse(bool flag);
    void bringGameOver();
    void startTimer();
    void stopTimer(int index);
    void stopAllTimers();
    void on_dif_e_clicked();
    void on_dif_m_clicked();
    void on_dif_h_clicked();
    void on_turner_btn_clicked();
    void on_q_ans1_clicked();
    void on_q_ans2_clicked();
    void on_q_ans3_clicked();
    void on_q_ans4_clicked();
    void on_t_wid_clicked();
    void on_f_wid_clicked();
    void processAnswer(const string &answer);
private:
    Ui::SurvivalMode *ui;
    string difficulty;
    QTimer timer[15];
    string crt_ans;
    int counter = 3;
    int score = 0;
};
#endif
