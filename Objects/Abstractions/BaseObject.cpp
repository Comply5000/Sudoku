//
// Created by Wojtek on 02.10.2023.
//

#include "BaseObject.h"
#include "../../Shared/CustomColors.h"


void BaseObject::Create() {

}

void BaseObject::SetDefaultTexture() {
    Shape.setTexture(&Texture);
}

void BaseObject::SetSecondTexture() {
    Shape.setTexture(&SecondTexture);
}

bool BaseObject::IsClicked(sf::Vector2f mousePosition, sf::Mouse::Button mouseButton) {
    return Shape.getGlobalBounds().contains(mousePosition) && sf::Mouse::isButtonPressed(mouseButton);
}

bool BaseObject::IsHover(sf::Vector2f mousePosition) {
    return Shape.getGlobalBounds().contains(mousePosition);
}

void BaseObject::SetWhiteColor() {
    Shape.setFillColor(sf::Color::White);
}

void BaseObject::SetGreyColor() {
    Shape.setFillColor(*CustomColors::GreyColor);
}
