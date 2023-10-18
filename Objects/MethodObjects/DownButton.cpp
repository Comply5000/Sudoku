//
// Created by Wojtek on 03.10.2023.
//

#include "DownButton.h"

void DownButton::Create() {
    _shape.setPosition(930.f, 775.f);
    _shape.setSize(sf::Vector2f(60.f, 60.f));
    _texture.loadFromFile("../Objects/MethodObjects/Textures/down.png");
    _shape.setTexture(&_texture);
}

DownButton::DownButton() {
    Create();
}
