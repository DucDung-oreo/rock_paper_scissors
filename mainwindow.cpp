#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    player1->intitialize(ui);
    player2->intitialize(ui);
    ui->goButton->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_rockButton_clicked()
{
    player1->set_choice(ROCK);
    display_round();
    player1->done_chosing(player1, ui->player1Label);
}


void MainWindow::on_paperButton_clicked()
{
    player1->set_choice(PAPER);
    display_round();
    player1->done_chosing(player1, ui->player1Label);
}


void MainWindow::on_scissorsButton_clicked()
{
    player1->set_choice(SCISSORS);
    display_round();
    player1->done_chosing(player1, ui->player1Label);
}


void MainWindow::on_goButton_clicked()
{
    player1->display_choice(player1->get_choice(), ui->player1Label);
    player2->set_choice(player2->generate_choice());
    player2->display_choice(player2->get_choice(), ui->player2Label);

    ui->resultLabel->setText(get_result(player1->get_choice(), player2->get_choice()));
    qDebug() << "It's " << player1->get_choice() << " vs " << player2->get_choice();

    display_result();
    roundCount++;

    ui->goButton->setEnabled(false);
}

QString MainWindow::get_result(int p1, int p2)
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
