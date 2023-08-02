#pragma once
#include "Barco.h"

class BarcoPlayer2 :public Barco {
protected:



	//void iniciaVariables();



public:
	BarcoPlayer2(float x = 200.f, float y = 400.f);
	virtual ~BarcoPlayer2() {}
	virtual void iniImage() override;
	void inicializarImagenBarco() override;
	//const sf::Sprite& getSprite() const;
	//const int& getVida() const;
	//const int& getVidaMax() const;

	//void recibirDaño(const int damage);
	//void ganarSalud(const int health);

	virtual void movimiento() override;
	//void actualizarColisiónVentana(const sf::RenderTarget* target);

	//void update(const sf::RenderTarget* target);
	//void render(sf::RenderTarget* target);

};