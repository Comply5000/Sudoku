#include <iostream>
#include <array>
#include "Sudoku.h"
#include "Extensions/MethodsExtension.h"

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
    CandidateBox::InitCandidateBoxes();
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
}

bool Sudoku::IsRunning() const {
    return _window->isOpen();
}

void Sudoku::Update() {
    IsRunning();
    GetMousePosition();
    PoolEvent();
    HoverMenuButtons();
    ClickMenuButtons();
    ClickBoxes();

    _candidateBoxes = CandidateBox::UpdateCandidates(_numbers, _boxes);
}

void Sudoku::Render() {
    _window->clear();
    _window->draw(_logo->Shape);
    _window->draw(_board->Shape);
    _window->draw(_resetButton->Shape);
    _window->draw(_solveButton->Shape);
    _window->draw(_loadButton->Shape);
    _window->draw(_saveButton->Shape);

    for(int i = 0;i < 9;i++)
    {
        for(int j = 0;j < 9;j++)
        {
            _window->draw(_boxes[i][j].Shape);
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
                    _window->draw(_candidateBoxes[i][j][k].Shape);
                }
            }
        }
    }

    _window->draw(_showCandidatesCheckBox->Shape);
    _window->draw(_upButton->Shape);
    _window->draw(_downButton->Shape);
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
        for (int i = 0;i < 9;i++)
        {
            for (int j = 0;j < 9;j++)
            {
                _boxes[i][j].SetNumberTexture(0);
                _numbers[i][j] = 0;
//                for (int k = 1;k < 10;k++)
//                    this->checkedCand[i][j][k] = false;
            }
        }

//        for (int i = 0;i < 9;i++)
//            for (int j = 0;j < 9;j++)
//                for (int k = 0;k < 10;k++)
//                {
//                    this->candMethod[i][j][k] = false;
//                    this->candMethodDel[i][j][k] = false;
//                }
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
                if (!candidateClicked || !_isCandidatesShow)
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
            _numbers[_checkedBoxCoordinates.Y][_checkedBoxCoordinates.X] = 0;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
        {
            _boxes[_checkedBoxCoordinates.Y][_checkedBoxCoordinates.X].SetNumberTexture(1);
            _numbers[_checkedBoxCoordinates.Y][_checkedBoxCoordinates.X] = 1;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
        {
            _boxes[_checkedBoxCoordinates.Y][_checkedBoxCoordinates.X].SetNumberTexture(2);
            _numbers[_checkedBoxCoordinates.Y][_checkedBoxCoordinates.X] = 2;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
        {
            _boxes[_checkedBoxCoordinates.Y][_checkedBoxCoordinates.X].SetNumberTexture(3);
            _numbers[_checkedBoxCoordinates.Y][_checkedBoxCoordinates.X] = 3;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
        {
            _boxes[_checkedBoxCoordinates.Y][_checkedBoxCoordinates.X].SetNumberTexture(4);
            _numbers[_checkedBoxCoordinates.Y][_checkedBoxCoordinates.X] = 4;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
        {
            _boxes[_checkedBoxCoordinates.Y][_checkedBoxCoordinates.X].SetNumberTexture(5);
            _numbers[_checkedBoxCoordinates.Y][_checkedBoxCoordinates.X] = 5;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
        {
            _boxes[_checkedBoxCoordinates.Y][_checkedBoxCoordinates.X].SetNumberTexture(6);
            _numbers[_checkedBoxCoordinates.Y][_checkedBoxCoordinates.X] = 6;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
        {
            _boxes[_checkedBoxCoordinates.Y][_checkedBoxCoordinates.X].SetNumberTexture(7);
            _numbers[_checkedBoxCoordinates.Y][_checkedBoxCoordinates.X] = 7;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
        {
            _boxes[_checkedBoxCoordinates.Y][_checkedBoxCoordinates.X].SetNumberTexture(8);
            _numbers[_checkedBoxCoordinates.Y][_checkedBoxCoordinates.X] = 8;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9))
        {
            _boxes[_checkedBoxCoordinates.Y][_checkedBoxCoordinates.X].SetNumberTexture(9);
            _numbers[_checkedBoxCoordinates.Y][_checkedBoxCoordinates.X] = 9;
        }
    }
}



