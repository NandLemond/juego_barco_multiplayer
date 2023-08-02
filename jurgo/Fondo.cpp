#include "Fondo.h"

Fondo::Fondo(const std::string& imagenFondo) {
   
    if (!texturaFondo.loadFromFile(imagenFondo))
    {
        // Manejar el error si la carga de la imagen falla
    }

    spriteFondo.setTexture(texturaFondo);
}

void Fondo::mostrar(sf::RenderWindow* window) {
    window->draw(spriteFondo);
}