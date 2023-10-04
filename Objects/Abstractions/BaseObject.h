#ifndef SUDOKU_BASEOBJECT_H
#define SUDOKU_BASEOBJECT_H

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>

class BaseObject {
public:
    sf::RectangleShape Shape;
    sf::Texture Texture;
    sf::Texture SecondTexture;

public:
    virtual void Create();
    virtual void SetDefaultTexture();
    virtual void SetSecondTexture();
    bool IsClicked(sf::Vector2f mousePosition, sf::Mouse::Button mouseButton);
    bool IsHover(sf::Vector2f mousePosition);
    void SetWhiteColor();
    void SetGreyColor();
};


#endif //SUDOKU_BASEOBJECT_H
