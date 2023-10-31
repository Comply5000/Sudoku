//
// Created by Wojtek on 03.10.2023.
//

#ifndef SUDOKU_UPBUTTON_H
#define SUDOKU_UPBUTTON_H


#include "../Abstractions/BaseObject.h"

///przycisk do scrolowania przez dostępne metody w górę
class UpButton : public BaseObject {
    void Create() override;

public:
    UpButton();
};


#endif //SUDOKU_UPBUTTON_H
