#include "stdafx.h"

class XOSprites
{
protected:
    sf::Sprite sprite;
    sf::Texture spriteTexture;

public:
    /**
     * @brief Construct a new XOSprites abstract
     *
     */
    XOSprites();

    /**
     * @brief Destroy the XOSprites abstract
     *
     */
    virtual ~XOSprites();

    /**
     * @brief abstract function inherited to X_Sprite and O_Sprite
     *
     */
    virtual void initTextures() = 0;

    /**
     * @brief initializes the sprites
     *
     * @param x local position of sprite
     * @param y local position of sprite
     */
    void initSprites(float x, float y);

    /**
     * @brief draws sprite on buffer
     *
     * @param target screen buffer
     */
    void render(sf::RenderTarget &target);
};

class XSprite : public XOSprites
{

public:
    /**
     * @brief Construct a new XSprite object
     *
     * @param x local position of sprite
     * @param y local position of sprite
     */
    XSprite(float x, float y);

    /**
     * @brief Destroy the XSprite object
     *
     */
    ~XSprite();

    /**
     * @brief initialize textures for X_Sprite
     *
     */
    void initTextures();
};

class OSprite : public XOSprites
{

public:
    /**
     * @brief Construct a new OSprite object
     *
     * @param x local position of sprite
     * @param y local position of sprite
     */
    OSprite(float x, float y);

    /**
     * @brief Destroy the OSprite object
     *
     */
    ~OSprite();

    /**
     * @brief initialize textures for X_Sprite
     *
     */
    void initTextures();
};

XOSprites::XOSprites()
{
}

XOSprites::~XOSprites()
{
}

void XOSprites::initSprites(float x, float y)
{
    this->sprite.setTexture(this->spriteTexture);
    this->sprite.setScale(sf::Vector2f(0.8f, 0.8f));
    this->sprite.setPosition(x, y);
}

void XOSprites::render(sf::RenderTarget &target)
{
    target.draw(this->sprite);
}

XSprite::XSprite(float x, float y)
{
    this->initTextures();
    this->initSprites(x, y);
}

XSprite::~XSprite()
{
}

void XSprite::initTextures()
{
    if (!this->spriteTexture.loadFromFile("Textures/XSprite.png"))
        std::cout << "XSprite.png::file not loaded succesfully!\n";
}

OSprite::OSprite(float x, float y)
{
    this->initTextures();
    this->initSprites(x, y);
}

OSprite::~OSprite()
{
}

void OSprite::initTextures()
{
    if (!this->spriteTexture.loadFromFile("Textures/OSprite.png"))
        std::cout << "OSprite.png::file not loaded succesfully!\n";
}