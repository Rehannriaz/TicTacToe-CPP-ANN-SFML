#include "stdafx.h"

class Board
{
private:
    sf::Texture backgroundTexture;
    sf::Texture winningLineTexture;

    sf::Sprite bg;
    sf::Sprite winningLine;

    /**
     * @brief 
     * 
     *
     *
     */
    void initTextures();

    /**
     * @brief initializes the sprites for the board class
     *
     */
    void initSprites();

public:
    /**
     * @brief Construct a new Board object
     *
     */
    Board();

    /**
     * @brief Destroy the Board object
     *
     */
    virtual ~Board();

    /**
     * @brief renders the sprites onto the screen
     * USES DOUBLE BUFFERING
     *
     * @param target where to draw the sprites
     */
    void render(sf::RenderTarget &target);
};

Board::Board()
{
    this->initTextures();
    this->initSprites();
}

Board::~Board()
{
}

void Board::initTextures()
{
    if (!this->backgroundTexture.loadFromFile("Textures/Board.png"))
        std::cout << "Board.png::file not loaded succesfully!\n";
    if (!this->winningLineTexture.loadFromFile("Textures/line.png"))
        std::cout << "Board.png::file not loaded succesfully!\n";
}

void Board::initSprites()
{
    this->bg.setTexture(this->backgroundTexture);
    this->winningLine.setTexture(this->winningLineTexture);

    this->bg.setPosition(0.f, 0.f);
}

void Board::render(sf::RenderTarget &target)
{
    target.draw(this->bg);
}