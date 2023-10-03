//
// Created by Wojtek on 02.10.2023.
//

#ifndef SUDOKU_SAVEBUTTON_H
#define SUDOKU_SAVEBUTTON_H


#include "../Abstractions/BaseObject.h"

class SaveButton : public BaseObject {
    void Create() override;

public:
    SaveButton();
};


#endif //SUDOKU_SAVEBUTTON_H
