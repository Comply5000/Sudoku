//
// Created by wojci on 04.10.2023.
//

#include "BoxTextures.h"

sf::Color* BoxTextures::GreyColor = nullptr;
sf::Texture BoxTextures::Textures[10];

void BoxTextures::InitBoxTextures()
{
    GreyColor = new sf::Color(186, 181, 181);
    for (int i = 0;i < 10;i++)
    {
        std::string t = "../Objects/Boxes/Textures/" + std::to_string(i) + ".png";
        Textures[i].loadFromFile(t);
    }
}
