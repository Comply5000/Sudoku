//
// Created by wojci on 04.10.2023.
//

#ifndef SUDOKU_CANDIDATEBOXTEXTURES_H
#define SUDOKU_CANDIDATEBOXTEXTURES_H


#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Texture.hpp>

class CandidateBoxTextures {
public:
    static sf::Color* GreyColor;
    static sf::Texture Textures[10];
    static sf::Texture CheckedTextures[10];

    static void InitCandidateBoxTextures();
};


#endif //SUDOKU_CANDIDATEBOXTEXTURES_H
