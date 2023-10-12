//
// Created by wojci on 12.10.2023.
//

#ifndef SUDOKU_LISTMETHODBUTTON_H
#define SUDOKU_LISTMETHODBUTTON_H


#include "../Abstractions/BaseObject.h"

class ListMethodButton : public BaseObject {
    void Create() override;

public:
    ListMethodButton();
    void SetMethodTexture(int number);
};


#endif //SUDOKU_LISTMETHODBUTTON_H
