#include <iostream>
#include <array>
#include "Sudoku.h"
#include "Extensions/MethodsExtension.h"
#include "Objects/Candidates/CandidateBoxTextures.h"
#include "Extensions/FileExtension.h"
#include "Extensions/SolverExtension.h"
#include "Extensions/HelperFunctionsExtension.h"
#include "Shared/Static/EnumsToStrings.h"

void Sudoku::InitWindow() {
    _videoMode.height = 850;
    _videoMode.width = 1000;
    _window = new sf::RenderWindow(_videoMode, "Sudoku solver", sf::Style::Close | sf::Style::Titlebar);
    _window->setFramerateLimit(60);
}

Sudoku::Sudoku() {
    InitWindow();
    _board = new Board();
    _resetButton = new ResetButton();
    _solveButton = new SolveButton();
    _loadButton = new LoadButton();
    _saveButton = new SaveButton();
    _boxes = BoxObject::InitBoxes();
    _showCandidatesCheckBox = new ShowCandidatesCheckBox();
    _upButton = new UpButton();
    _downButton = new DownButton();
    _logo = new Logo();
    _listMethodButton = new ListMethodButton();
    CandidateBoxTextures::InitCandidateBoxTextures();
    _methodButtons = MethodButton::InitMethodButtons();
    _methodTextList = MethodText::InitMethodText();
}

Sudoku::~Sudoku() {
    delete _window;
    delete _board;
    delete _resetButton;
    delete _solveButton;
    delete _loadButton;
    delete _saveButton;
    delete _showCandidatesCheckBox;
    delete _downButton;
    delete _upButton;
    delete _logo;
    delete _listMethodButton;
}

bool Sudoku::IsRunning(){
    return _window->isOpen();
}

void Sudoku::Update() {
    IsRunning();

    _candidateNumbers = MethodsExtension::FindCandidates(_numbers);
    _candidateBoxes = CandidateBox::UpdateCandidates(_numbers, _boxes);
    GetMousePosition();
    PoolEvent();
    HoverMenuButtons();
    ClickMenuButtons();
    ClickBoxes();
    ClickCandidatesAndUpdateColor();
    ClickMethodButtons();
    UpdateMethod();
    UpdateStartPosition();
    ClickMethodText();
}

void Sudoku::Render() {
    _window->clear();
    _window->draw(_logo->GetShape());
    _window->draw(_board->GetShape());
    _window->draw(_resetButton->GetShape());
    _window->draw(_solveButton->GetShape());
    _window->draw(_loadButton->GetShape());
    _window->draw(_saveButton->GetShape());

    for(int i = 0;i < 9;i++)
    {
        for(int j = 0;j < 9;j++)
        {
            _window->draw(_boxes[i][j].GetShape());
        }
    }

    if(_isCandidatesShow)
    {
        for (int i = 0;i < 9;i++)
        {
            for (int j = 0;j < 9;j++)
            {
                for (int k = 0;k < _candidateBoxes[i][j].size();k++)
                {
                    _window->draw(_candidateBoxes[i][j][k].GetShape());
                }
            }
        }
    }

    _window->draw(_showCandidatesCheckBox->GetShape());
    _window->draw(_showCandidatesCheckBox->GetText());
    _window->draw(_upButton->GetShape());
    _window->draw(_downButton->GetShape());
    _window->draw(_listMethodButton->GetShape());

    if(_isMethodListOpen)
        for (auto  & methodButton : _methodButtons)
            _window->draw(methodButton.GetShape());

    for(auto & methodText : _methodTextList)
        _window->draw(methodText.GetText());

    _window->display();
}

sf::Vector2f Sudoku::GetMousePosition() {
    return _window->mapPixelToCoords(sf::Mouse::getPosition(*_window));
}

