#include "Barco.h"
#include<iostream>
#include <chrono>
#include <thread>

void foo(int mcs) {
	std::this_thread::sleep_for(std::chrono::milliseconds(mcs));
}
void Barco::iniciaVariables()
{
	std::thread t(foo, 1000);
	t.join();
	iniVelocidad();
	iniVida();
	iniImage();
}

void Barco::iniVelocidad() {
	this->velocidad = 6.f;
}
void Barco::iniVida() {
	this->vidaMax = 3;
	this->vida = vidaMax;

}

Barco::Barco()
{
	
}

Barco::~Barco()
{

}

//Accessors
const sf::Sprite& Barco::getSprite() const
{
	return this->spriteBarco;
}

const int& Barco::getVida() const
{
	return this->vida;
}

const int& Barco::getVidaMax() const
{
	return this->vidaMax;
}
 float& Barco::getVelocidad() {
	return this->velocidad;
}
//Functions
void Barco::recibirDaño(const int damage)
{
	if (this->vida > 0)
		this->vida -= damage;

	if (this->vida < 0)
		this->vida = 0;
}

void Barco::ganarSalud(const int health)
{
	if (this->vida < this->vidaMax)
		this->vida += health;

	if (this->vida > this->vidaMax)
		this->vida = this->vidaMax;
}

void Barco::actualizarColisiónVentana(const sf::RenderTarget* target)
{
	//Left
	if (this->spriteBarco.getGlobalBounds().left <= 0.f)
		this->spriteBarco.setPosition(0.f, this->spriteBarco.getGlobalBounds().top);
	//Right
	if (this->spriteBarco.getGlobalBounds().left + this->spriteBarco.getGlobalBounds().width >= target->getSize().x)
		this->spriteBarco.setPosition(target->getSize().x - this->spriteBarco.getGlobalBounds().width, this->spriteBarco.getGlobalBounds().top);
	//Top
	if (this->spriteBarco.getGlobalBounds().top <= 0.f)
		this->spriteBarco.setPosition(this->spriteBarco.getGlobalBounds().left, 0.f);
	//Bottom
	if (this->spriteBarco.getGlobalBounds().top + this->spriteBarco.getGlobalBounds().height >= target->getSize().y)
		this->spriteBarco.setPosition(this->spriteBarco.getGlobalBounds().left, target->getSize().y - this->spriteBarco.getGlobalBounds().height);
}

void Barco::update(const sf::RenderTarget* target)
{  

	this->movimiento();

	this->actualizarColisiónVentana(target);
}

void Barco::render(sf::RenderTarget* target)
{
	target->draw(this->spriteBarco);
}

