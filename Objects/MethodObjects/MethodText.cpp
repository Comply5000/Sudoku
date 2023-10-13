//
// Created by wojci on 12.10.2023.
//

#include "MethodText.h"

sf::Font MethodText::_font;

std::array<MethodText, 3> MethodText::InitMethodText()
{
    std::array<MethodText, 3> methodTextList;
    _font.loadFromFile("../Shared/Fonts/arial.ttf");

    for (int i = 0;i < 3;i++)
    {
        methodTextList[i]._text.setFont(_font);
        methodTextList[i]._text.setPosition(sf::Vector2f(270.f, 720.f+i*35));
        methodTextList[i]._text.setCharacterSize(32);
        methodTextList[i]._text.setFillColor(sf::Color::White);
    }

    return methodTextList;
}

sf::Text MethodText::GetText() {
    return _text;
}

void MethodText::SetString(const std::string& value) {
    _text.setString(value);
}

bool MethodText::IsClicked(sf::Vector2f mousePosition, sf::Mouse::Button mouseButton) {
    return _text.getGlobalBounds().contains(mousePosition) && sf::Mouse::isButtonPressed(mouseButton);
}

void MethodText::SetWhiteColor() {
    _text.setFillColor(sf::Color::White);
}

void MethodText::SetGreenColor() {
    _text.setFillColor(sf::Color::Green);
}