void Sudoku::PoolEvent() {
    while (_window->pollEvent(_event))
    {
        switch (_event.type)
        {
            case sf::Event::Closed:
                _window->close();
                break;
            case sf::Event::KeyPressed:
                if (_event.key.code == sf::Keyboard::Escape)
                    _window->close();
                break;
            case sf::Event::MouseButtonReleased:
                if(_event.key.code == sf::Mouse::Left)
                    _isAnyButtonPressed = false;
                break;
            case sf::Event::KeyReleased:
                if (_event.key.code != sf::Keyboard::Tab || _event.key.code != sf::Keyboard::Up ||
                        _event.key.code != sf::Keyboard::Down || _event.key.code != sf::Keyboard::Left ||
                        _event.key.code != sf::Keyboard::Right)
                    _isAnyButtonPressed = false;
                break;
        }
    }
}

void Sudoku::HoverMenuButtons() {
    if (_solveButton->IsHover(GetMousePosition()))
        _solveButton->SetSecondTexture();
    else
        _solveButton->SetDefaultTexture();

    if (_resetButton->IsHover(GetMousePosition()))
        _resetButton->SetSecondTexture();
    else
        _resetButton->SetDefaultTexture();

    if (_loadButton->IsHover(GetMousePosition()))
        _loadButton->SetSecondTexture();
    else
        _loadButton->SetDefaultTexture();

    if (_saveButton->IsHover(GetMousePosition()))
        _saveButton->SetSecondTexture();
    else
        _saveButton->SetDefaultTexture();
}

void Sudoku::ClickMenuButtons()
{
    if (_showCandidatesCheckBox->IsClicked(GetMousePosition(), sf::Mouse::Left) && !_isAnyButtonPressed)
    {
        _isAnyButtonPressed = true;
        if (!_isCandidatesShow)
        {
            _isCandidatesShow = true;
            _showCandidatesCheckBox->SetSecondTexture();
        }
        else
        {
            _isCandidatesShow = false;
            _showCandidatesCheckBox->SetDefaultTexture();
        }
    }

    if (_resetButton->IsClicked(GetMousePosition(), sf::Mouse::Left))
    {
        ResetBoard();
    }

    if(_saveButton->IsClicked(GetMousePosition(), sf::Mouse::Left))
    {
        FileExtension::SaveBoard(_numbers);
    }

    if(_loadButton->IsClicked(GetMousePosition(), sf::Mouse::Left))
    {
        ClearIfCandidateSelectedForMethod();
        _numbers = FileExtension::LoadBoard(_numbers);
        UpdateBoxes();
    }

    if(_solveButton->IsClicked(GetMousePosition(), sf::Mouse::Left) && !_isAnyButtonPressed)
    {
        _isAnyButtonPressed = true;
        ClearIfCandidateSelectedForMethod();
        _numbers = SolverExtension::SolveBoard(_numbers);
        UpdateBoxes();
    }
}


