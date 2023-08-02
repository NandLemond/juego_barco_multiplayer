#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Barco
{
protected:
	
	sf::Sprite spriteBarco;
	sf::Texture textureBarco;

	float velocidad;
	int vida;
	int vidaMax;
	
	
	
	

public:
	//void 
	Barco();
	virtual ~Barco();

	virtual void inicializarImagenBarco() =  0;
	virtual void movimiento() = 0;


	void iniciaVariables();
	
	void iniVelocidad();
	void iniVida();

	virtual void iniImage() = 0;



	const sf::Sprite& getSprite() const;
	const int& getVida() const;
	const int& getVidaMax() const;
	float& getVelocidad() ;

	void recibirDaño(const int damage);
	void ganarSalud(const int health);

	

	void actualizarColisiónVentana(const sf::RenderTarget* target);
	
	void update(const sf::RenderTarget* target);
	
	void render(sf::RenderTarget* target);
	
	
};


