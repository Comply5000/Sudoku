//
// Created by Wojtek on 03.10.2023.
//

#include "MethodsExtension.h"
#include "HelperFunctionsExtension.h"

std::array<std::array<std::vector<int>, 9>, 9> MethodsExtension::FindCandidates(std::array<std::array<int, 9>, 9> numbers)
{
    std::array<std::array<std::vector<int>, 9>, 9> candidates;

    for (int i = 0;i < 9;i++)
    {
        for (int j = 0;j < 9;j++)
        {
            if (numbers[i][j] != 0)
                candidates[i][j].push_back(10);
            else
            {
                for (int k = 1;k <= 9;k++)
                {
                    bool exist = false;
                    for (int x = 0;x < 9;x++)
                    {
                        if (k == numbers[i][x])
                        {
                            exist = true;
                            break;
                        }
                    }
                    for (int x = 0;x < 9;x++)
                    {
                        if (k == numbers[x][j])
                        {
                            exist = true;
                            break;
                        }
                    }
                    if (HelperFunctionsExtension::IsInSquare(numbers,i, j, k))
                        exist = true;

                    if (!exist)
                        candidates[i][j].push_back(k);
                }
            }
        }
    }
    return candidates;
}

std::vector<MethodSolutionDto> MethodsExtension::NakedSingle(std::array<std::array<int, 9>, 9> numbers)
{
    auto candidates = FindCandidates(numbers);
    std::vector<MethodSolutionDto> methodSolutions;

    for (int i = 0;i < 9;i++)
    {
        for (int j = 0;j < 9;j++)
        {
            std::array<std::array<std::vector<int>, 9>, 9 > singleMethod;
            if (candidates[i][j].size() == 1 && candidates[i][j][0] != 10) //szukamy pola które zawiera tylko 1 kandydata
            {
                singleMethod[i][j].push_back(candidates[i][j][0]);
                MethodSolutionDto solution;
                solution.Candidates = singleMethod;
                methodSolutions.push_back(solution);
            }
        }
    }

    return methodSolutions;
}

std::vector<MethodSolutionDto> MethodsExtension::HiddenSingle(std::array<std::array<int, 9>, 9> numbers)
{
    auto candidates = FindCandidates(numbers);
    std::vector<MethodSolutionDto> methodSolutions;

    for (int i = 0;i < 9;i++) //iteracja po wierszach
    {
        for (int j = 0;j < 9;j++)
        {
            if (!candidates[i][j].empty() && candidates[i][j][0] != 10)// pole nie jest uzupełnione
            {
                for (int k = 0;k < candidates[i][j].size();k++) //iteracja po kandydatach w polu
                {
                    std::array<std::array<std::vector<int>, 9>, 9 > singleMethod;
                    int n = 0;
                    for (int a = 0;a < 9;a++) //ponowna iteracja po wszystkich polach w wierszu aby sparawdziæ ile jest tych kandydatów
                        if (candidates[i][a][0] != 10 && HelperFunctionsExtension::IsContained(candidates[i][a], candidates[i][j][k]))
                            n++;
                    if (n == 1) //jezeli jest tylko 1 kandydat: uzupe³nienie bloku tym kandydatem
                    {
                        singleMethod[i][j].push_back(candidates[i][j][k]);
                        MethodSolutionDto solution;
                        solution.Candidates = singleMethod;
                        //solution.StructureType = BoardStructureType::Row;
                        methodSolutions.push_back(solution);
                    }
                }
            }
        }
    }

    //to samo tylko kolumny
    for (int j = 0;j < 9;j++)
    {
        for (int i = 0;i < 9;i++)
        {
            if (!candidates[i][j].empty() && candidates[i][j][0] != 10)
            {
                for (int k = 0;k < candidates[i][j].size();k++)
                {
                    std::array<std::array<std::vector<int>, 9>, 9 > singleMethod;
                    int n = 0;
                    for (int a = 0;a < 9;a++)
                        if (candidates[a][j][0] != 10 && HelperFunctionsExtension::IsContained(candidates[a][j], candidates[i][j][k]))
                            n++;
                    if (n == 1)
                    {
                        singleMethod[i][j].push_back(candidates[i][j][k]);
                        MethodSolutionDto solution;
                        solution.Candidates = singleMethod;
                        //solution.StructureType = BoardStructureType::Column;
                        methodSolutions.push_back(solution);
                    }
                }
            }
        }
    }

    for (int y = 0;y <= 6;y += 3)// x,y iteracja po blokach
    {
        for (int x = 0;x <= 6;x += 3)
        {
            for (int i = y;i < y + 3;i++) //iteracja po polach w ka¿dym bloku
            {
                for (int j = x;j < x + 3;j++)
                {
                    if (!candidates[i][j].empty() && candidates[i][j][0] != 10)
                    {
                        for (int k = 0;k < candidates[i][j].size();k++)
                        {
                            std::array<std::array<std::vector<int>, 9>, 9 > singleMethod;
                            int n = 0;
                            for (int a = y;a < y + 3;a++)
                                for (int b = x;b < x + 3;b++)
                                    if (candidates[a][b][0] != 10 && HelperFunctionsExtension::IsContained(candidates[a][b], candidates[i][j][k]))
                                        n++;
                            if (n == 1)
                            {
                                singleMethod[i][j].push_back(candidates[i][j][k]);
                                MethodSolutionDto solution;
                                solution.Candidates = singleMethod;
                                //solution.StructureType = BoardStructureType::Square;
                                methodSolutions.push_back(solution);
                            }
                        }
                    }
                }
            }
        }
    }

    std::sort(methodSolutions.begin(), methodSolutions.end());
    auto uniqueMethodSolutions = std::unique(methodSolutions.begin(), methodSolutions.end());

    methodSolutions.erase(uniqueMethodSolutions, methodSolutions.end());

    return methodSolutions;
}

