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
    void display_choice(Choices player_choice);
    Choices generate_choice();
    Choices choice;
private:
    Ui::MainWindow *ui;
};

#endif // PLAYER_H
