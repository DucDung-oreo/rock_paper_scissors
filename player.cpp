#include "player.h"

Player::Player()
{

}

void Player::intitialize(Ui::MainWindow *ui_ptr)
{
    ui = ui_ptr;
    choices_map =
    {
        {0, "ROCK"},
        {1, "PAPER"},
        {2, "SCISSORS"}
    };
}

void Player::display_choice(int player_choice, QLabel* player_label)
{
    player_label->setText(choices_map[player_choice]);
}

int Player::generate_choice()
{
    return static_cast<int>(rand() % 3);
}

void Player::done_chosing(Player* player_ptr, QLabel* player_label)
{
    player_ptr->display_choice(player_ptr->choice, player_label);
    ui->goButton->setEnabled(true);
}
