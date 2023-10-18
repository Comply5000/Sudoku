//
// Created by wojci on 12.10.2023.
//

#include "MethodButton.h"

void MethodButton::Create() {}

std::array<MethodButton, 7> MethodButton::InitMethodButtons()
{
    MethodButtonTextures::InitMethodButtonTextures();

    std::array<MethodButton, 7> methodButtons;

    for (int i = 0;i < methodButtons.size();i++)
    {
        methodButtons[i]._shape.setPosition(20.f, 625.f-(i*100));
        methodButtons[i]._shape.setSize(sf::Vector2f(200.f, 100.f));
        methodButtons[i]._shape.setTexture(&MethodButtonTextures::Textures[i]);
    }

    return methodButtons;
}
