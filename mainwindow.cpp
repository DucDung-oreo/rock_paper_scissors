#include "mainwindow.h"
#include "ui_mainwindow.h"

QTimer *timer = new QTimer();

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    player1->initialize(ui);
    player2->initialize(ui);
    ui->goButton->setEnabled(false);
    connect(timer, SIGNAL(timeout()), this, SLOT(display_round_and_result()));
    timer->start(500);
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
    player1->done_chosing(player1, ui->player1Label);
}


void MainWindow::on_paperButton_clicked()
{
    player1->set_choice(PAPER);
    player1->done_chosing(player1, ui->player1Label);
}


void MainWindow::on_scissorsButton_clicked()
{
    player1->set_choice(SCISSORS);
    player1->done_chosing(player1, ui->player1Label);
}


void MainWindow::on_goButton_clicked()
{
    player2->set_choice(player2->generate_choice());
    player2->display_choice(player2->get_choice(), ui->player2Label);

    ui->resultLabel->setText(player1->get_result(player1->get_choice(), player2->get_choice()));

    roundCount++;

    ui->goButton->setEnabled(false);
}

void MainWindow::display_round_and_result()
{
    ui->roundLabel->setText("(☞ﾟヮﾟ)☞ Round " + QString::number(roundCount));
    ui->winLabel->setText("Win: " + QString::number(player1->get_winCount()));
    ui->tieLabel->setText("Tie: " + QString::number(player1->get_tieCount()));
    ui->loseLabel->setText("Lose: " + QString::number(player1->get_loseCount()));
}
