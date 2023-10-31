//
// Created by Wojtek on 03.10.2023.
//

#ifndef SUDOKU_METHODSEXTENSION_H
#define SUDOKU_METHODSEXTENSION_H

#include <array>
#include <vector>
#include <algorithm>
#include "../DTOs/MethodSolutionDto.h"

///statuczna klasa do obsługi metod rozwiązywania sudoku
class MethodsExtension {
public:
    static std::array<std::array<std::vector<int>, 9>, 9> FindCandidates(std::array<std::array<int,9>,9> numbers); ///zwrócenie listy kandydatów dla danej planszy
    static std::vector<MethodSolutionDto> NakedSingle(std::array<std::array<int,9>,9> numbers);
    static std::vector<MethodSolutionDto> HiddenSingle(std::array<std::array<int,9>,9> numbers);
    static std::vector<MethodSolutionDto> LockedCandidate(std::array<std::array<int,9>,9> numbers);
    static std::vector<MethodSolutionDto> NakedPair(std::array<std::array<int,9>,9> numbers);
    static std::vector<MethodSolutionDto> NakedTriple(std::array<std::array<int,9>,9> numbers);
    static std::vector<MethodSolutionDto> HiddenPair(std::array<std::array<int,9>,9> numbers);
    static std::vector<MethodSolutionDto> XWing(std::array<std::array<int,9>,9> numbers);
};


#endif //SUDOKU_METHODSEXTENSION_H
