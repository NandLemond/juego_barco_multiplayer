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
	this->puntos_J1 = 0;
	this->puntos_J2 = 0;
	jugador_1 = std::make_shared<BarcoPlayer1>();
	jugador_2 = std::make_shared<BarcoPlayer2>();
	jugador_1->iniciaVariables();
	jugador_2->iniciaVariables();
	
}

void Game::mostrar_menu()
{
	sf::Font font;
	if (!font.loadFromFile("PixellettersFull.ttf"))
	{
		std::cout << "Error: No se pudo cargar la fuente PixellettersFull.ttf" << std::endl;
		return;
	}

	sf::Texture portadaTexture;
	if (!portadaTexture.loadFromFile("portada.png"))
	{
		std::cout << "Error: No se pudo cargar la portada portada.png" << std::endl;
		return;
	}

	sf::Sprite portadaSprite(portadaTexture);
	portadaSprite.setScale(0.8f, 0.8f);
	portadaSprite.setPosition(400.f, 140.f);

	sf::Text texto_titulo;
	texto_titulo.setFont(font);
	texto_titulo.setString("Multiplayer ship");
	texto_titulo.setCharacterSize(90);
	texto_titulo.setFillColor(sf::Color::White);
	texto_titulo.setPosition(700.f, 20.f);

	sf::Text Texto_de_inicio;
	Texto_de_inicio.setFont(font);
	Texto_de_inicio.setString("Presiona Enter para comenzar");
	Texto_de_inicio.setCharacterSize(40);
	Texto_de_inicio.setFillColor(sf::Color::White);
	Texto_de_inicio.setPosition(700.f, 800.f);

	sf::Text Texto_salida;
	Texto_salida.setFont(font);
	Texto_salida.setString("Presiona Esc para salir");
	Texto_salida.setCharacterSize(40);
	Texto_salida.setFillColor(sf::Color::White);
	Texto_salida.setPosition(757.f, 850.f);

	while (this->estado_actual == GameState::Menu)
	{
		while (this->ventana->pollEvent(this->sfmlEvent))
		{
			if (this->sfmlEvent.type == sf::Event::Closed)
				this->ventana->close();
			else if (this->sfmlEvent.type == sf::Event::KeyPressed)
			{
				if (this->sfmlEvent.key.code == sf::Keyboard::Enter)
				{
					this->estado_actual = GameState::Running;
					return;
				}
				else if (this->sfmlEvent.key.code == sf::Keyboard::Escape)
				{
					this->ventana->close();
					return;
				}
			}
		}

		this->ventana->clear();
		this->ventana->draw(portadaSprite);
		this->ventana->draw(texto_titulo);
		this->ventana->draw(Texto_de_inicio);
		this->ventana->draw(Texto_salida);
		this->ventana->display();
	}
}


void Game::inicializarWindow()
{
	this->dimensiones_ventana = sf::VideoMode(1900, 1000);
	this->ventana = new sf::RenderWindow(this->dimensiones_ventana, "Game 2", sf::Style::Close | sf::Style::Titlebar);
	this->ventana->setFramerateLimit(60);
	this->fondo = new Fondo("Fondo1.png");
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
	this->guiText.setFillColor(sf::Color::White);
	this->guiText.setCharacterSize(32);
	//Estadistica j2
	this->guiText2.setFont(this->fuente);
	this->guiText2.setFillColor(sf::Color::White);
	this->guiText2.setCharacterSize(32);
	this->guiText2.setPosition(1700, 0);

	//Fin texto juego
	this->fin_del_juego_texto.setFont(this->fuente);
	this->fin_del_juego_texto.setFillColor(sf::Color::Green);
	this->fin_del_juego_texto.setCharacterSize(60);
	this->fin_del_juego_texto.setPosition(sf::Vector2f(650, 100));
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
	delete this->ventana;
}

const bool& Game::getEndGame() const
{
	return this->fin_del_juego;
}


//Functions
const bool Game::running() const
{
	if (this->ventana && this->ventana->isOpen())
	{
		return true;
	}
	return false;
}


void Game::eventos_ventana()
{
	while (this->ventana->pollEvent(this->sfmlEvent))
	{
		switch (this->sfmlEvent.type)
		{
		case sf::Event::Closed:
			this->ventana->close();
			break;
		case sf::Event::KeyPressed:
			if (this->sfmlEvent.key.code == sf::Keyboard::Escape)
				this->ventana->close();
			break;
		}
	}
}

