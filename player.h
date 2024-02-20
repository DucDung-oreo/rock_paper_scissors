#ifndef PLAYER_H
#define PLAYER_H
#pragma once

#include "ui_mainwindow.h"
#include <QMainWindow>

enum Choices { ROCK, PAPER, SCISSORS };

class Player
{
public:
    Player();
    void initialize(Ui::MainWindow *ui);
    void display_choice(Choices player_choice, QLabel* player_label);
    void done_chosing(Player* player_ptr, QLabel* player_label);
    Choices get_choice();
    void set_choice(Choices choice_enum);
    Choices generate_choice();
    QString get_result(Choices p1, Choices p2);

    int get_winCount();
    int get_tieCount();
    int get_loseCount();

private:
    Ui::MainWindow *ui;
    std::unordered_map<Choices, QString> choices_map;
    Choices choice;
    int winCount = 0;
    int tieCount = 0;
    int loseCount = 0;
};

#endif // PLAYER_H
