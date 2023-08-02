#pragma once
#pragma once
#include "Item.h"

class BolaDefault : public Bola
{
public:
    BolaDefault(const sf::Vector2u& windowSize);
    virtual ~BolaDefault();
    void update() override;
};


