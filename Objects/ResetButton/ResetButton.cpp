//
// Created by Wojtek on 02.10.2023.
//

#include "ResetButton.h"

void ResetButton::Create() {
    _shape.setPosition(750.f, 300.f);
    _shape.setSize(sf::Vector2f(200.f, 100.f));
    _texture.loadFromFile("../Objects/ResetButton/Textures/reset.png");
    _shape.setTexture(&_texture);

    _secondTexture.loadFromFile("../Objects/ResetButton/Textures/reset-hover.png");
}

ResetButton::ResetButton() {
    Create();
}
