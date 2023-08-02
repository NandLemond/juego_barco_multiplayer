#include "ItemDefault.h"

BolaDefault::BolaDefault(const sf::Vector2u& windowSize) : Bola(0) // El valor 0 representa el tipo de bola default
{
    texture.loadFromFile("cofre.png");
    sprite.setTexture(texture);
    this->sprite.setScale(sf::Vector2f(0.3f, 0.3f));
    float posX = static_cast<float>(rand() % (windowSize.x - static_cast<int>(this->sprite.getGlobalBounds().width)));
    float posY = static_cast<float>(rand() % (windowSize.y - static_cast<int>(this->sprite.getGlobalBounds().height)));
    this->sprite.setPosition(sf::Vector2f(posX, posY));
}

BolaDefault::~BolaDefault()
{
}

void BolaDefault::update()
{
    // Lógica específica para la bola default, si es necesario
}
