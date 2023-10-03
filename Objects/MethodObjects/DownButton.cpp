//
// Created by Wojtek on 03.10.2023.
//

#include "DownButton.h"

void DownButton::Create() {
    Shape.setPosition(920.f, 775.f);
    Shape.setSize(sf::Vector2f(60.f, 60.f));
    Texture.loadFromFile("../Objects/MethodObjects/Textures/down.png");
    Shape.setTexture(&Texture);
}

DownButton::DownButton() {
    Create();
}
