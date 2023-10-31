//
// Created by Wojtek on 03.10.2023.
//

#ifndef SUDOKU_DOWNBUTTON_H
#define SUDOKU_DOWNBUTTON_H


#include "../Abstractions/BaseObject.h"

///przycisk do scrolowania przez dostępne metody w dół
class DownButton : public BaseObject {
    void Create() override;

public:
    DownButton();
};


#endif //SUDOKU_DOWNBUTTON_H
