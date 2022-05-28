/**
 * @file main.cpp
 * @author Faizam Haq 2021368, Rehan Riaz 2021438, Zaid bin Muzammil 2021718
 * @brief TIC-TAC-TOE game implementing ANNS for moves and SFML
 * @version 1.8.9
 * @date 2022-05-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "stdafx.h"
#include "Game.h"

int main()
{
    Game game;

    while (game.running())
    {
        game.update();
        game.render();
    }

    return 0;
}