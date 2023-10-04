//
// Created by wojci on 04.10.2023.
//

#include "BoxTextures.h"

sf::Texture BoxTextures::Textures[10];

void BoxTextures::InitBoxTextures()
{
    for (int i = 0;i < 10;i++)
    {
        std::string t = "../Objects/Boxes/Textures/" + std::to_string(i) + ".png";
        Textures[i].loadFromFile(t);
    }
}
