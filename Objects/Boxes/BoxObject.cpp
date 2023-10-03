//
// Created by Wojtek on 03.10.2023.
//

#include "BoxObject.h"

sf::Color* BoxObject::_greyColor = nullptr;
sf::Texture BoxObject::Textures[10];

std::array<std::array<BoxObject, 9>, 9> BoxObject::InitBoxes() {

    _greyColor = new sf::Color(186, 181, 181);
    for (int i = 0;i < 10;i++)
    {
        std::string t = "../Objects/Boxes/Textures/" + std::to_string(i) + ".png";
        Textures[i].loadFromFile(t);
    }

    std::array<std::array<BoxObject, 9>, 9> boxes;

    int y = 14;
    for (int i = 0;i < 9;i++)
    {
        int x = 14;
        for (int j = 0;j < 9;j++)
        {
            boxes[i][j].Shape.setFillColor(sf::Color::White);
            boxes[i][j].Shape.setSize(sf::Vector2f(70.f, 70.f));
            boxes[i][j].Shape.setPosition(x, y);
            x += 74;
            if (j == 2 || j == 5)
                x += 5;
        }
        y += 74;
        if (i == 2 || i == 5)
            y += 5;
    }

    return boxes;
}

void BoxObject::SetWhiteColor() {
    Shape.setFillColor(sf::Color::White);
}

void BoxObject::SetGreyColor() {
    Shape.setFillColor(*_greyColor);
}

void BoxObject::SetNumberTexture(int number) {
    Shape.setTexture(&Textures[number]);
}