void Sudoku::ClickBoxes()
{
    //zaznaczenie pola w kt�re b�dziemy wpisywa� cyfr�
    for (int i = 0;i < 9;i++)
    {
        for (int j = 0;j < 9;j++)
        {
            if (_boxes[i][j].IsClicked(GetMousePosition(), sf::Mouse::Left) && !_isAnyButtonPressed)
            {
                //sprawdza czy zosta� klikn�ty kandydat a nie pole
                bool candidateClicked = false;
                for (int k = 0;k < _candidateBoxes[i][j].size();k++)
                    if (_candidateBoxes[i][j][k].IsHover(GetMousePosition()))
                    {
                        candidateClicked = true;
                        break;
                    }

                //jesli nie zosta� klikni�ty kandydat lub pokazywanie kandydat�w jest wy��czone
                if ((!candidateClicked || !_isCandidatesShow) && !_isMethodListOpen)
                {
                    _isAnyButtonPressed = true;

                    if (_checkedBoxCoordinates.X == j && _checkedBoxCoordinates.Y == i)
                    {
                        _boxes[i][j].SetWhiteColor();
                        _checkedBoxCoordinates.X = -1;
                        _checkedBoxCoordinates.Y = -1;
                    }
                    else if (_checkedBoxCoordinates.X != -1 && _checkedBoxCoordinates.Y != -1)
                    {
                        _boxes[_checkedBoxCoordinates.Y][_checkedBoxCoordinates.X].SetWhiteColor();
                        _boxes[i][j].SetGreyColor();
                        _checkedBoxCoordinates.X = j;
                        _checkedBoxCoordinates.Y = i;
                    }
                    else
                    {
                        _boxes[i][j].SetGreyColor();
                        _checkedBoxCoordinates.X = j;
                        _checkedBoxCoordinates.Y = i;
                    }
                }
            }
        }
    }

    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) && !_isAnyButtonPressed && _window->hasFocus())
    {
        _isAnyButtonPressed = true;
        if (_checkedBoxCoordinates.X == -1 && _checkedBoxCoordinates.Y == -1)
        {
            _boxes[0][0].SetGreyColor();
            _checkedBoxCoordinates.X = 0;
            _checkedBoxCoordinates.Y = 0;
        }
        else if (_checkedBoxCoordinates.X == 8 && _checkedBoxCoordinates.Y != 8)
        {
            _boxes[_checkedBoxCoordinates.Y][_checkedBoxCoordinates.X].SetWhiteColor();
            _checkedBoxCoordinates.X = 0;
            _checkedBoxCoordinates.Y++;
            _boxes[_checkedBoxCoordinates.Y][_checkedBoxCoordinates.X].SetGreyColor();
        }
        else if (_checkedBoxCoordinates.Y == 8 && _checkedBoxCoordinates.X == 8)
        {
            _boxes[_checkedBoxCoordinates.Y][_checkedBoxCoordinates.X].SetWhiteColor();
            _checkedBoxCoordinates.X = 0;
            _checkedBoxCoordinates.Y = 0;
            _boxes[_checkedBoxCoordinates.Y][_checkedBoxCoordinates.X].SetGreyColor();
        }
        else
        {
            _boxes[_checkedBoxCoordinates.Y][_checkedBoxCoordinates.X].SetWhiteColor();
            _checkedBoxCoordinates.X++;
            _boxes[_checkedBoxCoordinates.Y][_checkedBoxCoordinates.X].SetGreyColor();
        }
    }
    else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && !_isAnyButtonPressed && _window->hasFocus())
    {
        _isAnyButtonPressed = true;
        if (_checkedBoxCoordinates.X == -1 && _checkedBoxCoordinates.Y == -1)
        {
            _boxes[0][0].SetGreyColor();
            _checkedBoxCoordinates.X = 0;
            _checkedBoxCoordinates.Y = 0;
        }
        else
        {
            _boxes[_checkedBoxCoordinates.Y][_checkedBoxCoordinates.X].SetWhiteColor();
            _checkedBoxCoordinates.Y--;
            if (_checkedBoxCoordinates.Y < 0)
                _checkedBoxCoordinates.Y = 8;
            _boxes[_checkedBoxCoordinates.Y][_checkedBoxCoordinates.X].SetGreyColor();
        }
    }
    else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && !_isAnyButtonPressed && _window->hasFocus())
    {
        if (_checkedBoxCoordinates.X == -1 && _checkedBoxCoordinates.Y == -1)
        {
            _boxes[0][0].SetGreyColor();
            _checkedBoxCoordinates.X = 0;
            _checkedBoxCoordinates.Y = 0;
        }
        else
        {
            _isAnyButtonPressed = true;
            _boxes[_checkedBoxCoordinates.Y][_checkedBoxCoordinates.X].SetWhiteColor();
            _checkedBoxCoordinates.Y++;
            if (_checkedBoxCoordinates.Y > 8)
                _checkedBoxCoordinates.Y = 0;
            _boxes[_checkedBoxCoordinates.Y][_checkedBoxCoordinates.X].SetGreyColor();
        }
    }
    else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && !_isAnyButtonPressed && _window->hasFocus())
    {
        if (_checkedBoxCoordinates.X == -1 && _checkedBoxCoordinates.Y == -1)
        {
            _boxes[0][0].SetGreyColor();
            _checkedBoxCoordinates.X = 0;
            _checkedBoxCoordinates.Y = 0;
        }
        else
        {
            _isAnyButtonPressed = true;
            _boxes[_checkedBoxCoordinates.Y][_checkedBoxCoordinates.X].SetWhiteColor();
            _checkedBoxCoordinates.X--;
            if (_checkedBoxCoordinates.X < 0)
                _checkedBoxCoordinates.X = 8;
            _boxes[_checkedBoxCoordinates.Y][_checkedBoxCoordinates.X].SetGreyColor();
        }
    }
    else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && !_isAnyButtonPressed && _window->hasFocus())
    {
        if (_checkedBoxCoordinates.X == -1 && _checkedBoxCoordinates.Y == -1)
        {
            _boxes[0][0].SetGreyColor();
            _checkedBoxCoordinates.X = 0;
            _checkedBoxCoordinates.Y = 0;
        }
        else
        {
            _isAnyButtonPressed = true;
            _boxes[_checkedBoxCoordinates.Y][_checkedBoxCoordinates.X].SetWhiteColor();
            _checkedBoxCoordinates.X++;
            if (_checkedBoxCoordinates.X > 8)
                _checkedBoxCoordinates.X = 0;
            _boxes[_checkedBoxCoordinates.Y][_checkedBoxCoordinates.X].SetGreyColor();
        }
    }

    //wypisanie cyfry z klawiatury
    if (_checkedBoxCoordinates.X != -1 && _checkedBoxCoordinates.Y != -1 && _window->hasFocus())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
        {
            _boxes[_checkedBoxCoordinates.Y][_checkedBoxCoordinates.X].SetNumberTexture(0);
            ClearIfCandidateSelectedForMethod();
            _numbers[_checkedBoxCoordinates.Y][_checkedBoxCoordinates.X] = 0;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
        {
            _boxes[_checkedBoxCoordinates.Y][_checkedBoxCoordinates.X].SetNumberTexture(1);
            ClearIfCandidateSelectedForMethod();
            _numbers[_checkedBoxCoordinates.Y][_checkedBoxCoordinates.X] = 1;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
        {
            _boxes[_checkedBoxCoordinates.Y][_checkedBoxCoordinates.X].SetNumberTexture(2);
            ClearIfCandidateSelectedForMethod();
            _numbers[_checkedBoxCoordinates.Y][_checkedBoxCoordinates.X] = 2;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
        {
            _boxes[_checkedBoxCoordinates.Y][_checkedBoxCoordinates.X].SetNumberTexture(3);
            ClearIfCandidateSelectedForMethod();
            _numbers[_checkedBoxCoordinates.Y][_checkedBoxCoordinates.X] = 3;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
        {
            _boxes[_checkedBoxCoordinates.Y][_checkedBoxCoordinates.X].SetNumberTexture(4);
            ClearIfCandidateSelectedForMethod();
            _numbers[_checkedBoxCoordinates.Y][_checkedBoxCoordinates.X] = 4;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
        {
            _boxes[_checkedBoxCoordinates.Y][_checkedBoxCoordinates.X].SetNumberTexture(5);
            ClearIfCandidateSelectedForMethod();
            _numbers[_checkedBoxCoordinates.Y][_checkedBoxCoordinates.X] = 5;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
        {
            _boxes[_checkedBoxCoordinates.Y][_checkedBoxCoordinates.X].SetNumberTexture(6);
            ClearIfCandidateSelectedForMethod();
            _numbers[_checkedBoxCoordinates.Y][_checkedBoxCoordinates.X] = 6;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
        {
            _boxes[_checkedBoxCoordinates.Y][_checkedBoxCoordinates.X].SetNumberTexture(7);
            ClearIfCandidateSelectedForMethod();
            _numbers[_checkedBoxCoordinates.Y][_checkedBoxCoordinates.X] = 7;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
        {
            _boxes[_checkedBoxCoordinates.Y][_checkedBoxCoordinates.X].SetNumberTexture(8);
            ClearIfCandidateSelectedForMethod();
            _numbers[_checkedBoxCoordinates.Y][_checkedBoxCoordinates.X] = 8;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9))
        {
            _boxes[_checkedBoxCoordinates.Y][_checkedBoxCoordinates.X].SetNumberTexture(9);
            ClearIfCandidateSelectedForMethod();
            _numbers[_checkedBoxCoordinates.Y][_checkedBoxCoordinates.X] = 9;
        }
    }
}

void Sudoku::ClickCandidatesAndUpdateColor() {
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            for (int k = 0; k < _candidateBoxes[i][j].size(); k++)
            {
                if (_candidateBoxes[i][j][k].IsClicked(GetMousePosition(), sf::Mouse::Left) && !_isAnyButtonPressed && !_isMethodListOpen)
                {
                    _isAnyButtonPressed = true;

                    if(_isCandidateChecked[i][j][_candidateNumbers[i][j][k]])
                        _isCandidateChecked[i][j][_candidateNumbers[i][j][k]] = false;
                    else
                        _isCandidateChecked[i][j][_candidateNumbers[i][j][k]] = true;
                }

                if (_isCandidateChecked[i][j][_candidateNumbers[i][j][k]])
                    _candidateBoxes[i][j][k].SetCheckedNumberTexture(_candidateNumbers[i][j][k]);
                else
                    _candidateBoxes[i][j][k].SetNumberTexture(_candidateNumbers[i][j][k]);

                if (i == _checkedBoxCoordinates.Y && j == _checkedBoxCoordinates.X)
                    _candidateBoxes[i][j][k].SetGreyColor();
                else
                    _candidateBoxes[i][j][k].SetWhiteColor();
            }
        }
    }
}

void Sudoku::ResetBoard() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            _boxes[i][j].SetNumberTexture(0);
            _numbers[i][j] = 0;
            for (int k = 1;k < 10;k++)
                _isCandidateChecked[i][j][k] = false;
        }
    }

    ClearIfCandidateSelectedForMethod();
}

