//
// Created by Wojtek on 03.10.2023.
//

#include "Logo.h"

void Logo::Create() {
    _shape.setPosition(693.f, 30.f);
    _shape.setSize(sf::Vector2f(312.f, 175.5f));
    _texture.loadFromFile("../Objects/Logo/Textures/logo.png");
    _shape.setTexture(&_texture);
}

Logo::Logo() {
    Create();
}
