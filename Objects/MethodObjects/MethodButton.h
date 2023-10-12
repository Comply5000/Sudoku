//
// Created by wojci on 12.10.2023.
//

#ifndef SUDOKU_METHODBUTTON_H
#define SUDOKU_METHODBUTTON_H


#include "../Abstractions/BaseObject.h"
#include "MethodButtonTextures.h"

class MethodButton : public BaseObject{
    void Create() override;

public:
    static std::array<MethodButton, 7> InitMethodButtons();
};


#endif //SUDOKU_METHODBUTTON_H
