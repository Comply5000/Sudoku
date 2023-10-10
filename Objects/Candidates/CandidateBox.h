//
// Created by Wojtek on 03.10.2023.
//

#ifndef SUDOKU_CANDIDATEBOX_H
#define SUDOKU_CANDIDATEBOX_H


#include "../Abstractions/BaseObject.h"
#include "../../Extensions/MethodsExtension.h"
#include "../Boxes/BoxObject.h"
#include <array>
#include <vector>

class CandidateBox : public BaseObject{
public:
    void Create() override;
    static std::array<std::array<std::vector<CandidateBox>, 9>, 9> UpdateCandidates(std::array<std::array<int, 9>, 9> numbers,std::array<std::array<BoxObject, 9>, 9> boxes);
    void SetNumberTexture(int number);
    void SetCheckedNumberTexture(int number);
};


#endif //SUDOKU_CANDIDATEBOX_H
