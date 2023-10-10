//
// Created by Wojtek on 03.10.2023.
//

#include "BoxObject.h"
#include "BoxTextures.h"
#include "../../Shared/Static/CustomColors.h"

std::array<std::array<BoxObject, 9>, 9> BoxObject::InitBoxes() {

    BoxTextures::InitBoxTextures();

    std::array<std::array<BoxObject, 9>, 9> boxes;

    int y = 14;
    for (int i = 0;i < 9;i++)
    {
        int x = 14;
        for (int j = 0;j < 9;j++)
        {
            boxes[i][j]._shape.setFillColor(sf::Color::White);
            boxes[i][j]._shape.setSize(sf::Vector2f(70.f, 70.f));
            boxes[i][j]._shape.setPosition(x, y);
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

void BoxObject::SetNumberTexture(int number) {
    _shape.setTexture(&BoxTextures::Textures[number]);
}

void BoxObject::Create() {

}


