//
// Created by wojci on 12.10.2023.
//

#ifndef SUDOKU_METHODTEXT_H
#define SUDOKU_METHODTEXT_H


#include <array>
#include <SFML/Graphics/Text.hpp>

class MethodText {
    sf::Text _text;
    static sf::Font _font;

public:
    static std::array<MethodText, 3> InitMethodText();
    sf::Text GetText();
    void SetString(const std::string& value);
};


#endif //SUDOKU_METHODTEXT_H
