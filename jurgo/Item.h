// Bola.h
#pragma once
#include <SFML/Graphics.hpp> //2d
#include<iostream>    
#include<random>
class Bola
{
protected:
    int tipo;
    sf::Texture texture;
    sf::Sprite sprite;

public:
    Bola(int tipo);
    virtual ~Bola();
    void setTexture(const sf::Texture& texture);
    const sf::Sprite& getSprite() const;
    const int& getTipo() const;
    virtual void update() = 0;
    void render(sf::RenderTarget& target);
};