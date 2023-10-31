//
// Created by Wojtek on 03.10.2023.
//

#ifndef SUDOKU_BOXOBJECT_H
#define SUDOKU_BOXOBJECT_H


#include "../Abstractions/BaseObject.h"
#include <array>

/// pole na planszy
class BoxObject : public BaseObject {
public:
    void Create() override;
    static std::array<std::array<BoxObject, 9>, 9> InitBoxes(); ///inicjacja pol numerycznych
    void SetNumberTexture(int number); ///zmiana tekstury w zależności od liczby
};


#endif //SUDOKU_BOXOBJECT_H
