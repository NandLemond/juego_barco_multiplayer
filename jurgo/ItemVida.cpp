#include "ItemVida.h"

BolaVida::BolaVida(const sf::Vector2u& windowSize) : Bola(2) // El valor 2 representa el tipo de bola de vida
{
    texture.loadFromFile("vida.png");
    sprite.setTexture(texture);
    this->sprite.setScale(sf::Vector2f(0.3f, 0.3f));
    float posX = static_cast<float>(rand() % (windowSize.x - static_cast<int>(this->sprite.getGlobalBounds().width)));
    float posY = static_cast<float>(rand() % (windowSize.y - static_cast<int>(this->sprite.getGlobalBounds().height)));
    this->sprite.setPosition(sf::Vector2f(posX, posY));
}

BolaVida::~BolaVida()
{
}

void BolaVida::update()
{
    // Lógica específica para la bola de vida, si es necesario
}