void Sudoku::UpdateBoxes()
{
    for(int i = 0;i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            _boxes[i][j].SetNumberTexture(_numbers[i][j]);
        }
    }
}

void Sudoku::ClickMethodButtons()
{
    if (!_isMethodListOpen)
    {
        if (_listMethodButton->IsClicked(GetMousePosition(), sf::Mouse::Left) && !_isAnyButtonPressed)
        {
            _isAnyButtonPressed = true;
            _isMethodListOpen = true;
            _listMethodButton->SetDefaultTexture();
        }
    }
    else
    {
        if (_listMethodButton->IsClicked(GetMousePosition(), sf::Mouse::Left) && !_isAnyButtonPressed)
        {
            _isAnyButtonPressed = true;
            _isMethodListOpen = false;
            _methodType = MethodType::NoData;
            _listMethodButton->SetDefaultTexture();


            for (int i = 0;i < 3;i++)
                _methodNumber[i] = i;

            _selectedMethodNumber = -1;
            _startPoint = 0;

            ClearIfCandidateSelectedForMethod();
        }

        for (int i = 0;i < _methodButtons.size(); i++)
        {
            if (_methodButtons[i].IsClicked(GetMousePosition(), sf::Mouse::Left) && !_isAnyButtonPressed)
            {
                _isAnyButtonPressed = true;
                _isMethodListOpen = false;
                _methodType = static_cast<MethodType>(i+1);
                _listMethodButton->SetMethodTexture(i);


                for (int i = 0;i < 3;i++)
                    _methodNumber[i] = i;

                _selectedMethodNumber = -1;
                _startPoint = 0;

                ClearIfCandidateSelectedForMethod();
            }
        }
    }
}

