#pragma once

#include "stdafx.h"
#include <Windows.h>

class Game
{
private:
    sf::RenderWindow *window;
    sf::Event event;

    TTT ttt;
    ANN AI;
    Board board;
    std::vector<XOSprites *> sprites;

    /**
     * @brief polls events
     * - functionality for what to with events
     *
     */
    void pollEvents();

    /**
     * @brief Get the local Mouse Pos object
     *
     * @return sf::Vector2f returns vector(x, y) of local mouse pos
     */
    sf::Vector2f getMousePos();

    /**
     * @brief changes tic-tax-toe move from x to o and viceversa
     *
     */
    void changeMove();

    /**
     * @brief places X/O sprite on the buffer
     *
     *
     * @param x position of sprite
     * @param y position of sprite
     */
    void addXOSprite(float x, float y);

    /**
     * @brief initializes SFML window object
     *
     */
    void initWindow();

    /**
     * @brief initialize variables
     *
     */
    void initVariables();

    /**
     * @brief checks the tic-tac-toe board for any wins
     *
     */
    void isWin();

public:
    /**
     * @brief Construct a new Game object
     *
     */
    Game();

    /**
     * @brief Destroy the Game object
     *
     */
    virtual ~Game();

    // Functions

    /**
     * @brief is the window open?
     *
     * @return true if game is running
     * @return false if game is not running
     */
    bool running();

    /**
     * @brief calls sprite updates and Game Object updates
     *
     */
    void update();

    /**
     * @brief calls sprites render functions to draw on buffer
     *
     * - flips the buffer to draw on screen
     *
     */
    void render();
};

Game::Game()
{
    std::vector<int> topology = {9, 5, 2, 1};
    AI.init(topology);
    AI.train();

    this->initWindow();
    this->initVariables();
}

Game::~Game()
{
    delete this->window;

    for (auto sprite : this->sprites)
    {
        delete sprite;
    }
    sprites.clear();
}

void Game::initWindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode(600, 600), "Game boiler plate", sf::Style::Close | sf::Style::Titlebar);
}

void Game::initVariables()
{
}

void Game::isWin()
{
    if (this->ttt.check())
    {
        if (this->ttt.check() == -1)
        {
            std::cout << "O wins\n";
            Sleep(1000);
            this->window->close();
        }
        else
        {
            std::cout << "X wins\n";
            Sleep(1000);
            this->window->close();
        }
    }
    else if (this->ttt.getNumMoves() == 9)
    {
        std::cout << "DRAW\n";
        Sleep(1000);
        this->window->close();
    }
    return;
}

bool Game::running()
{
    return this->window->isOpen();
}

void Game::update()
{
    pollEvents();
}

void Game::pollEvents()
{
    while (this->window->pollEvent(this->event))
    {
        if (this->event.type == sf::Event::Closed)
            this->window->close();
        if (this->event.type == sf::Event::KeyPressed && this->event.key.code == sf::Keyboard::Escape)
            this->window->close();

        if (this->event.type == sf::Event::MouseButtonPressed && this->event.mouseButton.button == sf::Mouse::Left)
        {

            std::cout << "Mouse Button Pressed!\n";

            sf::Vector2i mousePos = sf::Mouse::getPosition(*this->window);
            int row, col;
            float bias = 20.f;

            col = mousePos.x / 200;
            row = mousePos.y / 200;

            if (this->ttt.isEmpty(row, col))
            {
                this->addXOSprite(col * 200 + bias, row * 200 + bias);
                this->ttt.place(row, col);
                this->ttt.changeMove();

                this->isWin();

                int AImove, AIprob;
                tie(AImove, AIprob) = AI.getBestMove(ttt.getBoardVec(), ttt.getEmptyPositionsVec(), ttt.getMove());

                Sleep(200);

                row = (AImove) / 3;
                col = (AImove) % 3;

                this->addXOSprite(col * 200 + bias, row * 200 + bias);
                this->ttt.place(row, col);
                this->ttt.changeMove();
                this->isWin();
            }
        }
    }
}

void Game::addXOSprite(float x, float y)
{
    if (this->ttt.getMove() == 1)
    {
        this->sprites.push_back(new XSprite(x, y));
    }
    else
    {
        this->sprites.push_back(new OSprite(x, y));
    }
}

void Game::render()
{
    this->window->clear();

    board.render(*this->window);

    for (auto sprite : sprites)
        sprite->render(*this->window);

    // flip the screen
    this->window->display();
}