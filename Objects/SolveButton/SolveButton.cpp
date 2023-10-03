//
// Created by Wojtek on 02.10.2023.
//

#include "SolveButton.h"

void SolveButton::Create() {
    Shape.setPosition(750.f, 200.f);
    Shape.setSize(sf::Vector2f(200.f, 100.f));
    Texture.loadFromFile("../Objects/SolveButton/Textures/solve.png");
    Shape.setTexture(&Texture);

    SecondTexture.loadFromFile("../Objects/SolveButton/Textures/solve-hover.png");
}

SolveButton::SolveButton() {
    Create();
}


