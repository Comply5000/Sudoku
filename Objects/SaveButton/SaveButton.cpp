//
// Created by Wojtek on 02.10.2023.
//

#include "SaveButton.h"

void SaveButton::Create() {
    _shape.setPosition(750.f, 400.f);
    _shape.setSize(sf::Vector2f(200.f, 100.f));
    _texture.loadFromFile("../Objects/SaveButton/Textures/save.png");
    _shape.setTexture(&_texture);

    _secondTexture.loadFromFile("../Objects/SaveButton/Textures/save-hover.png");
}

SaveButton::SaveButton() {
    Create();
}
