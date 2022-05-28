#include "stdafx.h"

class XOSprites {
    protected:
        sf::Sprite sprite;
        sf::Texture spriteTexture;
    public:
        XOSprites();
        virtual ~XOSprites();
    
        virtual void initTextures() = 0;
        void initSprites(float x, float y);
        void render(sf::RenderTarget &target);
};

class XSprite : public XOSprites{

    public:
        XSprite(float x, float y);
        ~XSprite();
        
        void initTextures();
};

class OSprite : public XOSprites{

    public:
        OSprite(float x, float y);
        ~OSprite();
        
        void initTextures();
};



XOSprites::XOSprites(){
    
}

XOSprites::~XOSprites(){

}

void XOSprites::initSprites(float x, float y){
    this->sprite.setTexture(this->spriteTexture);
    this->sprite.setScale(sf::Vector2f(0.8f, 0.8f));
    this->sprite.setPosition(x, y);
}

void XOSprites::render(sf::RenderTarget &target){
    target.draw(this->sprite);
}


XSprite::XSprite(float x, float y){
    this->initTextures();
    this->initSprites(x, y);
}

XSprite::~XSprite(){

}

void XSprite::initTextures(){
    if(!this->spriteTexture.loadFromFile("Textures/XSprite.png"))
        std::cout << "XSprite.png::file not loaded succesfully!\n";       
}

OSprite::OSprite(float x, float y){
    this->initTextures();
    this->initSprites(x, y);
}

OSprite::~OSprite(){

}

void OSprite::initTextures(){
    if(!this->spriteTexture.loadFromFile("Textures/OSprite.png"))
        std::cout << "OSprite.png::file not loaded succesfully!\n";       
}