#ifndef SUDOKU_RESETBUTTON_H
#define SUDOKU_RESETBUTTON_H


#include "../Abstractions/BaseObject.h"

///przycisk resetu w menu
class ResetButton : public BaseObject {
    void Create() override;

public:
    ResetButton();
};


#endif //SUDOKU_RESETBUTTON_H
