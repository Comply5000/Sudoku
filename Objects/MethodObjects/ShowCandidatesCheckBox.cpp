//
// Created by Wojtek on 03.10.2023.
//

#include "ShowCandidatesCheckBox.h"

void ShowCandidatesCheckBox::Create() {
    _shape.setPosition(750.f, 625.f);
    _shape.setSize(sf::Vector2f(50.f, 50.f));
    _texture.loadFromFile("../Objects/MethodObjects/Textures/check2.png");
    _secondTexture.loadFromFile("../Objects/MethodObjects/Textures/check.png");
    _shape.setTexture(&_texture);
}

ShowCandidatesCheckBox::ShowCandidatesCheckBox() {
    Create();
}
