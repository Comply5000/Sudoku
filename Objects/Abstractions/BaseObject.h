#ifndef SUDOKU_BASEOBJECT_H
#define SUDOKU_BASEOBJECT_H

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>

class BaseObject {
protected:
    sf::RectangleShape _shape;
    sf::Texture _texture;
    sf::Texture _secondTexture;

public:
    virtual void Create() = 0;
    void SetDefaultTexture();
    void SetSecondTexture();
    bool IsClicked(sf::Vector2f mousePosition, sf::Mouse::Button mouseButton);
    bool IsHover(sf::Vector2f mousePosition);
    void SetWhiteColor();
    void SetGreyColor();
    sf::RectangleShape GetShape();

};


#endif //SUDOKU_BASEOBJECT_H
