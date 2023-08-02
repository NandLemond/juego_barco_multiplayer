// Bola.cpp
#include "Item.h"

Bola::Bola(int tipo) : tipo(tipo)
{
    // Cargar la textura adecuada según el tipo
    if (tipo == 0) // BolaDefault
    {
        texture.loadFromFile("cofre.png");
    }
    else if (tipo == 1) // BolaDanio
    {
        texture.loadFromFile("bomba.png");
    }
    else if (tipo == 2) // BolaVida
    {
        texture.loadFromFile("vida.png");
    }

    sprite.setTexture(texture);

}

Bola::~Bola()
{
}

void Bola::setTexture(const sf::Texture& texture)
{
    this->texture = texture;
    this->sprite.setTexture(this->texture);
}

const sf::Sprite& Bola::getSprite() const
{
    return this->sprite;
}

const int& Bola::getTipo() const
{
    return this->tipo;
}

void Bola::render(sf::RenderTarget& target)
{
    target.draw(this->sprite);
}
