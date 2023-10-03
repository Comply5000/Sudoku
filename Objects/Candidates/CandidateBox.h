//
// Created by Wojtek on 03.10.2023.
//

#ifndef SUDOKU_CANDIDATEBOX_H
#define SUDOKU_CANDIDATEBOX_H


#include "../Abstractions/BaseObject.h"
#include "../../Extensions/MethodsExtension.h"
#include "../Boxes/BoxObject.h"
#include <array>
#include <vector>

class CandidateBox : public BaseObject{
    static sf::Color* _greyColor;
    static sf::Texture Textures[10];
    static sf::Texture CheckedTextures[10];

public:
    static void InitCandidateBoxes();
    static std::array<std::array<std::vector<CandidateBox>, 9>, 9> UpdateCandidates(std::array<std::array<int, 9>, 9> numbers,std::array<std::array<BoxObject, 9>, 9> boxes);
};


#endif //SUDOKU_CANDIDATEBOX_H
