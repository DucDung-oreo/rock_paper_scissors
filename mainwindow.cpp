#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    player1->initialize(ui);
    player2->initialize(ui);
    ui->goButton->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete player1;
    delete player2;
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
    player2->set_choice(player2->generate_choice());
    player2->display_choice(player2->get_choice(), ui->player2Label);

    ui->resultLabel->setText(player1->get_result(player1->get_choice(), player2->get_choice()));

    display_result(player1);
    roundCount++;

    ui->goButton->setEnabled(false);
}

void MainWindow::display_round()
{
    ui->roundLabel->setText("(☞ﾟヮﾟ)☞ Round " + QString::number(roundCount));
}

void MainWindow::display_result(Player* player_ptr)
{
    ui->winLabel->setText("Win: " + QString::number(player_ptr->get_winCount()));
    ui->tieLabel->setText("Tie: " + QString::number(player_ptr->get_tieCount()));
    ui->loseLabel->setText("Lose: " + QString::number(player_ptr->get_loseCount()));
}
