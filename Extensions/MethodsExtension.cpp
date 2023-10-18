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
                            if (methodSolution.Candidates == singleMethod && methodSolution.StructureType == StructureType::Row)
                                existMethod = true;

                        if (!existMethod)
                        {
                            MethodSolutionDto solution;
                            solution.Candidates = singleMethod;
                            solution.CandidatesToDelete = singleMethodDel;
                            solution.StructureType = StructureType::Row;
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
                            if (methodSolution.Candidates == singleMethod && methodSolution.StructureType == StructureType::Column)
                                existMethod = true;

                        if (!existMethod)
                        {
                            MethodSolutionDto solution;
                            solution.Candidates = singleMethod;
                            solution.CandidatesToDelete = singleMethodDel;
                            solution.StructureType = StructureType::Column;
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
                                    if (methodSolution.Candidates == singleMethod && methodSolution.StructureType == StructureType::Square)
                                        existMethod = true;

                                if (!existMethod)
                                {
                                    MethodSolutionDto solution;
                                    solution.Candidates = singleMethod;
                                    solution.CandidatesToDelete = singleMethodDel;
                                    solution.StructureType = StructureType::Square;
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

std::vector<MethodSolutionDto> MethodsExtension::NakedPair(std::array<std::array<int, 9>, 9> numbers) 
{
    auto candidates = FindCandidates(numbers);
    std::vector<MethodSolutionDto> methodSolutions;
    
    for (int i = 0;i < 9;i++) //iteracja po wierszu
    {
        for (int j = 0;j < 9;j++) //iteracja po kolumnie
        {
            if (candidates[i][j].size() == 2) // szukamy takiego pola które posiada 2 kandydatów
            {
                for (int a = 0;a < 9;a++) //ponowna iteracja po polach w wierszu
                {
                    if (candidates[i][j] == candidates[i][a] && j != a) //szukane pole ma takich samych kandydatów i nie jest polem pierwotnym
                    {
                        int e1 = candidates[i][j][0]; // zapisanie tych kandydatów
                        int e2 = candidates[i][j][1];
                        std::array<std::array<std::vector<int>, 9>, 9 > singleMethod;
                        singleMethod[i][j].push_back(e1);
                        singleMethod[i][j].push_back(e2);
                        singleMethod[i][a].push_back(e1);
                        singleMethod[i][a].push_back(e2);

                        bool existMethod = false;
                        for (auto & methodSolution : methodSolutions)
                            if (methodSolution.Candidates == singleMethod && methodSolution.StructureType == StructureType::Row)
                                existMethod = true;
                        if (!existMethod)
                        {
                            std::array<std::array<std::vector<int>, 9>, 9 > singleMethodDel;
                            for (int b = 0;b < 9;b++)
                            {
                                for (int c = 0;c < candidates[i][b].size();c++) //usuwanie zapisanych kandydatów z pól (oprócz tych pól które zawieraj¹ dok³adnie tych kandydatów)
                                {
                                    if (b != j && b != a)
                                    {
                                        if (candidates[i][b][c] == e1)
                                            singleMethodDel[i][b].push_back(e1);
                                        else if (candidates[i][b][c] == e2)
                                            singleMethodDel[i][b].push_back(e2);
                                    }
                                }
                            }
                            MethodSolutionDto solution;
                            solution.Candidates = singleMethod;
                            solution.StructureType = StructureType::Row;
                            solution.CandidatesToDelete = singleMethodDel;
                            methodSolutions.push_back(solution);
                        }
                    }
                }
            }
        }
    }

    //to samo tylko po kolumnach
    for (int j = 0;j < 9;j++)
    {
        for (int i = 0;i < 9;i++)
        {
            if (candidates[i][j].size() == 2)
            {
                for (int a = 0;a < 9;a++)
                {
                    if (candidates[i][j] == candidates[a][j] && i != a)
                    {
                        int e1 = candidates[i][j][0];
                        int e2 = candidates[i][j][1];
                        std::array<std::array<std::vector<int>, 9>, 9 > singleMethod;
                        singleMethod[i][j].push_back(e1);
                        singleMethod[i][j].push_back(e2);
                        singleMethod[a][j].push_back(e1);
                        singleMethod[a][j].push_back(e2);

                        bool existMethod = false;
                        for (auto & methodSolution : methodSolutions)
                            if (methodSolution.Candidates == singleMethod && methodSolution.StructureType == StructureType::Column)
                                existMethod = true;
                        if (!existMethod)
                        {
                            std::array<std::array<std::vector<int>, 9>, 9 > singleMethodDel;
                            for (int b = 0;b < 9;b++)
                            {
                                for (int c = 0;c < candidates[b][j].size();c++)
                                {
                                    if (b != i && b != a)
                                    {
                                        if (candidates[b][j][c] == e1)
                                            singleMethodDel[b][j].push_back(e1);
                                        else if (candidates[b][j][c] == e2)
                                            singleMethodDel[b][j].push_back(e2);
                                    }
                                }
                            }
                            MethodSolutionDto solution;
                            solution.Candidates = singleMethod;
                            solution.StructureType = StructureType::Column;
                            solution.CandidatesToDelete = singleMethodDel;
                            methodSolutions.push_back(solution);
                        }
                    }
                }
            }
        }
    }
    
    for (int y = 0;y <= 6;y += 3) // x,y - pêtle odpowiedzialne za przemieszczanie siê pobiêdzy 9 boxami 
    {
        for (int x = 0;x <= 6;x += 3)
        {
            for (int i = y;i < y + 3;i++) // iterazja poszczególnych pól w boxie
            {
                for (int j = x;j < x + 3;j++)
                {
                    if (candidates[i][j].size() == 2) // szukamy takiego pola które posiada 2 kandydatów
                    {
                        for (int a = y;a < y + 3;a++) //ponowna iteracja po polach w boxie by znaleœæ pole z takimi samymi kandydatami
                        {
                            for (int b = x;b < x + 3;b++)
                            {
                                if (candidates[i][j] == candidates[a][b] && i != a && a != b) //szukane pole ma takich samych kandydatów i nie jest polem pierwotnym
                                {
                                    int e1 = candidates[i][j][0]; //zapisanie tych kandydatów
                                    int e2 = candidates[i][j][1];
                                    std::array<std::array<std::vector<int>, 9>, 9 > singleMethod;
                                    singleMethod[i][j].push_back(e1);
                                    singleMethod[i][j].push_back(e2);
                                    singleMethod[a][b].push_back(e1);
                                    singleMethod[a][b].push_back(e2);

                                    bool existMethod = false;
                                    for (auto & methodSolution : methodSolutions)
                                        if (methodSolution.Candidates == singleMethod && methodSolution.StructureType == StructureType::Square)
                                            existMethod = true;
                                    if (!existMethod)
                                    {
                                        std::array<std::array<std::vector<int>, 9>, 9 > singleMethodDel;
                                        for (int c = y;c < y + 3;c++) //iteracja po polach w boxie
                                        {
                                            for (int d = x;d < x + 3;d++)
                                            {
                                                for (int e = 0;e < candidates[c][d].size();e++) //usuwanie zapisanych kandydatów z pól (oprócz tych pól które zawieraj¹ dok³adnie tych kandydatów)
                                                {
                                                    if (candidates[c][d] != candidates[i][j] && candidates[c][d] != candidates[a][b] && (candidates[c][d][e] == e1 || candidates[c][d][e] == e2))
                                                    {
                                                        if (candidates[c][d][e] == e1)
                                                            singleMethodDel[c][d].push_back(e1);
                                                        else if (candidates[c][d][e] == e2)
                                                            singleMethodDel[c][d].push_back(e2);
                                                    }
                                                }
                                            }
                                        }
                                        MethodSolutionDto solution;
                                        solution.Candidates = singleMethod;
                                        solution.StructureType = StructureType::Square;
                                        solution.CandidatesToDelete = singleMethodDel;
                                        methodSolutions.push_back(solution);
                                    }
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

std::vector<MethodSolutionDto> MethodsExtension::NakedTriple(std::array<std::array<int, 9>, 9> numbers) 
{
    auto candidates = FindCandidates(numbers);
    std::vector<MethodSolutionDto> methodSolutions;
    
    for (int i = 0;i < 9;i++)
    {
        for (int j = 0;j < 9;j++)
        {
            if (candidates[i][j].size() == 3) //pola o wiekoœci 3
            {
                std::vector<int> line;
                for (int a = 0;a < 9;a++)
                {
                    if (candidates[i][a] == candidates[i][j]) //je¿eli pole jest takie samo
                    {
                        line.push_back(a);
                    }
                    if (candidates[i][a].size() == 2) // je¿eli pole jes wielkoœci 2
                    {
                        int exist = 0;
                        for (int b = 0;b < candidates[i][a].size();b++)
                            if (HelperFunctionsExtension::IsContained(candidates[i][j], candidates[i][a][b]))
                                exist++;
                        if (exist == 2) // to pole zawiera 2 takich samych kandydatów jak pole pierwotne
                            line.push_back(a);
                    }
                }
                if (line.size() == 3) // je¿eli istniej¹ 3 takie pola
                {
                    std::array<std::array<std::vector<int>, 9>, 9 > singleMethod;
                    std::array<std::array<std::vector<int>, 9>, 9 > singleMethodDel;

                    for(int q = 0;q<3;q++)
                        for(int l = 0;l<candidates[i][line[q]].size();l++)
                            singleMethod[i][line[q]].push_back(candidates[i][line[q]][l]);

                    bool existMethod = false;
                    for (auto & methodSolution : methodSolutions)
                        if (methodSolution.Candidates == singleMethod && methodSolution.StructureType == StructureType::Row)
                            existMethod = true;
                    if (!existMethod)
                    {
                        for (int a = 0;a < 9;a++)
                            if (a != line[0] && a != line[1] && a != line[2])
                                for (int b = 0;b < candidates[i][a].size();b++)
                                {
                                    if (candidates[i][a][b] == candidates[i][j][0])
                                        singleMethodDel[i][a].push_back(candidates[i][a][b]);
                                    if (candidates[i][a][b] == candidates[i][j][1])
                                        singleMethodDel[i][a].push_back(candidates[i][a][b]);
                                    if (candidates[i][a][b] == candidates[i][j][2])
                                        singleMethodDel[i][a].push_back(candidates[i][a][b]);
                                }

                        MethodSolutionDto solution;
                        solution.Candidates = singleMethod;
                        solution.StructureType = StructureType::Row;
                        solution.CandidatesToDelete = singleMethodDel;
                        methodSolutions.push_back(solution);
                    }
                }
            }
        }
    }

    for (int j = 0;j < 9;j++)
    {
        for (int i = 0;i < 9;i++)
        {
            if (candidates[i][j].size() == 3)
            {
                std::vector<int> line;
                for (int a = 0;a < 9;a++)
                {
                    if (candidates[a][j] == candidates[i][j])
                    {
                        line.push_back(a);
                    }
                    if (candidates[a][j].size() == 2)
                    {
                        int exist = 0;
                        for (int b = 0;b < candidates[a][j].size();b++)
                            if (HelperFunctionsExtension::IsContained(candidates[i][j], candidates[a][j][b]))
                                exist++;
                        if (exist == 2)
                            line.push_back(a);
                    }
                }
                if (line.size() == 3)
                {
                    std::array<std::array<std::vector<int>, 9>, 9 > singleMethod;
                    std::array<std::array<std::vector<int>, 9>, 9 > singleMethodDel;

                    for (int q = 0;q < 3;q++)
                        for (int l = 0;l < candidates[line[q]][j].size();l++)
                            singleMethod[line[q]][j].push_back(candidates[line[q]][j][l]);

                    bool existMethod = false;
                    for (auto & methodSolution : methodSolutions)
                        if (methodSolution.Candidates == singleMethod && methodSolution.StructureType == StructureType::Column)
                            existMethod = true;

                    if (!existMethod)
                    {
                        for (int a = 0;a < 9;a++)
                            if (a != line[0] && a != line[1] && a != line[2])
                                for (int b = 0;b < candidates[i][a].size();b++)
                                {
                                    if (candidates[a][j][b] == candidates[i][j][0])
                                        singleMethodDel[a][j].push_back(candidates[a][j][b]);
                                    if (candidates[a][j][b] == candidates[i][j][1])
                                        singleMethodDel[a][j].push_back(candidates[a][j][b]);
                                    if (candidates[a][j][b] == candidates[i][j][2])
                                        singleMethodDel[a][j].push_back(candidates[a][j][b]);
                                }

                        MethodSolutionDto solution;
                        solution.Candidates = singleMethod;
                        solution.StructureType = StructureType::Column;
                        solution.CandidatesToDelete = singleMethodDel;
                        methodSolutions.push_back(solution);
                    }
                }
            }
        }
    }

    for (int y = 0;y <= 6;y += 3) // x,y - pêtle odpowiedzialne za przemieszczanie siê pobiêdzy 9 boxami 
    {
        for (int x = 0;x <= 6;x += 3)
        {
            for (int i = y;i < y + 3;i++) // iterazja poszczególnych pól w boxie
            {
                for (int j = x;j < x + 3;j++)
                {
                    if (candidates[i][j].size() == 3)
                    {
                        std::vector<std::vector<int>>box;
                        for (int a = y;a < y + 3;a++)
                        {
                            for (int b = x;b < x + 3;b++)
                            {
                                if (candidates[a][b] == candidates[i][j])
                                {
                                    box.push_back(candidates[a][b]);
                                }
                                if (candidates[a][b].size() == 2)
                                {
                                    int exist = 0;
                                    for (int c = 0;c < candidates[a][b].size();c++)
                                        if (HelperFunctionsExtension::IsContained(candidates[i][j], candidates[a][b][c]))
                                            exist++;
                                    if (exist == 2)
                                    {
                                        box.push_back(candidates[a][b]);
                                    }
                                }
                            }
                        }
                        if (box.size() == 3)
                        {
                            std::array<std::array<std::vector<int>, 9>, 9 > singleMethod;
                            std::array<std::array<std::vector<int>, 9>, 9 > singleMethodDel;

                            for (int a = y;a < y + 3;a++)
                                for (int b = x;b < x + 3;b++)
                                    for (int q = 0;q < 3;q++)
                                        if (candidates[a][b] == box[q])
                                            for (int l = 0;l < candidates[a][b].size();l++)
                                                singleMethod[a][b].push_back(candidates[a][b][l]);

                            bool existMethod = false;
                            for (auto & methodSolution : methodSolutions)
                                if (methodSolution.Candidates == singleMethod && methodSolution.StructureType == StructureType::Square)
                                    existMethod = true;

                            if (!existMethod)
                            {
                                for (int a = y;a < y + 3;a++)
                                    for (int b = x;b < x + 3;b++)
                                        if (candidates[a][b] != box[0] && candidates[a][b] != box[1] && candidates[a][b] != box[2])
                                            for (int c = 0;c < candidates[a][b].size();c++)
                                            {
                                                if (candidates[a][b][c] == candidates[i][j][0])
                                                    singleMethodDel[a][b].push_back(candidates[a][b][c]);
                                                if (candidates[a][b][c] == candidates[i][j][1])
                                                    singleMethodDel[a][b].push_back(candidates[a][b][c]);
                                                if (candidates[a][b][c] == candidates[i][j][2])
                                                    singleMethodDel[a][b].push_back(candidates[a][b][c]);
                                            }

                                MethodSolutionDto solution;
                                solution.Candidates = singleMethod;
                                solution.StructureType = StructureType::Square;
                                solution.CandidatesToDelete = singleMethodDel;
                                methodSolutions.push_back(solution);
                            }
                        }
                    }
                }
            }
        }
    }

    return methodSolutions;
}

std::vector<MethodSolutionDto> MethodsExtension::LockedPair(std::array<std::array<int, 9>, 9> numbers)
{
    auto candidates = FindCandidates(numbers);
    std::vector<MethodSolutionDto> methodSolutions;
    
    for (int i = 0;i < 9;i++)
    {
        for (int a = 1;a <= 9;a++) //iteracja po wszystkich mo¿liwych kandydatach
        {
            int exist1 = 0;
            for (int j = 0;j < 9;j++)
                if (HelperFunctionsExtension::IsContained(candidates[i][j], a))
                    exist1++;

            if (exist1 == 2) //je¿eli kandydat wystêpuje tylko 2 razy w wierszu
            {
                for (int b = 1;b <= 9;b++) // iteracja po kandydatach ró¿nych od pierwszego (a)
                {
                    int exist2 = 0;
                    if (b != a)
                        for (int c = 0;c < 9;c++)
                            if (HelperFunctionsExtension::IsContained(candidates[i][c], b))
                                exist2++;

                    if (exist2 == 2) //je¿eli kandydat wystêpuje tylko 2 razy w wierszu
                    {
                        //sprawdzenie czy ci kandydaci wystêpuj¹ w 2 tych samych polach
                        std::vector<int> sameBoxes; //koordynata bloku w którym wystêpuj¹ kandydaci
                        for (int c = 0;c < 9;c++)
                            if (HelperFunctionsExtension::IsContained(candidates[i][c], a) && HelperFunctionsExtension::IsContained(candidates[i][c], b))
                                sameBoxes.push_back(c);

                        if (sameBoxes.size() == 2) //jêzeli wystêpuj¹ w tych samych polach - usuniêcie pozosta³ych kandydatów z tych 2 pól
                        {
                            std::array<std::array<std::vector<int>, 9>, 9 > singleMethod;
                            std::array<std::array<std::vector<int>, 9>, 9 > singleMethodDel;

                            for (int q = 0; q < 2; q++)
                                if (candidates[i][sameBoxes[q]].size() >= 2)
                                    for (int c = 0; c < candidates[i][sameBoxes[q]].size(); c++)
                                    {
                                        if (a != candidates[i][sameBoxes[q]][c] && b != candidates[i][sameBoxes[q]][c])
                                            singleMethodDel[i][sameBoxes[q]].push_back(candidates[i][sameBoxes[q]][c]);
                                        else
                                            singleMethod[i][sameBoxes[q]].push_back(candidates[i][sameBoxes[q]][c]);
                                    }

                            bool existMethod = false;
                            for (auto & methodSolution : methodSolutions)
                                if (methodSolution.Candidates == singleMethod && methodSolution.StructureType == StructureType::Row)
                                    existMethod = true;

                            if (!existMethod)
                            {
                                MethodSolutionDto solution;
                                solution.Candidates = singleMethod;
                                solution.StructureType = StructureType::Row;
                                solution.CandidatesToDelete = singleMethodDel;
                                methodSolutions.push_back(solution);
                            }
                        }
                    }
                }
            }
        }
    }

    std::vector<std::array<std::array<std::vector<int>, 9>, 9>> col;
    for (int j = 0; j < 9; j++)
    {
        for (int a = 1;a <= 9;a++)
        {
            int exist1 = 0;
            for (int i = 0;i < 9;i++)
                if (HelperFunctionsExtension::IsContained(candidates[i][j], a))
                    exist1++;

            if (exist1 == 2)
            {
                for (int b = 1;b <= 9;b++)
                {
                    int exist2 = 0;
                    if (b != a)
                        for (int c = 0;c < 9;c++)
                            if (HelperFunctionsExtension::IsContained(candidates[c][j], b))
                                exist2++;

                    if (exist2 == 2)
                    {
                        std::vector<int> sameBoxes;
                        for (int c = 0;c < 9;c++)
                            if (HelperFunctionsExtension::IsContained(candidates[c][j], a) && HelperFunctionsExtension::IsContained(candidates[c][j], b))
                                sameBoxes.push_back(c);

                        if (sameBoxes.size() == 2)
                        {
                            std::array<std::array<std::vector<int>, 9>, 9 > singleMethod;
                            std::array<std::array<std::vector<int>, 9>, 9 > singleMethodDel;

                            bool notEmpty = true;
                            for (int q = 0; q < 2; q++)
                                if (candidates[sameBoxes[q]][j].size() >= 2)
                                    for (int c = 0; c < candidates[sameBoxes[q]][j].size(); c++)
                                    {
                                        if (a != candidates[sameBoxes[q]][j][c] && b != candidates[sameBoxes[q]][j][c])
                                            singleMethodDel[sameBoxes[q]][j].push_back(candidates[sameBoxes[q]][j][c]);
                                        else
                                            singleMethod[sameBoxes[q]][j].push_back(candidates[sameBoxes[q]][j][c]);
                                    }

                            bool existMethod = false;
                            for (auto & methodSolution : methodSolutions)
                                if (methodSolution.Candidates == singleMethod && methodSolution.StructureType == StructureType::Column)
                                    existMethod = true;

                            if (!existMethod)
                            {
                                MethodSolutionDto solution;
                                solution.Candidates = singleMethod;
                                solution.StructureType = StructureType::Column;
                                solution.CandidatesToDelete = singleMethodDel;
                                methodSolutions.push_back(solution);
                            }
                        }
                    }
                }
            }
        }
    }

    std::vector<std::array<std::array<std::vector<int>, 9>, 9>> sqrt;
    for (int y = 0;y <= 6;y += 3)
    {
        for (int x = 0;x <= 6;x += 3)
        {
            for (int a = 1;a <= 9;a++)
            {
                int exist1 = 0;
                for (int i = y;i < y + 3;i++)
                    for (int j = x;j < x + 3;j++)
                        if (HelperFunctionsExtension::IsContained(candidates[i][j], a))
                            exist1++;

                if (exist1 == 2)
                {
                    for (int b = 1;b <= 9;b++)
                    {
                        int exist2 = 0;
                        if (b != a)
                            for (int i = y;i < y + 3;i++)
                                for (int j = x;j < x + 3;j++)
                                    if (HelperFunctionsExtension::IsContained(candidates[i][j], b))
                                        exist2++;

                        if (exist2 == 2)
                        {
                            std::vector<int> sameBoxesY, sameBoxesX;
                            for (int i = y;i < y + 3;i++)
                                for (int j = x;j < x + 3;j++)
                                    if (HelperFunctionsExtension::IsContained(candidates[i][j], a) && HelperFunctionsExtension::IsContained(candidates[i][j], b))
                                    {
                                        sameBoxesY.push_back(i);
                                        sameBoxesX.push_back(j);
                                    }

                            if (sameBoxesX.size() == 2)
                            {
                                std::array<std::array<std::vector<int>, 9>, 9 > singleMethod;
                                std::array<std::array<std::vector<int>, 9>, 9 > singleMethodDel;

                                for (int q = 0; q < 2; q++)
                                    if (candidates[sameBoxesY[q]][sameBoxesX[q]].size() >= 2)
                                        for (int c = 0; c < candidates[sameBoxesY[q]][sameBoxesX[q]].size(); c++)
                                        {
                                            if (a != candidates[sameBoxesY[q]][sameBoxesX[q]][c] && b != candidates[sameBoxesY[q]][sameBoxesX[q]][c])
                                                singleMethodDel[sameBoxesY[q]][sameBoxesX[q]].push_back(candidates[sameBoxesY[q]][sameBoxesX[q]][c]);
                                            else
                                                singleMethod[sameBoxesY[q]][sameBoxesX[q]].push_back(candidates[sameBoxesY[q]][sameBoxesX[q]][c]);
                                        }

                                bool existMethod = false;
                                for (auto & methodSolution : methodSolutions)
                                    if (methodSolution.Candidates == singleMethod && methodSolution.StructureType == StructureType::Square)
                                        existMethod = true;

                                if (!existMethod)
                                {
                                    MethodSolutionDto solution;
                                    solution.Candidates = singleMethod;
                                    solution.StructureType = StructureType::Square;
                                    solution.CandidatesToDelete = singleMethodDel;
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

std::vector<MethodSolutionDto> MethodsExtension::XWing(std::array<std::array<int, 9>, 9> numbers) 
{
    auto candidates = FindCandidates(numbers);
    std::vector<MethodSolutionDto> methodSolutions;

    for (int i = 0;i < 9;i++)
    {
        for (int j = 0;j < 9;j++)
        {
            if (!candidates[i][j].empty() && candidates[i][j][0] != 10) // pole nie jest uzupe³nione
            {
                for (int k = 0;k < candidates[i][j].size();k++) //iteracja po kandydatach w polu
                {
                    std::vector<int> columnCoord;
                    for (int a = 0;a < 9;a++) //ponowna iteracja po wszystkich polach w wierszu aby sparawdziæ ile jest tych kandydatów
                        if (candidates[i][a][0] != 10 && HelperFunctionsExtension::IsContained(candidates[i][a], candidates[i][j][k]))
                            columnCoord.push_back(a);
                    if (columnCoord.size() == 2) //je¿eli jest tylko 2 kandydatów
                    {
                        for (int b = 0;b < 9;b++)
                        {
                            //sprawdzenie czy w innym wierszu wystêpuje tylko 2 razy ten sam kandydat
                            int n = 0;
                            for (int c = 0;c < 9;c++)
                                if (b != i && HelperFunctionsExtension::IsContained(candidates[b][c], candidates[i][j][k]))
                                    n++;
                            //jeœli wystêpuje tylko 2 razy oraz na w tych samych kolumnach
                            if (n == 2 && HelperFunctionsExtension::IsContained(candidates[b][columnCoord[0]], candidates[i][j][k]) && HelperFunctionsExtension::IsContained(candidates[b][columnCoord[1]], candidates[i][j][k]))
                            {
                                std::array<std::array<std::vector<int>, 9>, 9 > singleMethod;
                                std::array<std::array<std::vector<int>, 9>, 9 > singleMethodDel;

                                for (int q = 0; q < 9; q++)
                                    for (int w = 0; w < 9; w++)
                                        if ((w == columnCoord[0] || w == columnCoord[1]) && HelperFunctionsExtension::IsContained(candidates[q][w], candidates[i][j][k]))
                                            singleMethod[q][w].push_back(candidates[i][j][k]);

                                bool existMethod = false;
                                for (auto & methodSolution : methodSolutions)
                                    if (methodSolution.Candidates == singleMethod && methodSolution.StructureType == StructureType::Row)
                                        existMethod = true;

                                if (!existMethod)
                                {
                                    for(int q = 0;q<2;q++)
                                        for (int c = 0; c < 9; c++)
                                            for (int d = 0; d < candidates[c][columnCoord[q]].size(); d++)
                                                if (c != b && c != i && candidates[c][columnCoord[q]][d] == candidates[i][j][k])
                                                    singleMethodDel[c][columnCoord[q]].push_back(candidates[i][j][k]);

                                    MethodSolutionDto solution;
                                    solution.Candidates = singleMethod;
                                    solution.StructureType = StructureType::Row;
                                    solution.CandidatesToDelete = singleMethodDel;
                                    methodSolutions.push_back(solution);
                                }
                            }
                        }
                    }
                }
            }
        }
    }


    //kolumny
    for (int j = 0; j < 9; j++)
    {
        for (int i = 0;i < 9;i++)
        {
            if (!candidates[i][j].empty() && candidates[i][j][0] != 10) // pole nie jest uzupe³nione
            {
                for (int k = 0;k < candidates[i][j].size();k++) //iteracja po kandydatach w polu
                {
                    std::vector<int> columnCoord;
                    for (int a = 0;a < 9;a++) //ponowna iteracja po wszystkich polach w wierszu aby sparawdziæ ile jest tych kandydatów
                        if (candidates[a][j][0] != 10 && HelperFunctionsExtension::IsContained(candidates[a][j], candidates[i][j][k]))
                            columnCoord.push_back(a);
                    if (columnCoord.size() == 2) //je¿eli jest tylko 2 kandydatów
                    {
                        for (int b = 0;b < 9;b++)
                        {
                            int n = 0;
                            for (int c = 0;c < 9;c++)
                                if (b != j && HelperFunctionsExtension::IsContained(candidates[c][b], candidates[i][j][k]))
                                    n++;
                            if (n == 2 && HelperFunctionsExtension::IsContained(candidates[columnCoord[0]][b], candidates[i][j][k]) && HelperFunctionsExtension::IsContained(candidates[columnCoord[1]][b], candidates[i][j][k]))
                            {
                                std::array<std::array<std::vector<int>, 9>, 9 > singleMethod;
                                std::array<std::array<std::vector<int>, 9>, 9 > singleMethodDel;

                                for (int q = 0; q < 9; q++)
                                    for (int w = 0; w < 9; w++)
                                        if ((q == columnCoord[0] || q == columnCoord[1]) && HelperFunctionsExtension::IsContained(candidates[q][w], candidates[i][j][k]))
                                            singleMethod[q][w].push_back(candidates[i][j][k]);

                                bool existMethod = false;
                                for (auto & methodSolution : methodSolutions)
                                    if (methodSolution.Candidates == singleMethod && methodSolution.StructureType == StructureType::Column)
                                        existMethod = true;

                                if (!existMethod)
                                {
                                    for(int q = 0;q<2;q++)
                                        for (int c = 0; c < 9; c++)
                                            for (int d = 0; d < candidates[columnCoord[q]][c].size(); d++)
                                                if (c != b && c != j && candidates[columnCoord[q]][c][d] == candidates[i][j][k])
                                                    singleMethodDel[columnCoord[q]][c].push_back(candidates[i][j][k]);

                                    MethodSolutionDto solution;
                                    solution.Candidates = singleMethod;
                                    solution.StructureType = StructureType::Column;
                                    solution.CandidatesToDelete = singleMethodDel;
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

