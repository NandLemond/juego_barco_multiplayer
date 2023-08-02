#include "Game.h"
#include "Fondo.h"
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include <iostream>
void Game::inicializarVariables()
{
	this->fin_del_juego = false;
	this->spawnTimerMax = 10.f;
	this->spawnTimer = this->spawnTimerMax;
	this->maxBolitas = 20;
	this->numBolitas = 0;
	this->points = 0;
	this->point2 = 0;
	player1 = std::make_shared<BarcoPlayer2>();
	player2 = std::make_shared<BarcoPlayer1>();
	player1->iniciaVariables();
	player2->iniciaVariables();
	
}

void Game::inicializarWindow()
{
	this->videoMode = sf::VideoMode(1000, 1000);
	this->window = new sf::RenderWindow(this->videoMode, "Game 2", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
	this->fondo = new Fondo("Fondo.png");
}

void Game::inicializarFuente_letra()
{
	if (!this->fuente.loadFromFile("PixellettersFull.ttf"))
	{
		std::cout << " ! ERROR::GAME::INITFONTS::COULD NOT LOAD PixellettersFull.ttf" << "\n";
	}
}

void Game::inicializarTexto()
{
	//Estadistica j1
	this->guiText.setFont(this->fuente);
	this->guiText.setFillColor(sf::Color::Magenta);
	this->guiText.setCharacterSize(32);
	//Estadistica j2
	this->guiText2.setFont(this->fuente);
	this->guiText2.setFillColor(sf::Color::Black);
	this->guiText2.setCharacterSize(32);
	this->guiText2.setPosition(500, 0);

	//Fin texto juego
	this->fin_del_juego_texto.setFont(this->fuente);
	this->fin_del_juego_texto.setFillColor(sf::Color::Green);
	this->fin_del_juego_texto.setCharacterSize(60);
	this->fin_del_juego_texto.setPosition(sf::Vector2f(100, 100));
}


//Constructors and Destructors
Game::Game()
{ 
	

	this->inicializarVariables();
	this->inicializarWindow();
	this->inicializarFuente_letra();
	this->inicializarTexto();
	
}

Game::~Game()
{
	delete this->window;
}

const bool& Game::getEndGame() const
{
	return this->fin_del_juego;
}


//Functions
const bool Game::running() const
{
	if (this->window && this->window->isOpen())
	{
		return true;
	}
	return false;
}


void Game::pollEvents()
{
	while (this->window->pollEvent(this->sfmlEvent))
	{
		switch (this->sfmlEvent.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->sfmlEvent.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

void Game::spawnSwagBalls()
{
	if (this->spawnTimer < this->spawnTimerMax) {
		this->spawnTimer += 1.f;
		return;
	}

	if (this->spawnTimer >= this->spawnTimerMax && this->bolitas.size() < this->maxBolitas) {
		std::unique_ptr<Bola> nuevaBolita;

		int randomType = std::rand() % 3; // Generar un tipo aleatorio (0, 1 o 2)
		switch (randomType)
		{
		case 0:
			nuevaBolita = std::make_unique<BolaDefault>(this->window->getSize());
			break;
		case 1:
			nuevaBolita = std::make_unique<BolaDanio>(this->window->getSize());
			break;
		case 2:
			nuevaBolita = std::make_unique<BolaVida>(this->window->getSize());
			break;
		}

		bolitas.push_back(std::move(nuevaBolita));
		this->numBolitas++;
	}
	this->spawnTimer = 0.f;

	//std::cout << "Bolitas en juego: " << bolitas.size() << std::endl;
}



void Game::updatePlayer()
{
	this->player1->update(this->window);
	this->player2->update(this->window);

	if (this->player1->getVida() <= 0) {
		//ganador jugador 2
		this->fin_del_juego_texto.setString("\tGanador jugador 2");
		this->fin_del_juego = true;
	}

	else if (this->player2->getVida() <= 0) {
		//ganador jugador 1
		this->fin_del_juego_texto.setString("\tGanador jugador 1");
		this->fin_del_juego = true;
	}

	else if (this->points >= 10 || this->point2 >= 10) {
		if (this->points > this->point2)
		{
			// Jugador 1 es el ganador
			this->fin_del_juego_texto.setString("\tGanador jugador 1");;

		}
		else if (this->points < this->point2)
		{
			// Jugador 2 es el ganador
			this->fin_del_juego_texto.setString("\tGanador jugador 2");

		}
		this->fin_del_juego = true;
	}

}

void Game::updateCollision()
{
	
	for (size_t i = 0; i < bolitas.size(); i++)
	{
		// Verificar colisión con el jugador 1
		if (player1->getSprite().getGlobalBounds().intersects(bolitas[i]->getSprite().getGlobalBounds()))
		{
			switch (bolitas[i]->getTipo())
			{
			case 0: // BolaDefault
				points++;
				break;
			case 1: // BolaDanio
				player1->recibirDaño(1);
				break;
			case 2: // BolaVida
				player1->ganarSalud(1);
				break;
			}

			bolitas.erase(bolitas.begin() + i);
			break; // Rompemos el loop, ya que hemos eliminado una bolita
		}

		// Verificar colisión con el jugador 2 (si existe)
		if (player2->getSprite().getGlobalBounds().intersects(bolitas[i]->getSprite().getGlobalBounds()))
		{
			switch (bolitas[i]->getTipo())
			{
			case 0: // BolaDefault
				point2++;
				break;
			case 1: // BolaDanio
				player2->recibirDaño(1);
				break;
			case 2: // BolaVida
				player2->ganarSalud(1);
				break;
			}

			bolitas.erase(bolitas.begin() + i);
			break; // Rompemos el loop, ya que hemos eliminado una bolita
		}
	}
		
}


void Game::updateGui()
{
	std::stringstream ss;

	ss << "- Jugador 1" << "\n" << " - Puntos: " << this->points << "\n"
		<< " - vidas: " << this->player1->getVida() << " / " << this->player1->getVidaMax() << "\n";

	this->guiText.setString(ss.str());

	std::stringstream ss2;

	ss2 << "Jugador 2" << "\n" << " - Puntos: " << this->point2 << "\n"
		<< " - vidas: " << this->player2->getVida() << " / " << this->player2->getVidaMax() << "\n";

	this->guiText2.setString(ss2.str());
}


void Game::update()
{
	this->pollEvents();

	if (this->fin_del_juego == false)
	{
		
		this->spawnSwagBalls();
		this->updatePlayer();
		this->updateCollision();
		this->updateGui();
	}
}

void Game::renderGui(sf::RenderTarget* target)
{
	target->draw(this->guiText);
	target->draw(this->guiText2);
}

void Game::render()
{
	this->window->clear();
	fondo->mostrar(this->window);

	//Render stuff
	this->player1->render(this->window);
	this->player2->render(this->window);

	for (auto it = this->bolitas.begin(); it != this->bolitas.end(); ++it)
	{
		(*it)->render(*this->window);
	}

	//Render gui
	this->renderGui(this->window);

	//Render end text
	if (this->fin_del_juego == true) {
		this->window->draw(this->fin_del_juego_texto);
		
	}
	if (this->points == 10) 
		this->window->draw(this->fin_del_juego_texto);
		
	if (this->point2 == 10)
		this->window->draw(this->fin_del_juego_texto);

	this->window->display();
}
