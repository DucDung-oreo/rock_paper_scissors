#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum Choices { ROCK, PAPER, SCISSORS };

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_rockButton_clicked();
    void on_paperButton_clicked();
    void on_scissorsButton_clicked();
    void on_goButton_clicked();


private:
    Ui::MainWindow *ui;
    Choices player1Choice;
    Choices player2Choice;
    int roundCount = 1;
    int winCount = 0;
    int tieCount = 0;
    int loseCount = 0;
    void display_choice();
    Choices generate_choice();
    QString get_result(Choices p1, Choices p2);
    void display_round();
    void display_result();
};
#endif // MAINWINDOW_H