std::vector<MethodSolutionDto> MethodsExtension::LockedCandidate(std::array<std::array<int, 9>, 9> numbers)
{
    auto candidates = FindCandidates(numbers);
    std::vector<MethodSolutionDto> methodSolutions;

    for (int i = 0;i < 9;i++) //iteracja po wierszach
    {
        for (int j = 0;j < 9;j++)
        {
            if (!candidates[i][j].empty() && candidates[i][j][0] != 10)
            {
                for (int k = 0;k < candidates[i][j].size();k++) //itreacja po kandydatach w polach
                {
                    int exist = 0, line;
                    for (int a = 0;a <= 6;a += 3)
                    {
                        for (int b = a;b < a + 3;b++) //iteracja po polach w linii w tym samym kwadracie
                        {
                            if (HelperFunctionsExtension::IsContained(candidates[i][b], candidates[i][j][k])) //jeœli pole zawiera kandydata
                            {
                                exist++;
                                line = a; // ustawienie linii pocz¹tkowej wiersza kwadratu tam gdzie wystêpuje kandydat
                                break;
                            }
                        }
                    }
                    if (exist == 1) //je¿eli kandydaci wystêpuj¹ tylko w polach które nale¿y do tylko jednego kwadratu
                    {
                        std::array<std::array<std::vector<int>, 9>, 9 > singleMethod;
                        std::array<std::array<std::vector<int>, 9>, 9 > singleMethodDel;
                        int n = 0; //ustalenie linii kolumny
                        if (i < 3) n = 0;
                        else if (i >= 3 && i < 6) n = 3;
                        else if (i >= 6) n = 6;

                        for (int y = n;y < n + 3;y++) // iteracja po polach w kwardacie
                            for (int x = line;x < line + 3;x++)
                                for (int a = 0;a < candidates[y][x].size();a++) //usniêcie kandydata z pól kwadratu który nie le¿y na linii y 
                                    if (candidates[y][x][a] == candidates[i][j][k])
                                    {
                                        if (y != i)
                                            singleMethodDel[y][x].push_back(candidates[y][x][a]);
                                        else
                                            singleMethod[y][x].push_back(candidates[y][x][a]);
                                    }

                        bool existMethod = false;
                        int l = 0;
                        for (int a = 0;a < 9;a++)
                            for (int b = 0;b < 9;b++)
                                if (singleMethodDel[a][b].empty())
                                    l++;
                        if(l == 81)
                            existMethod = true;
                        for (auto & methodSolution : methodSolutions)
                            if (methodSolution.Candidates == singleMethod && methodSolution.StructureType == BoardStructureType::Row)
                                existMethod = true;

                        if (!existMethod)
                        {
                            MethodSolutionDto solution;
                            solution.Candidates = singleMethod;
                            solution.CandidatesToDelete = singleMethodDel;
                            solution.StructureType = BoardStructureType::Row;
                            methodSolutions.push_back(solution);
                        }
                    }
                }
            }
        }
    }

    for (int j = 0;j < 9;j++) //iteracja po kolumnach
    {
        for (int i = 0;i < 9;i++)
        {
            if (!candidates[i][j].empty() && candidates[i][j][0] != 10)
            {
                for (int k = 0;k < candidates[i][j].size();k++) //itreacja po kandydatach w polach
                {
                    int exist = 0, line;
                    for (int a = 0;a <= 6;a += 3)
                    {
                        for (int b = a;b < a + 3;b++) //iteracja po polach w linii w tym samym kwadracie
                        {
                            if (HelperFunctionsExtension::IsContained(candidates[b][j], candidates[i][j][k])) //jeœli pole zawiera kandydata
                            {
                                exist++;
                                line = a; // ustawienie linii pocz¹tkowej kolumny kwadratu tam gdzie wystêpuje kandydat
                                break;
                            }
                        }
                    }
                    if (exist == 1) //je¿eli kandydaci wystêpuj¹ tylko w polach które nale¿y do tylko jednego kwadratu
                    {
                        std::array<std::array<std::vector<int>, 9>, 9 > singleMethod;
                        std::array<std::array<std::vector<int>, 9>, 9 > singleMethodDel;
                        int n = 0; //ustalenie linii wiersza
                        if (j < 3) n = 0;
                        else if (j >= 3 && j < 6) n = 3;
                        else if (j >= 6) n = 6;

                        for (int x = n;x < n + 3;x++) // iteracja po polach w kwardacie
                            for (int y = line;y < line + 3;y++)
                                for (int a = 0;a < candidates[y][x].size();a++) //susniêcie kandydata z pól kwadratu który nie le¿y na linii y 
                                    if (candidates[y][x][a] == candidates[i][j][k])
                                    {
                                        if (x != j)
                                            singleMethodDel[y][x].push_back(candidates[y][x][a]);
                                        else
                                            singleMethod[y][x].push_back(candidates[y][x][a]);
                                    }

                        bool existMethod = false;
                        int l = 0;
                        for (int a = 0;a < 9;a++)
                            for (int b = 0;b < 9;b++)
                                if (singleMethodDel[a][b].empty())
                                    l++;
                        if (l == 81)
                            existMethod = true;
                        for (auto & methodSolution : methodSolutions)
                            if (methodSolution.Candidates == singleMethod && methodSolution.StructureType == BoardStructureType::Column)
                                existMethod = true;

                        if (!existMethod)
                        {
                            MethodSolutionDto solution;
                            solution.Candidates = singleMethod;
                            solution.CandidatesToDelete = singleMethodDel;
                            solution.StructureType = BoardStructureType::Column;
                            methodSolutions.push_back(solution);
                        }
                    }
                }

            }
        }
    }

    for (int y = 0;y <= 6;y += 3) // iteracja po kwadratach
    {
        for (int x = 0;x <= 6;x += 3)
        {
            for (int i = y;i < y + 3;i++)
            {
                for (int j = x;j < x + 3;j++)
                {
                    if (!candidates[i][j].empty() && candidates[i][j][0] != 10)
                    {
                        for (int k = 0;k < candidates[i][j].size();k++)
                        {
                            int exist = 0;
                            for (int a = y;a < y + 3;a++) //sprawdzenie w ilu wierszach wystêpuje kandydat
                            {
                                for (int b = x;b < x + 3;b++)
                                {
                                    if (HelperFunctionsExtension::IsContained(candidates[a][b], candidates[i][j][k]))
                                    {
                                        exist++;
                                        break;
                                    }
                                }
                            }
                            if (exist == 1)//wystêpuje tylko w 1 wierszu
                            {
                                std::array<std::array<std::vector<int>, 9>, 9 > singleMethod;
                                std::array<std::array<std::vector<int>, 9>, 9 > singleMethodDel;
                                int n;
                                if (j < 3) n = 0;
                                else if (j >= 3 && j < 6) n = 3;
                                else if (j >= 6) n = 6;

                                for (int a = 0;a < 9;a++) //usuniêcie kandydata z wiersza (z wy³¹czeniem pól które s¹ w kwadracie)
                                    for (int b = 0;b < candidates[i][a].size();b++)
                                        if (candidates[i][a][b] == candidates[i][j][k])
                                        {
                                            if (a != n && a != n + 1 && a != n + 2)
                                                singleMethodDel[i][a].push_back(candidates[i][a][b]);
                                            else
                                                singleMethod[i][a].push_back(candidates[i][a][b]);
                                        }

                                bool existMethod = false;
                                int l = 0;
                                for (int a = 0;a < 9;a++)
                                    for (int b = 0;b < 9;b++)
                                        if (singleMethodDel[a][b].empty())
                                            l++;
                                if (l == 81)
                                    existMethod = true;
                                for (auto & methodSolution : methodSolutions)
                                    if (methodSolution.Candidates == singleMethod && methodSolution.StructureType == BoardStructureType::Square)
                                        existMethod = true;

                                if (!existMethod)
                                {
                                    MethodSolutionDto solution;
                                    solution.Candidates = singleMethod;
                                    solution.CandidatesToDelete = singleMethodDel;
                                    solution.StructureType = BoardStructureType::Square;
                                    methodSolutions.push_back(solution);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return methodSolutions;
}

