//
// Created by Wojtek on 02.10.2023.
//

#include "LoadButton.h"

void LoadButton::Create() {
    Shape.setPosition(750.f, 500.f);
    Shape.setSize(sf::Vector2f(200.f, 100.f));
    Texture.loadFromFile("../Objects/LoadButton/Textures/load.png");
    Shape.setTexture(&Texture);

    SecondTexture.loadFromFile("../Objects/LoadButton/Textures/load-hover.png");
}

LoadButton::LoadButton() {
    Create();
}
