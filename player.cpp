#include "player.h"

Player::Player()
{

}

void Player::intitialize(Ui::MainWindow *ui_ptr)
{
    ui = ui_ptr;
}

void Player::display_choice(Choices player_choice)
{
    switch (player_choice) {
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

Choices Player::generate_choice()
{
    return static_cast<Choices>(rand() % 3);
}
