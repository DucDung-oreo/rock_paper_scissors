#include "mainwindow.h"
#include "ui_mainwindow.h"

QTimer *timer = new QTimer();

MainWindow::MainWindow(QMqttSubscription *sub, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_sub(sub)
{
    ui->setupUi(this);

    m_client = new QMqttClient(this);
    m_client->setHostname(ui->hostInput->text());
    m_client->setPort(static_cast<quint16>(ui->portInput->value()));

    connect(m_client, &QMqttClient::stateChanged, this, &MainWindow::updateLogStateChange);
    connect(m_client, &QMqttClient::disconnected, this, &MainWindow::brokerDisconnected);
    connect(m_client, &QMqttClient::messageReceived, this, [this](const QByteArray &message, const QMqttTopicName &topic) {
        const QString content = QDateTime::currentDateTime().toString()
                                + QLatin1String(" Received Topic: ")
                                + topic.name()
                                + QLatin1String(" Message: ")
                                + message
                                + QLatin1Char('\n');
        ui->logEdit->insertPlainText(content);
        ui->logEditGame->insertPlainText(content);
    });

    connect(m_client, &QMqttClient::pingResponseReceived, this, [this]() {
        const QString content = QDateTime::currentDateTime().toString()
                                + QLatin1String(" PingResponse")
                                + QLatin1Char('\n');
        ui->logEdit->insertPlainText(content);
        ui->logEditGame->insertPlainText(content);
    });

    // connect(m_sub, &QMqttSubscription::messageReceived, this, &MainWindow::updateMessage);

    connect(ui->hostInput, &QLineEdit::textChanged, m_client, &QMqttClient::setHostname);
    connect(ui->portInput, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::setClientPort);
    connect(ui->usernameInput, &QLineEdit::textChanged, m_client, &QMqttClient::setUsername);
    connect(ui->passwordInput, &QLineEdit::textChanged, m_client, &QMqttClient::setPassword);
    updateLogStateChange();

    ui->stackedWidget->setCurrentIndex(1);  // set to introPage
    disable_multiplayer(true);
    player1->initialize(ui);
    player2->initialize(ui);
    ui->goButton->setEnabled(false);
    ui->hostInput->setText("test.mosquitto.org");
    // reset_for_new_round("OK let's get going!", "YOU TWIT!");
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

    qDebug() << "=========  MOVING TO GAMEPAGE NOW ========= \n";
}

void MainWindow::setClientPort(int p)
{
    m_client->setPort(static_cast<quint16>(p));
}

void MainWindow::on_connectButton_clicked()
{
    if (m_client->state() == QMqttClient::Disconnected) {
        ui->hostInput->setEnabled(false);
        ui->portInput->setEnabled(false);
        ui->usernameInput->setEnabled(false);
        ui->passwordInput->setEnabled(false);
        ui->connectButton->setText(tr("Disconnect"));
        m_client->connectToHost();
    } else {
        ui->hostInput->setEnabled(true);
        ui->portInput->setEnabled(true);
        ui->usernameInput->setEnabled(true);
        ui->passwordInput->setEnabled(true);
        ui->connectButton->setText(tr("Connect"));
        m_client->disconnectFromHost();
    }
}

void MainWindow::brokerDisconnected()
{
    ui->hostInput->setEnabled(true);
    ui->portInput->setEnabled(true);
    ui->usernameInput->setEnabled(true);
    ui->passwordInput->setEnabled(true);
    ui->connectButton->setText(tr("Connect"));
}

void MainWindow::on_subscribeButton_clicked()
{
    auto subscription = m_client->subscribe(QString("test topic"), 0);
    if (!subscription) {
        QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not subscribe. Is there a valid connection?"));
        return;
    }
    connect(m_sub, &QMqttSubscription::messageReceived, this, &MainWindow::updateMessage);
}

void MainWindow::on_testSubButton_clicked()
{
    // QMqttMessage* message = new QMqttMessage();
    
    QJsonObject root;
    root["PlayerName"] = get_playerName();
    root["Choice"] = player1->get_choice_string(player1->get_choice());
    root["WinCount"] = 17;

    QByteArray jsonTest = QJsonDocument(root).toJson();
    qDebug() << jsonTest;

    if (m_client->publish(QString("test topic"), jsonTest,
                          0, false)
        == -1)
        QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not publish message"));   
}

void MainWindow::updateMessage(const QMqttMessage &msg)
{
    // ui->roundLabel->setText(msg.payload());
    ui->logEdit->insertPlainText(msg.payload());
    ui->logEdit->insertPlainText("msg.payload()");
}

void MainWindow::updateLogStateChange()
{
    const QString content = QDateTime::currentDateTime().toString()
                            + QLatin1String(": State Change")
                            + QString::number(m_client->state())
                            + QLatin1Char('\n');
    ui->logEdit->insertPlainText(content);
}

void MainWindow::on_backButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1); // move to homePage
}


void MainWindow::on_multiCheckBox_stateChanged(int arg1)
{
    if(ui->multiCheckBox->isChecked())
    {
        disable_multiplayer(false);
        disable_singleplayer(true);
    }
    else
    {
        disable_multiplayer(true);
        disable_singleplayer(false);
    }
}

void MainWindow::disable_multiplayer(bool state)
{
    ui->connectButton->setDisabled(state);
    ui->subscribeButton->setDisabled(state);
    ui->hostInput->setDisabled(state);
    ui->portInput->setDisabled(state);
    ui->usernameInput->setDisabled(state);
    ui->passwordInput->setDisabled(state);
    ui->playerNameInput->setDisabled(state);
}

void MainWindow::disable_singleplayer(bool state)
{
    QPixmap pixmap1(":/icon/spongeBob.jpg");
    ui->player1Avatar->setPixmap(pixmap1.scaled(ui->player1Avatar->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    QPixmap pixmap2(":/icon/squidward.jpg");
    ui->player2Avatar->setPixmap(pixmap2.scaled(ui->player2Avatar->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

QString MainWindow::get_clientId()
{
    return m_client->clientId();
}

QString MainWindow::get_playerName()
{
    QString playerName = ui->playerNameInput->text()
                         + "_"
                         + m_client->clientId().right(4);
    return playerName;
}