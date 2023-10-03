//
// Created by Wojtek on 02.10.2023.
//

#include "SaveButton.h"

void SaveButton::Create() {
    Shape.setPosition(750.f, 400.f);
    Shape.setSize(sf::Vector2f(200.f, 100.f));
    Texture.loadFromFile("../Objects/SaveButton/Textures/save.png");
    Shape.setTexture(&Texture);

    SecondTexture.loadFromFile("../Objects/SaveButton/Textures/save-hover.png");
}

SaveButton::SaveButton() {
    Create();
}
