#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_rockButton_clicked()
{
    player1->choice = ROCK;
    ui->paperButton->setEnabled(false);
    ui->scissorsButton->setEnabled(false);
    display_round();
}


void MainWindow::on_paperButton_clicked()
{
    player1->choice = PAPER;
    ui->rockButton->setEnabled(false);
    ui->scissorsButton->setEnabled(false);
    display_round();
}


void MainWindow::on_scissorsButton_clicked()
{
    player1->choice = SCISSORS;
    ui->paperButton->setEnabled(false);
    ui->rockButton->setEnabled(false);
    display_round();
}


void MainWindow::on_goButton_clicked()
{
    player1->display_choice(player1->choice);
//    qDebug() << "Done displaying choices!!!";
//    player2->choice = player2->generate_choice();
//    qDebug() << "Done generating choices!!!";
//    switch (player2->choice) {
//    case ROCK:
//        ui->player2Label->setText("ROCK");
//        break;
//    case PAPER:
//        ui->player2Label->setText("PAPER");
//        break;
//    case SCISSORS:
//        ui->player2Label->setText("SCISSORS");
//        break;
//    }
//    ui->resultLabel->setText(get_result(player1->choice, player2->choice));
//    qDebug() << "It's " << player1->choice << " vs " << player2->choice;
//    ui->paperButton->setEnabled(true);
//    ui->rockButton->setEnabled(true);
//    ui->scissorsButton->setEnabled(true);
//    display_result();
//    roundCount++;
}

QString MainWindow::get_result(Choices p1, Choices p2)
{
    if (p1 == p2)
    {
        tieCount++;
        return "IT'S A TIE ಠ_ಠ";
    }
    else if ((p1 - p2 == -1) || (p1 - p2 == 2))
    {
        loseCount++;
        return "YOU LOSE ಥ_ಥ";
    }
    else
        return "YOU WIN (⌐■_■)";
}

void MainWindow::display_round()
{
    ui->roundLabel->setText("(☞ﾟヮﾟ)☞ Round " + QString::number(roundCount));
}

void MainWindow::display_result()
{
    winCount = roundCount - loseCount - tieCount;
    ui->winLabel->setText("Win: " + QString::number(winCount));
    ui->tieLabel->setText("Tie: " + QString::number(tieCount));
    ui->loseLabel->setText("Lose: " + QString::number(loseCount));
}
