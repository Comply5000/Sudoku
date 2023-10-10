//
// Created by Wojtek on 02.10.2023.
//

#include "LoadButton.h"

void LoadButton::Create() {
    _shape.setPosition(750.f, 500.f);
    _shape.setSize(sf::Vector2f(200.f, 100.f));
    _texture.loadFromFile("../Objects/LoadButton/Textures/load.png");
    _shape.setTexture(&_texture);

    _secondTexture.loadFromFile("../Objects/LoadButton/Textures/load-hover.png");
}

LoadButton::LoadButton() {
    Create();
}