void Sudoku::UpdateMethod()
{
    _methodStringList.clear();
    _methodStringList.shrink_to_fit();

    if (_methodType == MethodType::NoData)
    {
        UpdateMethodTextList();
    }
    if (_methodType == MethodType::NakedSingle)
    {
        _methodSolutions = MethodsExtension::NakedSingle(_numbers);

        for (int m = 0;m < _methodSolutions.size();m++)
        {
            for (int i = 0;i < 9;i++)
            {
                for (int j = 0;j < 9;j++)
                {
                    if (!_methodSolutions[m].Candidates[i][j].empty())
                    {
                        std::string text = std::to_string(m + 1) + ". The cell R" + std::to_string(i+1) + "C" + std::to_string(j+1) + " can contain only the value " + std::to_string(_methodSolutions[m].Candidates[i][j][0]);
                        _methodStringList.push_back(text);
                    }
                }
            }
        }
    }
    if(_methodType == MethodType::HiddenSingle)
    {
        _methodSolutions = MethodsExtension::HiddenSingle(_numbers);

        for (int m = 0;m < _methodSolutions.size();m++)
        {
            for (int i = 0;i < 9;i++)
            {
                for (int j = 0;j < 9;j++)
                {
                    if (!_methodSolutions[m].Candidates[i][j].empty())
                    {
                        std::string text = std::to_string(m + 1) + ". The cell R" + std::to_string(i + 1) + "C" + std::to_string(j + 1) + " can contain only the value " + std::to_string(_methodSolutions[m].Candidates[i][j][0]);
                        _methodStringList.push_back(text);
                    }
                }
            }
        }
    }
    if(_methodType == MethodType::LockedCandidate)
    {
        _methodSolutions = MethodsExtension::LockedCandidate(_numbers);

        for (int m = 0; m < _methodSolutions.size(); m++)
        {
            std::string text = std::to_string(m + 1) + ". Locket candidate in " +
                    HelperFunctionsExtension::EnumToString( _methodSolutions[m].StructureType, EnumsToStrings::StructureTypes);
            _methodStringList.push_back(text);
        }
    }
    if(_methodType == MethodType::NakedPair)
    {
        _methodSolutions = MethodsExtension::NakedPair(_numbers);

        for (int m = 0;m < _methodSolutions.size();m++)
        {
            std::vector<std::string> box;
            for (int i = 0;i < 9;i++)
            {
                for (int j = 0;j < 9;j++)
                {
                    if (!_methodSolutions[m].Candidates[i][j].empty())
                    {
                        std::string t = "R" + std::to_string(i + 1) + "C" + std::to_string(j + 1);
                        box.push_back(t);
                    }
                }
            }
            std::string text = std::to_string(m + 1) + ". "+box[0]+" and "+box[1]+ " create pair in "+
                    HelperFunctionsExtension::EnumToString( _methodSolutions[m].StructureType, EnumsToStrings::StructureTypes);
            _methodStringList.push_back(text);
        }
    }
    if(_methodType == MethodType::NakedTriple)
    {
        _methodSolutions = MethodsExtension::NakedTriple(_numbers);

        for (int m = 0;m < _methodSolutions.size();m++)
        {
            std::vector<std::string> box;
            for (int i = 0;i < 9;i++)
            {
                for (int j = 0;j < 9;j++)
                {
                    if (!_methodSolutions[m].Candidates[i][j].empty())
                    {
                        std::string t = "R" + std::to_string(i + 1) + "C" + std::to_string(j + 1);
                        box.push_back(t);
                    }
                }
            }
            std::string text = std::to_string(m + 1) + ". " + box[0] + ", " + box[1] + " and " + box[2] + " create triple in " +
                    HelperFunctionsExtension::EnumToString( _methodSolutions[m].StructureType, EnumsToStrings::StructureTypes);
            _methodStringList.push_back(text);
        }
    }
    if(_methodType == MethodType::LockedPair)
    {
        _methodSolutions = MethodsExtension::LockedPair(_numbers);

        for (int m = 0; m < _methodSolutions.size(); m++)
        {
            std::vector<std::string> box;
            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++)
                {
                    if (!_methodSolutions[m].Candidates[i][j].empty())
                    {
                        std::string t = "R" + std::to_string(i + 1) + "C" + std::to_string(j + 1);
                        box.push_back(t);
                    }
                }
            }
            std::string text = std::to_string(m + 1) + ". " + box[0] + " and " + box[1] + " create hidden pair in " +
                    HelperFunctionsExtension::EnumToString( _methodSolutions[m].StructureType, EnumsToStrings::StructureTypes);
            _methodStringList.push_back(text);
        }
    }
    if(_methodType == MethodType::XWing)
    {
        _methodSolutions = MethodsExtension::XWing(_numbers);

        for (int m = 0; m < _methodSolutions.size(); m++)
        {
            int number;
            std::vector<std::string> box;
            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++)
                {
                    if (!_methodSolutions[m].Candidates[i][j].empty())
                    {
                        number = _methodSolutions[m].Candidates[i][j][0];
                        std::string t;
                        if (_methodSolutions[m].StructureType == StructureType::Row)
                            t = std::to_string(i + 1);
                        else if (_methodSolutions[m].StructureType == StructureType::Column)
                            t = std::to_string(j + 1);
                        box.push_back(t);
                        break;
                    }
                }
            }
            auto structureTypeName = HelperFunctionsExtension::EnumToString( _methodSolutions[m].StructureType, EnumsToStrings::StructureTypes);
            structureTypeName[0] = std::toupper(structureTypeName[0]);
            std::string text = std::to_string(m + 1) + ". "+
                    structureTypeName
                    + " " + box[0] + " and " + box[1] + " create X-Wing with number " + std::to_string(number);
            _methodStringList.push_back(text);
        }
    }
    UpdateMethodTextList();
}

