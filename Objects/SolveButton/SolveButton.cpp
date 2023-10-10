//
// Created by Wojtek on 02.10.2023.
//

#include "SolveButton.h"

void SolveButton::Create() {
    _shape.setPosition(750.f, 200.f);
    _shape.setSize(sf::Vector2f(200.f, 100.f));
    _texture.loadFromFile("../Objects/SolveButton/Textures/solve.png");
    _shape.setTexture(&_texture);

    _secondTexture.loadFromFile("../Objects/SolveButton/Textures/solve-hover.png");
}

SolveButton::SolveButton() {
    Create();
}


