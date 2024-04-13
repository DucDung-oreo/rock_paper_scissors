#include <QtWidgets>
#include <QtNetwork>

#include "mainwindow.h"
#include "ui_mainwindow.h"

QTimer *timer = new QTimer();

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(1);  // set to introPage
    player1->initialize(ui);
    player2->initialize(ui);
    ui->goButton->setEnabled(false);
    reset_for_new_round("OK let's get going!", "YOU TWIT!");
    connect(timer, SIGNAL(timeout()), this, SLOT(display_round_and_result()));
    timer->start(500);

    ui->ipInput->setValidator(new QIntValidator(1, 65535, this));
    ui->getDataButton->setDefault(true);
    ui->getDataButton->setEnabled(false);
    in.setDevice(tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);

    connect(ui->ipInput, &QLineEdit::textChanged,
            this, &MainWindow::enable_get_fortune_button);
    connect(ui->portInput, &QLineEdit::textChanged,
            this, &MainWindow::enable_get_fortune_button);
    connect(ui->getDataButton, &QAbstractButton::clicked,
            this, &MainWindow::request_new_fortune);
    connect(tcpSocket, &QIODevice::readyRead, this, &MainWindow::read_fortune);
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
    reset_for_new_round("Ready for another round?", "I'm chosing...");
}


void MainWindow::on_paperButton_clicked()
{
    player1->set_choice(PAPER);
    player1->done_chosing(player1, ui->player1Label);
    reset_for_new_round("Ready for another round?", "I'm chosing...");
}


void MainWindow::on_scissorsButton_clicked()
{
    player1->set_choice(SCISSORS);
    player1->done_chosing(player1, ui->player1Label);
    reset_for_new_round("Ready for another round?", "I'm chosing...");
}


void MainWindow::on_goButton_clicked()
{
    player2->set_choice(player2->generate_choice());
    player2->display_choice(player2->get_choice(), ui->player2Label);

    result_for_player1 = player1->get_result(player1->get_choice(), player2->get_choice());
    roundCount++;

    ui->goButton->setEnabled(false);
}

void MainWindow::display_round_and_result()
{
    ui->resultLabel->setText(result_for_player1);
    ui->roundLabel->setText("(☞ﾟヮﾟ)☞ Round " + QString::number(roundCount));
    ui->winLabel->setText("Win: " + QString::number(player1->get_winCount()));
    ui->tieLabel->setText("Tie: " + QString::number(player1->get_tieCount()));
    ui->loseLabel->setText("Lose: " + QString::number(player1->get_loseCount()));
}

void MainWindow::reset_for_new_round(QString round_string, QString computer_string)
{
    result_for_player1 = round_string;
    ui->player2Label->setText(computer_string);
}

void MainWindow::on_goToGameButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0); // move to gamePage
}


void MainWindow::on_getDataButton_clicked()
{

}

void MainWindow::request_new_fortune()
{
    ui->getDataButton->setEnabled(false);
    tcpSocket->abort();
    tcpSocket->connectToHost(ui->ipInput->text(),
                             ui->portInput->text().toInt());
}

void MainWindow::read_fortune()
{
    in.startTransaction();

    QString nextFortune;
    in >> nextFortune;

    if (!in.commitTransaction())
        return;

    if (nextFortune == currentFortune) {
        QTimer::singleShot(0, this, &MainWindow::request_new_fortune);
        return;
    }

    currentFortune = nextFortune;
    ui->fortuneOutput->setText(currentFortune);
    ui->getDataButton->setEnabled(true);
}

void MainWindow::enable_get_fortune_button()
{
    ui->getDataButton->setEnabled(!ui->ipInput->text().isEmpty() &&
                                 !ui->portInput->text().isEmpty());

}

