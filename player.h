#ifndef PLAYER_H
#define PLAYER_H
#pragma once

#include "ui_mainwindow.h"
#include <QMainWindow>

//enum Choices { ROCK, PAPER, SCISSORS };

class Player
{
public:
    Player();
    void intitialize(Ui::MainWindow *ui);
    void display_choice(int player_choice, QLabel* player_label);
    void done_chosing(Player* player_ptr, QLabel* player_label);
    int generate_choice();
    int choice;
private:
    Ui::MainWindow *ui;
    std::unordered_map<int, QString> choices_map;
};

#endif // PLAYER_H
