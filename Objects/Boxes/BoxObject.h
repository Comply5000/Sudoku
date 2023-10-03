//
// Created by Wojtek on 03.10.2023.
//

#ifndef SUDOKU_BOXOBJECT_H
#define SUDOKU_BOXOBJECT_H


#include "../Abstractions/BaseObject.h"
#include <array>

class BoxObject : public BaseObject {
public:
    static sf::Color* _greyColor;
    static sf::Texture Textures[10];
public:
    static std::array<std::array<BoxObject, 9>, 9> InitBoxes();
    void SetWhiteColor();
    void SetGreyColor();
    void SetNumberTexture(int number);
};


#endif //SUDOKU_BOXOBJECT_H
