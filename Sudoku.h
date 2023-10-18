#ifndef SUDOKU_SUDOKU_H
#define SUDOKU_SUDOKU_H

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include "Objects/Board/Board.h"
#include "Objects/ResetButton/ResetButton.h"
#include "Objects/SolveButton/SolveButton.h"
#include "Objects/LoadButton/LoadButton.h"
#include "Objects/SaveButton/SaveButton.h"
#include "Objects/Boxes/BoxObject.h"
#include "DTOs/Coordinates.h"
#include "Objects/MethodObjects/UpButton.h"
#include "Objects/MethodObjects/DownButton.h"
#include "Objects/Logo/Logo.h"
#include "Objects/Candidates/CandidateBox.h"
#include "Objects/MethodObjects/ListMethodButton.h"
#include "Objects/MethodObjects/MethodButton.h"
#include "Objects/ShowCandidatesCheckBox/ShowCandidatesCheckBox.h"
#include "Shared/Enums/MethodType.h"
#include "Objects/MethodObjects/MethodText.h"
#include <array>
#include <cctype>

class Sudoku {

    //variables
    sf::RenderWindow* _window;
    sf::VideoMode _videoMode;
    sf::Event _event;
    bool _isAnyButtonPressed = false;
    Coordinates _checkedBoxCoordinates;
    std::array<std::array<int,9>,9> _numbers = {};
    bool _isCandidatesShow = false;

    //objects
    Board* _board;
    ResetButton* _resetButton;
    SolveButton* _solveButton;
    LoadButton* _loadButton;
    SaveButton* _saveButton;
    std::array<std::array<BoxObject, 9>, 9> _boxes;
    ShowCandidatesCheckBox* _showCandidatesCheckBox;
    UpButton* _upButton;
    DownButton* _downButton;
    Logo* _logo;

    //method logic
    ListMethodButton* _listMethodButton;
    std::array<MethodButton, 7> _methodButtons;
    bool _isMethodListOpen = false;
    std::vector<std::string> _methodStringList;
    std::array<MethodText, 3> _methodTextList;
    std::array<int, 3> _methodNumber;
    MethodType _methodType;
    int _startPoint = 0;
    int _selectedMethodNumber = -1;
    std::vector<MethodSolutionDto> _methodSolutions;


    //candidates logic
    std::array<std::array<std::vector<CandidateBox>, 9>, 9> _candidateBoxes;
    bool _isCandidateChecked[9][9][10] = {};
    bool _isCandidateSelectedForMethod[9][9][10] = {};
    bool _isCandidateSelectedForMethodToDelete[9][9][10] = {};
    std::array<std::array<std::vector<int>, 9>, 9> _candidateNumbers;



    //functions
    void InitWindow();
    sf::Vector2f GetMousePosition();
    void PoolEvent();
    void ResetBoard();

    void HoverMenuButtons();
    void ClickMenuButtons();
    void ClickBoxes();
    void ClickCandidatesAndUpdateColor();
    void UpdateBoxes();
    void ClickMethodButtons();
    void UpdateMethod();
    void UpdateMethodTextList();
    void UpdateStartPosition();
    void ClickMethodText();
    void ClearIsCandidateSelectedForMethod();

public:
    Sudoku();
    ~Sudoku();
    bool IsRunning() const;
    void Update();
    void Render();

};


#endif //SUDOKU_SUDOKU_H
