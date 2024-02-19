#include "player.h"


Player::Player()
{

}

void Player::initialize(Ui::MainWindow *ui_ptr)
{
    ui = ui_ptr;
    choices_map =
    {
        {ROCK, "ROCK"},
        {PAPER, "PAPER"},
        {SCISSORS, "SCISSORS"}
    };
}

void Player::display_choice(Choices player_choice, QLabel* player_label)
{
    player_label->setText(choices_map.at(player_choice));
}

Choices Player::generate_choice()
{
    return static_cast<Choices>(rand() % 3);
}

void Player::done_chosing(Player* player_ptr, QLabel* player_label)
{
    player_ptr->display_choice(player_ptr->choice, player_label);
    ui->goButton->setEnabled(true);
}

Choices Player::get_choice()
{
    return choice;
}

void Player::set_choice(Choices choice_enum)
{
    choice = choice_enum;
    qDebug() << "setChoice() " << choice;
}
