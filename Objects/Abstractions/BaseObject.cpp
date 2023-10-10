//
// Created by Wojtek on 02.10.2023.
//

#include "BaseObject.h"
#include "../../Shared/CustomColors.h"

void BaseObject::SetDefaultTexture() {
    _shape.setTexture(&_texture);
}

void BaseObject::SetSecondTexture() {
    _shape.setTexture(&_secondTexture);
}

bool BaseObject::IsClicked(sf::Vector2f mousePosition, sf::Mouse::Button mouseButton) {
    return _shape.getGlobalBounds().contains(mousePosition) && sf::Mouse::isButtonPressed(mouseButton);
}

bool BaseObject::IsHover(sf::Vector2f mousePosition) {
    return _shape.getGlobalBounds().contains(mousePosition);
}

void BaseObject::SetWhiteColor() {
    _shape.setFillColor(sf::Color::White);
}

void BaseObject::SetGreyColor() {
    _shape.setFillColor(*CustomColors::GreyColor);
}

sf::RectangleShape BaseObject::GetShape() {
    return _shape;
}
