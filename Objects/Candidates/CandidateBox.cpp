//
// Created by Wojtek on 03.10.2023.
//

#include "CandidateBox.h"
#include "CandidateBoxTextures.h"
#include "../Boxes/BoxTextures.h"
#include "../../Shared/CustomColors.h"

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
                    candidateBox._shape.setPosition(boxes[i][j].GetShape().getPosition().x + x, boxes[i][j].GetShape().getPosition().y + y);
                    candidateBox._shape.setSize(sf::Vector2f(17.5f, 17.5f));
                    candidateBox._shape.setTexture(&CandidateBoxTextures::Textures[candidateNumbers[i][j][k]]);
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

void CandidateBox::SetNumberTexture(int number)
{
    _shape.setTexture(&CandidateBoxTextures::Textures[number]);
}

void CandidateBox::SetCheckedNumberTexture(int number)
{
    _shape.setTexture(&CandidateBoxTextures::CheckedTextures[number]);
}

void CandidateBox::Create() {

}

