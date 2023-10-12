//
// Created by wojci on 12.10.2023.
//

#include "MethodButtonTextures.h"

sf::Texture MethodButtonTextures::Textures[7];

void MethodButtonTextures::InitMethodButtonTextures()
{
    Textures[0].loadFromFile("../Objects/MethodObjects/Textures/nakedSingle.png");
    Textures[1].loadFromFile("../Objects/MethodObjects/Textures/hiddenSingle.png");
    Textures[2].loadFromFile("../Objects/MethodObjects/Textures/lockedCandidate.png");
    Textures[3].loadFromFile("../Objects/MethodObjects/Textures/nakedPair.png");
    Textures[4].loadFromFile("../Objects/MethodObjects/Textures/nakedTriple.png");
    Textures[5].loadFromFile("../Objects/MethodObjects/Textures/hiddenPair.png");
    Textures[6].loadFromFile("../Objects/MethodObjects/Textures/xWing.png");
}
