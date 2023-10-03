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
#include "Objects/MethodObjects/ShowCandidatesCheckBox.h"
#include "Objects/MethodObjects/UpButton.h"
#include "Objects/MethodObjects/DownButton.h"
#include "Objects/Logo/Logo.h"
#include "Objects/Candidates/CandidateBox.h"
#include <array>

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
    std::array<std::array<std::vector<CandidateBox>, 9>, 9> _candidateBoxes;


    //functions
    void InitWindow();
    sf::Vector2f GetMousePosition();
    void PoolEvent();

    void HoverMenuButtons();
    void ClickMenuButtons();
    void ClickBoxes();

public:
    Sudoku();
    ~Sudoku();
    bool IsRunning() const;
    void Update();
    void Render();

};


#endif //SUDOKU_SUDOKU_H