void Game::Generador_de_items()
{
	if (this->spawnTimer < this->spawnTimerMax) {
		this->spawnTimer += 1.f;
		return;
	}

	if (this->spawnTimer >= this->spawnTimerMax && this->bolitas.size() < this->maxBolitas) {
		std::unique_ptr<Bola> nuevaBolita;

		int randomType = std::rand() % 3; 

		switch (randomType)
		{
		case 0:
			nuevaBolita = std::make_unique<BolaDefault>(this->ventana->getSize());
			break;
		case 1:
			nuevaBolita = std::make_unique<BolaDanio>(this->ventana->getSize());
			break;
		case 2:
			nuevaBolita = std::make_unique<BolaVida>(this->ventana->getSize());
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
	this->jugador_1->update(this->ventana);
	this->jugador_2->update(this->ventana);

	if (this->jugador_1->getVida() <= 0) {
		//ganador jugador 2
		this->fin_del_juego_texto.setString("\tGanador jugador 2");
		this->fin_del_juego = true;
	}

	else if (this->jugador_2->getVida() <= 0) {
		//ganador jugador 1
		this->fin_del_juego_texto.setString("\tGanador jugador 1");
		this->fin_del_juego = true;
	}

	else if (this->puntos_J1 >= 10 || this->puntos_J2 >= 10) {
		if (this->puntos_J1 > this->puntos_J2)
		{
			// Jugador 1 es el ganador
			this->fin_del_juego_texto.setString("\tGanador jugador 1");;

		}
		else if (this->puntos_J1 < this->puntos_J2)
		{
			// Jugador 2 es el ganador
			this->fin_del_juego_texto.setString("\tGanador jugador 2");

		}
		this->fin_del_juego = true;
	}

}

void Game::Colision_bolitas()
{
	
	for (size_t i = 0; i < bolitas.size(); i++)
	{
		// Verificar colisión con el jugador 1
		if (jugador_1->getSprite().getGlobalBounds().intersects(bolitas[i]->getSprite().getGlobalBounds()))
		{
			switch (bolitas[i]->getTipo())
			{
			case 0: // BolaDefault
				puntos_J1++;
				break;
			case 1: // BolaDanio
				using namespace std::chrono_literals;
				std::this_thread::sleep_for(500ms);
			jugador_1->recibirDaño(1);
				if (puntos_J1 > 0) {
					puntos_J1 = puntos_J1 - 1;
				}
				break;
			case 2: // BolaVida
				jugador_1->ganarSalud(1);
				break;
			}

			bolitas.erase(bolitas.begin() + i);
			break; // Rompemos el loop, ya que hemos eliminado una bolita
		}

		// Verificar colisión con el jugador 2 (si existe)
		if (jugador_2->getSprite().getGlobalBounds().intersects(bolitas[i]->getSprite().getGlobalBounds()))
		{
			switch (bolitas[i]->getTipo())
			{
			case 0: // BolaDefault
				puntos_J2++;
				break;
			case 1: // BolaDanio
				using namespace std::chrono_literals;
				std::this_thread::sleep_for(500ms);
				jugador_2->recibirDaño(1);
				if (puntos_J2 > 0) {
					puntos_J2 = puntos_J2 - 1;
				}
				break;
			case 2: // BolaVida
				jugador_2->ganarSalud(1);
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

	ss << "- Jugador 1" << "\n" << " - Puntos: " << this->puntos_J1 << "\n"
		<< " - vidas: " << this->jugador_1->getVida() << " / " << this->jugador_1->getVidaMax() << "\n";

	this->guiText.setString(ss.str());

	std::stringstream ss2;

	ss2 << "Jugador 2" << "\n" << " - Puntos: " << this->puntos_J2 << "\n"
		<< " - vidas: " << this->jugador_2->getVida() << " / " << this->jugador_2->getVidaMax() << "\n";

	this->guiText2.setString(ss2.str());
}


void Game::update()
{
	this->eventos_ventana();

	if (this->fin_del_juego == false)
	{
		if (this->estado_actual == GameState::Menu)
		{
			this->mostrar_menu();
		}
		else if (this->estado_actual == GameState::Running)
		{
			this->Generador_de_items();
			this->updatePlayer();
			this->Colision_bolitas();
			this->updateGui();
		}
	}
}

void Game::mostrar_texto(sf::RenderTarget* target)
{
	target->draw(this->guiText);
	target->draw(this->guiText2);
}

void Game::render()
{
	this->ventana->clear();
	fondo->mostrar(this->ventana);

	//Render stuff
	this->jugador_1->render(this->ventana);
	this->jugador_2->render(this->ventana);

	for (auto it = this->bolitas.begin(); it != this->bolitas.end(); ++it)
	{
		(*it)->render(*this->ventana);
	}


	this->mostrar_texto(this->ventana);

	
	if (this->fin_del_juego == true) {
		this->ventana->draw(this->fin_del_juego_texto);
		
	}
	if (this->puntos_J1 == 10) 
		this->ventana->draw(this->fin_del_juego_texto);
		
	if (this->puntos_J2 == 10)
		this->ventana->draw(this->fin_del_juego_texto);

	this->ventana->display();
}
