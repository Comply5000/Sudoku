//
// Created by wojci on 04.10.2023.
//

#ifndef SUDOKU_BOXTEXTURES_H
#define SUDOKU_BOXTEXTURES_H


#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Texture.hpp>

///tekstury pól
class BoxTextures {
public:
    static sf::Texture Textures[10];

    static void InitBoxTextures(); ///inicjacja tekstur numerycznych
};


#endif //SUDOKU_BOXTEXTURES_H