void Sudoku::UpdateMethodTextList()
{
    int a = 0;
    for (int i = _startPoint; i < _startPoint + 3; i++)
    {
        if (_methodStringList.size() > i)
            _methodTextList[a].SetString(_methodStringList[i]);
        else
            _methodTextList[a].SetString("");
        a++;
    }
}

void Sudoku::UpdateStartPosition()
{
    if (_methodStringList.size() > 3)
    {
        if (_downButton->IsClicked(GetMousePosition(), sf::Mouse::Left) && !_isAnyButtonPressed)
        {
            _isAnyButtonPressed = true;
            if (_startPoint < _methodStringList.size() - 3)
            {
                _startPoint++;
                for (int i = 0;i < 3;i++)
                    _methodNumber[i]++;
            }
        }
        else if (_upButton->IsClicked(GetMousePosition(), sf::Mouse::Left) && !_isAnyButtonPressed)
        {
            _isAnyButtonPressed = true;
            if (_startPoint > 0)
            {
                _startPoint--;
                for (int i = 0;i < 3;i++)
                    _methodNumber[i]--;
            }
        }
    }
}

void Sudoku::ClickMethodText()
{
    for (int l = 0;l < 3;l++)
    {
        if (_methodTextList[l].IsClicked(GetMousePosition(), sf::Mouse::Left))
        {
            ClearIfCandidateSelectedForMethod();

            _selectedMethodNumber = _methodNumber[l];

            for (int i = 0;i < 9;i++)
                for (int j = 0;j < 9;j++)
                    for (int k = 0;k < _candidateNumbers[i][j].size();k++)
                    {
                        if (HelperFunctionsExtension::IsContained(_methodSolutions[_selectedMethodNumber].Candidates[i][j], _candidateNumbers[i][j][k]))
                            _isCandidateSelectedForMethod[i][j][k] = true;
                        if (_methodType != MethodType::NakedSingle && _methodType != MethodType::HiddenSingle && HelperFunctionsExtension::IsContained(_methodSolutions[_selectedMethodNumber].CandidatesToDelete[i][j], _candidateNumbers[i][j][k]))
                            _isCandidateSelectedForMethodToDelete[i][j][k] = true;
                    }
        }
    }

    for (int i = 0;i < 3;i++)
    {
        if (_methodNumber[i] == _selectedMethodNumber)
            _methodTextList[i].SetGreenColor();
        else
            _methodTextList[i].SetWhiteColor();
    }

    for (int i = 0;i < 9;i++)
        for (int j = 0;j < 9;j++)
            for (int k = 0;k < 10;k++)
            {
                if (_isCandidateSelectedForMethod[i][j][k])
                    _candidateBoxes[i][j][k].SetGreenColor();
                if (_isCandidateSelectedForMethodToDelete[i][j][k])
                    _candidateBoxes[i][j][k].SetRedColor();
            }
}

void Sudoku::ClearIfCandidateSelectedForMethod()
{
    for (int i = 0;i < 9;i++)
        for (int j = 0;j < 9;j++)
            for (int k = 0;k < 10;k++)
            {
                _isCandidateSelectedForMethod[i][j][k] = false;
                _isCandidateSelectedForMethodToDelete[i][j][k] = false;
            }
    _selectedMethodNumber = -1;
}




