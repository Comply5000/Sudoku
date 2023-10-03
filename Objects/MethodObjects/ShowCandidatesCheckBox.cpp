//
// Created by Wojtek on 03.10.2023.
//

#include "ShowCandidatesCheckBox.h"

void ShowCandidatesCheckBox::Create() {
    Shape.setPosition(750.f, 625.f);
    Shape.setSize(sf::Vector2f(50.f, 50.f));
    Texture.loadFromFile("../Objects/MethodObjects/Textures/check2.png");
    SecondTexture.loadFromFile("../Objects/MethodObjects/Textures/check.png");
    Shape.setTexture(&Texture);
}

ShowCandidatesCheckBox::ShowCandidatesCheckBox() {
    Create();
}
