//
// Created by wojci on 04.10.2023.
//

#include "CandidateBoxTextures.h"

sf::Texture CandidateBoxTextures::Textures[10];
sf::Texture CandidateBoxTextures::CheckedTextures[10];

void CandidateBoxTextures::InitCandidateBoxTextures()
{
    for (int i = 1; i < 10; i++)
    {
        std::string t = "../Objects/Candidates/Textures/Default/" + std::to_string(i) + ".png";
        Textures[i].loadFromFile(t);
        t = "../Objects/Candidates/Textures/Checked/" + std::to_string(i) + ".png";
        CheckedTextures[i].loadFromFile(t);
    }
}
