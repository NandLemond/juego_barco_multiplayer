#pragma once

#include<iostream>
#include<ctime>
#include<vector>
#include<sstream>
#include "Fondo.h"
#include "Barco.h"
#include "Item.h"
#include "ItemDefault.h"
#include "ItemVida.h"
#include "ItemDanio.h"
#include <memory>
#include "BarcoPlayer1.h"
#include "BarcoPlayer2.h"
#include <vector>

class Game
{
private:
	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	bool fin_del_juego;
	sf::Event sfmlEvent;
	Fondo* fondo;

	


	std::shared_ptr<Barco> player1;
	std::shared_ptr<Barco> player2;

	int points;
	int point2;
	sf::Font fuente;
	sf::Text guiText;
	sf::Text fin_del_juego_texto;
	sf::Text guiText2;

	std::vector<std::unique_ptr<Bola>> bolitas;
	float spawnTimerMax;
	float spawnTimer;
	int maxBolitas;
	int numBolitas;

	void inicializarVariables();
	void inicializarWindow();
	void inicializarFuente_letra();
	void inicializarTexto();

public:
	//Constructors and Destructors
	Game();
	~Game();

	
	const bool& getEndGame() const;
	//const bool& getEndGame2() const;
	

	
	const bool running() const;
	void pollEvents();

	void spawnSwagBalls();
	//const int randBallType() const;
	void updatePlayer();
	void updateCollision();
	void updateGui();
	void update();

	void renderGui(sf::RenderTarget* target);
	void render();
};
