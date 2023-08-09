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
#include <thread>
#include <chrono>


class Game
{
private:
	sf::VideoMode dimensiones_ventana;
	sf::RenderWindow* ventana;
	bool fin_del_juego;
	sf::Event sfmlEvent;
	Fondo* fondo;
	enum class GameState
	{
		Menu,
		Running,
		GameOver
	};

	GameState estado_actual;
	std::shared_ptr<Barco> jugador_1;
	std::shared_ptr<Barco> jugador_2;

	int puntos_J1;
	int puntos_J2;
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
	void eventos_ventana();
	void mostrar_menu();
	void Generador_de_items();
	//const int randBallType() const;
	void updatePlayer();
	void Colision_bolitas();
	void updateGui();
	void update();

	void mostrar_texto(sf::RenderTarget* target);
	void render();
};
