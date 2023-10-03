//
// Created by Wojtek on 03.10.2023.
//

#include "Logo.h"

void Logo::Create() {
    Shape.setPosition(693.f, 30.f);
    Shape.setSize(sf::Vector2f(312.f, 175.5f));
    Texture.loadFromFile("../Objects/Logo/Textures/logo.png");
    Shape.setTexture(&Texture);
}

Logo::Logo() {
    Create();
}
