#ifndef SUDOKU_BOARD_H
#define SUDOKU_BOARD_H

#include "../Abstractions/BaseObject.h"

class Board : public BaseObject {
    void Create() override;

public:
    Board();
};


#endif //SUDOKU_BOARD_H
