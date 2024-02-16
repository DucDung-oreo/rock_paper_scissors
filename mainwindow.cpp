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
    player1Choice = ROCK;
    ui->paperButton->setEnabled(false);
    ui->scissorsButton->setEnabled(false);
    display_round();
}


void MainWindow::on_paperButton_clicked()
{
    player1Choice = PAPER;
    ui->rockButton->setEnabled(false);
    ui->scissorsButton->setEnabled(false);
    display_round();
}


void MainWindow::on_scissorsButton_clicked()
{
    player1Choice = SCISSORS;
    ui->paperButton->setEnabled(false);
    ui->rockButton->setEnabled(false);
    display_round();
}


void MainWindow::on_goButton_clicked()
{
    display_choice();
    player2Choice = generate_choice();
    switch (player2Choice) {
    case ROCK:
        ui->player2Label->setText("ROCK");
        break;
    case PAPER:
        ui->player2Label->setText("PAPER");
        break;
    case SCISSORS:
        ui->player2Label->setText("SCISSORS");
        break;
    }
    ui->resultLabel->setText(get_result(player1Choice, player2Choice));
    qDebug() << "It's " << player1Choice << " vs " << player2Choice;
    ui->paperButton->setEnabled(true);
    ui->rockButton->setEnabled(true);
    ui->scissorsButton->setEnabled(true);
    display_result();
    roundCount++;
}

void MainWindow::display_choice()
{
    switch (player1Choice) {
    case ROCK:
        ui->player1Label->setText("ROCK");
        break;
    case PAPER:
        ui->player1Label->setText("PAPER");
        break;
    case SCISSORS:
        ui->player1Label->setText("SCISSORS");
        break;
    }
}

Choices MainWindow::generate_choice()
{
    return static_cast<Choices>(rand() % 3);
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
