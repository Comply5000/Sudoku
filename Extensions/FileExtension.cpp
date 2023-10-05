//
// Created by wojci on 05.10.2023.
//

#include <vector>
#include "FileExtension.h"

void FileExtension::SaveBoard(std::array<std::array<int, 9>, 9> numbers)
{
    wchar_t savedFileName[MAX_PATH];

    if (SaveFileDialog(savedFileName))
    {
        std::wstring ws(savedFileName);
        std::string str(ws.begin(), ws.end());
        if (str.substr(str.length() - 4, str.length() - 1) != ".txt")
            str += ".txt";

        std::fstream file;
        file.open(str, std::ios::out);

        for (int i = 0;i < 9;i++)
        {
            for (int j = 0;j < 9;j++)
            {
                file << numbers[i][j];
            }
            file << std::endl;
        }
        file.close();
    }
}

bool FileExtension::SaveFileDialog(wchar_t szFileName[]) {
    OPENFILENAMEW ofn;
    const wchar_t* FilterSpec = L"Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
    const wchar_t* Title = L"Save File";

    wchar_t szFileTitle[MAX_PATH] = L"";

    szFileName[0] = L'\0';

    ofn.lStructSize = sizeof(OPENFILENAMEW);
    ofn.hwndOwner = NULL;
    ofn.lpstrFilter = FilterSpec;
    ofn.lpstrCustomFilter = NULL;
    ofn.nMaxCustFilter = 0;
    ofn.nFilterIndex = 1;
    ofn.lpstrFile = szFileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrInitialDir = L".";
    ofn.lpstrFileTitle = szFileTitle;
    ofn.nMaxFileTitle = MAX_PATH;
    ofn.lpstrTitle = Title;
    ofn.lpstrDefExt = L"txt";
    ofn.Flags = OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST;

    return GetSaveFileNameW(&ofn) == TRUE;
}

bool FileExtension::OpenFileDialog(wchar_t szFileName[]) {
    OPENFILENAMEW ofn;
    const wchar_t* FilterSpec = L"Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
    const wchar_t* Title = L"Open File";

    wchar_t szFileTitle[MAX_PATH] = L"";

    szFileName[0] = L'\0';

    ofn.lStructSize = sizeof(OPENFILENAMEW);
    ofn.hwndOwner = NULL; // Ustaw na NULL, aby niezależnie otwierać okno dialogowe.
    ofn.lpstrFilter = FilterSpec;
    ofn.lpstrCustomFilter = NULL;
    ofn.nMaxCustFilter = 0;
    ofn.nFilterIndex = 1; // Wybierz pierwszy filtr na liście.
    ofn.lpstrFile = szFileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrInitialDir = L"."; // Początkowy katalog.
    ofn.lpstrFileTitle = szFileTitle;
    ofn.nMaxFileTitle = MAX_PATH;
    ofn.lpstrTitle = Title;
    ofn.lpstrDefExt = NULL; // Brak domyślnego rozszerzenia.
    ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;

    // Zwróć true, jeśli użytkownik wybrał plik.
    return GetOpenFileNameW(&ofn) == TRUE;
}

std::array<std::array<int, 9>, 9> FileExtension::LoadBoard()
{
    wchar_t openedFileName[MAX_PATH];
    if (OpenFileDialog(openedFileName))
    {
        std::fstream file;
        file.open(openedFileName, std::ios::in);

        std::string line;
        std::vector<std::string> tab;
        while (!file.eof())
        {
            std::getline(file, line);
            tab.push_back(line);
        }
        file.close();

        std::array<std::array<int, 9>, 9> numbers = {};
        try
        {
            for (int i = 0;i < 9;i++)
            {
                for (int j = 0;j < tab[i].length();j++)
                    numbers[i][j] = tab[i][j] - 48;
            }
            return numbers;
        }
        catch(std::exception& e)
        {
        }
        return numbers;
    }
}



