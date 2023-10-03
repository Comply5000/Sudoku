//
// Created by Wojtek on 03.10.2023.
//

#include "CandidateBox.h"

sf::Color* CandidateBox::_greyColor = nullptr;
sf::Texture CandidateBox::Textures[10];
sf::Texture CandidateBox::CheckedTextures[10];

void CandidateBox::InitCandidateBoxes()
{
    for (int i = 1; i < 10; i++)
    {
        std::string t = "../Objects/Candidates/Textures/Default/" + std::to_string(i) + ".png";
        Textures[i].loadFromFile(t);
        t = "../Objects/Candidates/Textures/Checked/" + std::to_string(i) + ".png";
        CheckedTextures[i].loadFromFile(t);
    }
}

std::array<std::array<std::vector<CandidateBox>, 9>, 9> CandidateBox::UpdateCandidates(std::array<std::array<int, 9>, 9> numbers, std::array<std::array<BoxObject, 9>, 9> boxes)
{
    auto candidateNumbers = MethodsExtension::FindCandidates(numbers);

    std::array<std::array<std::vector<CandidateBox>, 9>, 9> candidateBoxes;

    for (int i = 0;i < 9;i++)
    {
        for (int j = 0;j < 9;j++)
        {
            if (numbers[i][j] == 0)
            {
                float x = 0;
                float y = 0;
                for (int k = 0;k < candidateNumbers[i][j].size();k++)
                {
                    CandidateBox candidateBox;
                    candidateBox.Shape.setPosition(boxes[i][j].Shape.getPosition().x + x, boxes[i][j].Shape.getPosition().y + y);
                    candidateBox.Shape.setSize(sf::Vector2f(17.5f, 17.5f));
                    candidateBox.Shape.setTexture(&Textures[candidateNumbers[i][j][k]]);
                    //candidateBox.Shape.setFillColor(sf::Color::Red);
                    candidateBoxes[i][j].push_back(candidateBox);

                    if (x == 52.5)
                    {
                        x = 0;
                        y += 17.5;
                    }
                    else
                        x += 17.5;

                }
            }
        }
    }

    return candidateBoxes;
}

