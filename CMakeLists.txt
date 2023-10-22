cmake_minimum_required(VERSION 3.26)
project(Sudoku)

set(CMAKE_CXX_STANDARD 20)

add_executable(Sudoku main.cpp
        Sudoku.cpp
        Sudoku.h
        Objects/Abstractions/BaseObject.cpp
        Objects/Abstractions/BaseObject.h
        Objects/Board/Board.cpp
        Objects/Board/Board.h
        Objects/ResetButton/ResetButton.cpp
        Objects/ResetButton/ResetButton.h
        Objects/SolveButton/SolveButton.cpp
        Objects/SolveButton/SolveButton.h
        Objects/LoadButton/LoadButton.cpp
        Objects/LoadButton/LoadButton.h
        Objects/SaveButton/SaveButton.cpp
        Objects/SaveButton/SaveButton.h
        Objects/Boxes/BoxObject.cpp
        Objects/Boxes/BoxObject.h
        DTOs/Coordinates.h
        Objects/ShowCandidatesCheckBox/ShowCandidatesCheckBox.cpp
        Objects/ShowCandidatesCheckBox/ShowCandidatesCheckBox.h
        Objects/MethodObjects/UpButton.cpp
        Objects/MethodObjects/UpButton.h
        Objects/MethodObjects/DownButton.cpp
        Objects/MethodObjects/DownButton.h
        Objects/Logo/Logo.cpp
        Objects/Logo/Logo.h
        Objects/Candidates/CandidateBox.cpp
        Objects/Candidates/CandidateBox.h
        Extensions/MethodsExtension.cpp
        Extensions/MethodsExtension.h
        Objects/Boxes/BoxTextures.cpp
        Objects/Boxes/BoxTextures.h
        Objects/Candidates/CandidateBoxTextures.cpp
        Objects/Candidates/CandidateBoxTextures.h
        Shared/Static/CustomColors.cpp
        Shared/Static/CustomColors.h
        Extensions/FileExtension.cpp
        Extensions/FileExtension.h
        Extensions/SolverExtension.cpp
        Extensions/SolverExtension.h
        Extensions/HelperFunctionsExtension.cpp
        Extensions/HelperFunctionsExtension.h
        DTOs/MethodSolutionDto.h
        Shared/Enums/StructureType.h
        Objects/MethodObjects/ListMethodButton.cpp
        Objects/MethodObjects/ListMethodButton.h
        Objects/MethodObjects/MethodButton.cpp
        Objects/MethodObjects/MethodButton.h
        Objects/MethodObjects/MethodButtonTextures.cpp
        Objects/MethodObjects/MethodButtonTextures.h
        Shared/Enums/MethodType.h
        Objects/MethodObjects/MethodText.cpp
        Objects/MethodObjects/MethodText.h
        Shared/Static/EnumsToStrings.cpp
        Shared/Static/EnumsToStrings.h)


set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR E:/c++/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(E:/c++/SFML/include/cmake/SFML)
target_link_libraries(Sudoku sfml-system sfml-window sfml-graphics sfml-audio)
