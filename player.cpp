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
}

QString Player::get_choice_string(Choices choice_enum)
{
    if (auto search = choices_map.find(choice_enum); search != choices_map.end())
    {
        return choices_map.at(choice_enum);
    }
    else
    {
        return "NOT AVAILABLE!!!";
    }
}

QString Player::get_result(Choices p1, Choices p2)
{
    if (p1 == p2)
    {
        tieCount++;
        return "IT'S A TIE ಠ_ಠ";
    }
    else if ((p1 - p2 == -1) || (p1 - p2 == 2))
    {
        loseCount++;
        return "YOU LOSE ಥ_ಥ";
    }
    else
    {
        winCount++;
        return "YOU WIN (⌐■_■)";
    }
}

int Player::get_winCount()
{
    return winCount;
}

int Player::get_tieCount()
{
    return tieCount;
}

int Player::get_loseCount()
{
    return loseCount;
}


