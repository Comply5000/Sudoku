//
// Created by Wojtek on 03.10.2023.
//

#ifndef SUDOKU_LOGO_H
#define SUDOKU_LOGO_H


#include "../Abstractions/BaseObject.h"

///logo aplikacji
class Logo : public BaseObject{
    void Create() override;

public:
    Logo();
};


#endif //SUDOKU_LOGO_H
