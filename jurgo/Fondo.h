#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Fondo {
private:
	sf::Texture texturaFondo;
	sf::Sprite spriteFondo;
	
public:
	Fondo(const std::string& imageFondo);
	void mostrar(sf::RenderWindow* ventana);
	

};