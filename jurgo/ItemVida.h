#pragma once
#pragma once
#include "Item.h"

class BolaVida : public Bola
{
public:
    BolaVida(const sf::Vector2u& windowSize);
    virtual ~BolaVida();
    void update() override;
};

