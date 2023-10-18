//
// Created by wojci on 12.10.2023.
//

#include "ListMethodButton.h"
#include "MethodButtonTextures.h"

void ListMethodButton::Create()
{
    _shape.setPosition(20.f, 725.f);
    _shape.setSize(sf::Vector2f(200.f, 100.f));
    _texture.loadFromFile("../Objects/MethodObjects/Textures/none.png");
    _shape.setTexture(&this->_texture);
}

ListMethodButton::ListMethodButton()
{
    Create();
}

void ListMethodButton::SetMethodTexture(int number)
{
    _shape.setTexture(&MethodButtonTextures::Textures[number]);
}
