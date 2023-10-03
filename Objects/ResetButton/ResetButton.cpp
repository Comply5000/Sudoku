//
// Created by Wojtek on 02.10.2023.
//

#include "ResetButton.h"

void ResetButton::Create() {
    Shape.setPosition(750.f, 300.f);
    Shape.setSize(sf::Vector2f(200.f, 100.f));
    Texture.loadFromFile("../Objects/ResetButton/Textures/reset.png");
    Shape.setTexture(&Texture);

    SecondTexture.loadFromFile("../Objects/ResetButton/Textures/reset-hover.png");
}

ResetButton::ResetButton() {
    Create();
}
