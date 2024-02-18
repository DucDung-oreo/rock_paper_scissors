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
    void intitialize(Ui::MainWindow *ui);
    void display_choice(Choices player_choice, QLabel* player_label);
    void done_chosing(Player* player_ptr, QLabel* player_label);
    Choices get_choice();
    void set_choice(Choices choice_enum);
    Choices generate_choice();

private:
    Ui::MainWindow *ui;
    std::unordered_map<int, QString> choices_map;
    Choices choice;
};

#endif // PLAYER_H
