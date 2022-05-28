#pragma once

#include "stdafx.h"
#include "Headers.h"
#include "Board.h"
#include "XOSprites.h"
#include "TTT.h"
#include <Windows.h>

class Game {
    private:

        sf::RenderWindow *window;
        sf::Event event;

        TTT ttt;
        ANN AI;
        Board board;
        std::vector<XOSprites*> sprites;

        void pollEvents();
        sf::Vector2f getMousePos();
        void changeMove();
        void addXOSprite(float x, float y);
        void initWindow();
        void initVariables();

        void isWin();

    public:

        Game();
        virtual ~Game();

        // Functions
        bool running();
        void update();
        void render();
};


Game::Game(){
    std::vector<int> topology = {9, 5, 2, 1};
    AI.init(topology);
    AI.train();


    this->initWindow();
    this->initVariables();
}

Game::~Game(){
    delete this->window;

    for(auto sprite : this->sprites){
        delete sprite;
    }
    sprites.clear();

}

void Game::initWindow(){
    this->window = new sf::RenderWindow(sf::VideoMode(600, 600), "Game boiler plate", sf::Style::Close | sf::Style::Titlebar);
}

void Game::initVariables(){
    
}

void Game::isWin(){
    if(this->ttt.check()){
        if(this->ttt.check() == -1){
            std::cout << "O wins\n";
            Sleep(1000);
            this->window->close();
        } else {
            std::cout << "X wins\n";
            Sleep(1000);
            this->window->close();
        }
    } else if(this->ttt.getNumMoves() == 9){
        std::cout << "DRAW\n";
        Sleep(1000);
        this->window->close();
    }
    return;
}

bool Game::running(){
    return this->window->isOpen();
}

void Game::update(){
    pollEvents();
}

void Game::pollEvents(){
    while(this->window->pollEvent(this->event)){
        if(this->event.type == sf::Event::Closed)
            this->window->close();
        if(this->event.type == sf::Event::KeyPressed && this->event.key.code == sf::Keyboard::Escape)
            this->window->close();

        if(this->event.type == sf::Event::MouseButtonPressed && this->event.mouseButton.button == sf::Mouse::Left){
            
            std::cout << "Mouse Button Pressed!\n";

            sf::Vector2i mousePos = sf::Mouse::getPosition(*this->window);
            int row, col;
            float bias = 20.f;
            
            col = mousePos.x / 200;
            row = mousePos.y / 200;


            if(this->ttt.isEmpty(row, col)){
                this->addXOSprite(col*200+bias, row*200+bias);
                this->ttt.place(row, col);
                this->ttt.changeMove();

                this->isWin();

                int AImove, AIprob;
                tie(AImove, AIprob) = AI.getBestMove(ttt.getBoardVec(), ttt.getEmptyPositionsVec(), ttt.getMove());

                Sleep(200);

                row = (AImove)/3;
                col = (AImove)%3;

                this->addXOSprite(col*200+bias, row*200+bias);
                this->ttt.place(row, col);
                this->ttt.changeMove();
                this->isWin();
            }
        }
    }
}

void Game::addXOSprite(float x, float y){
    if(this->ttt.getMove() == 1){
        this->sprites.push_back(new XSprite(x, y));
    } else {
        this->sprites.push_back(new OSprite(x, y));
    }
}

void Game::render(){
    this->window->clear();

    board.render(*this->window);

    for(auto sprite : sprites)
        sprite->render(*this->window);

    // flip the screen
    this->window->display();

}