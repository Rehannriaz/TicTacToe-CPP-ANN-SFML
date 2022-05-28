#include "stdafx.h"

class Board {
    private:

        sf::Texture backgroundTexture;
        sf::Texture winningLineTexture;

        sf::Sprite bg;
        sf::Sprite winningLine;

        void initTextures();
        void initSprites();

    public:
        Board();
        virtual ~Board();

        // void update();
        void render(sf::RenderTarget &target);
    
};



Board::Board(){
    this->initTextures();
    this->initSprites();
}

Board::~Board(){

}

void Board::initTextures(){
    if(!this->backgroundTexture.loadFromFile("Textures/Board.png"))
        std::cout << "Board.png::file not loaded succesfully!\n";
    if(!this->winningLineTexture.loadFromFile("Textures/line.png"))
        std::cout << "Board.png::file not loaded succesfully!\n";
}

void Board::initSprites(){
    this->bg.setTexture(this->backgroundTexture);
    this->winningLine.setTexture(this->winningLineTexture);

    this->bg.setPosition(0.f, 0.f);
}

void Board::render(sf::RenderTarget &target){
    target.draw(this->bg);
}