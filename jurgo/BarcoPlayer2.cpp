#include "BarcoPlayer2.h"
#include <iostream>

 void BarcoPlayer2::inicializarImagenBarco()  {
	if (!this->textureBarco.loadFromFile("BarcoPlayer2.png"))
	{
		std::cout << "ERROR::PLAYER::INITSHAPE::Failed to load Barco.png" << std::endl;
	}


	this->spriteBarco.setTexture(this->textureBarco);


	this->spriteBarco.setScale(sf::Vector2f(0.5f, 0.5f));
}

 void BarcoPlayer2::iniImage() {
	 this->inicializarImagenBarco();
 }

 BarcoPlayer2::BarcoPlayer2(float x, float y)
 {
	 
	this->spriteBarco.setPosition(x, y);

	//this->iniciaVariables();
    //this->inicializarImagenBarco();
	
}

void BarcoPlayer2::movimiento() 
{
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		this->spriteBarco.move(-this->velocidad, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		this->spriteBarco.move(this->velocidad, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		this->spriteBarco.move(0.f, -this->velocidad);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		this->spriteBarco.move(0.f, this->velocidad);
	}
}