//
// Created by Wojtek on 03.10.2023.
//

#include "ShowCandidatesCheckBox.h"

void ShowCandidatesCheckBox::Create() {
    _shape.setPosition(750.f, 625.f);
    _shape.setSize(sf::Vector2f(50.f, 50.f));
    _texture.loadFromFile("../Objects/ShowCandidatesCheckBox/Textures/check2.png");
    _secondTexture.loadFromFile("../Objects/ShowCandidatesCheckBox/Textures/check.png");
    _shape.setTexture(&_texture);

    _font.loadFromFile("../Shared/Fonts/arial.ttf");
    _text.setFont(_font);
    _text.setString("Candidates");
    _text.setPosition(sf::Vector2f(810.f, 626.f));
    _text.setCharacterSize(35);
    _text.setFillColor(sf::Color::White);
}

ShowCandidatesCheckBox::ShowCandidatesCheckBox() {
    Create();
}

sf::Text ShowCandidatesCheckBox::GetText() {
    return _text;
}
