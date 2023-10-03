//
// Created by Wojtek on 03.10.2023.
//

#include "UpButton.h"

void UpButton::Create() {
    Shape.setPosition(920.f, 715.f);
    Shape.setSize(sf::Vector2f(60.f, 60.f));
    Texture.loadFromFile("../Objects/MethodObjects/Textures/up.png");
    Shape.setTexture(&Texture);
}

UpButton::UpButton() {
    Create();
}
