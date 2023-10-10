//
// Created by Wojtek on 03.10.2023.
//

#include "UpButton.h"

void UpButton::Create() {
    _shape.setPosition(920.f, 715.f);
    _shape.setSize(sf::Vector2f(60.f, 60.f));
    _texture.loadFromFile("../Objects/MethodObjects/Textures/up.png");
    _shape.setTexture(&_texture);
}

UpButton::UpButton() {
    Create();
}
