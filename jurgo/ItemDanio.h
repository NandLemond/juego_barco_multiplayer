#pragma once
#pragma once
#include "Item.h"

class BolaDanio : public Bola
{
public:
    BolaDanio(const sf::Vector2u& windowSize);
    virtual ~BolaDanio();
    void update() override;
};

