//
// Created by Wojtek on 02.10.2023.
//

#ifndef SUDOKU_SOLVEBUTTON_H
#define SUDOKU_SOLVEBUTTON_H


#include "../Abstractions/BaseObject.h"

///przycisk do rozwiuązywania planszy
class SolveButton : public BaseObject {
    void Create() override;

public:
    SolveButton();
};


#endif //SUDOKU_SOLVEBUTTON_H
