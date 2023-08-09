#include "BarcoPlayer1.h"
#include <iostream>

void BarcoPlayer1::inicializarImagenBarco() {
	if (!this->textureBarco.loadFromFile("BarcoPlayer1.png"))
	{
		std::cout << "ERROR::PLAYER::INITSHAPE::Failed to load Barco.png" << std::endl;
	}


	this->spriteBarco.setTexture(this->textureBarco);


	this->spriteBarco.setScale(sf::Vector2f(0.5f, 0.5f));
}
void BarcoPlayer1::iniImage() {
	this->inicializarImagenBarco();
}


BarcoPlayer1::BarcoPlayer1(float x, float y)
{
	
	this->spriteBarco.setPosition(x, y);

	//this->iniciaVariables();
	//this->inicializarImagenBarco();
	
}

void BarcoPlayer1::movimiento()
{
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->spriteBarco.move(-this->velocidad, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->spriteBarco.move(this->velocidad, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->spriteBarco.move(0.f, -this->velocidad);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->spriteBarco.move(0.f, this->velocidad);
	}
}