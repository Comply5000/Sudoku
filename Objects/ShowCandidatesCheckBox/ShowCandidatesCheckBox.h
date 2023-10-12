//
// Created by Wojtek on 03.10.2023.
//

#ifndef SUDOKU_SHOWCANDIDATESCHECKBOX_H
#define SUDOKU_SHOWCANDIDATESCHECKBOX_H


#include "../Abstractions/BaseObject.h"

class ShowCandidatesCheckBox : public BaseObject {
    void Create() override;
    sf::Text _text;
    sf::Font _font;

public:
    ShowCandidatesCheckBox();
    sf::Text GetText();
};


#endif //SUDOKU_SHOWCANDIDATESCHECKBOX_H
