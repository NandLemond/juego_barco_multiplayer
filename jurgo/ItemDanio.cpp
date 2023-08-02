#include "ItemDanio.h"

BolaDanio::BolaDanio(const sf::Vector2u& windowSize) : Bola(1) // El valor 1 representa el tipo de bola de daño
{
    texture.loadFromFile("bomba.png");
    sprite.setTexture(texture);
    this->sprite.setScale(sf::Vector2f(0.3f, 0.3f));
    float posX = static_cast<float>(rand() % (windowSize.x - static_cast<int>(this->sprite.getGlobalBounds().width)));
    float posY = static_cast<float>(rand() % (windowSize.y - static_cast<int>(this->sprite.getGlobalBounds().height)));
    this->sprite.setPosition(sf::Vector2f(posX, posY));
}

BolaDanio::~BolaDanio()
{
}

void BolaDanio::update()
{
    // Lógica específica para la bola de daño, si es necesario
}