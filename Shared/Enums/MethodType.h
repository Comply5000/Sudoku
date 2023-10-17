//
// Created by wojci on 12.10.2023.
//

#ifndef SUDOKU_METHODTYPE_H
#define SUDOKU_METHODTYPE_H

enum MethodType{
    NoData = 0,
    NakedSingle = 1,
    HiddenSingle = 2,
    LockedCandidate = 3,
    NakedPair = 4,
    NakedTriple = 5,
};

#endif //SUDOKU_METHODTYPE_H
