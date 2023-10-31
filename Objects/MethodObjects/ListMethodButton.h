//
// Created by wojci on 12.10.2023.
//

#ifndef SUDOKU_LISTMETHODBUTTON_H
#define SUDOKU_LISTMETHODBUTTON_H


#include "../Abstractions/BaseObject.h"

///przycisk z rozwijanym menu z metodami
class ListMethodButton : public BaseObject {
    void Create() override;

public:
    ListMethodButton();
    void SetMethodTexture(int number); ///ustawienie tekstury w zależności od wybranej metody
};


#endif //SUDOKU_LISTMETHODBUTTON_H
