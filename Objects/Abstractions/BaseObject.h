#ifndef SUDOKU_BASEOBJECT_H
#define SUDOKU_BASEOBJECT_H

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>

// klasa abstrakcyjna reprezentująca obiekty w aplikacji
class BaseObject {
protected:
    sf::RectangleShape _shape;
    sf::Texture _texture;
    sf::Texture _secondTexture;

public:
    virtual void Create() = 0; //metoda abstrakcyjna do tworzenie obiektu
    void SetDefaultTexture(); //ustawienie bazowej tekstury
    void SetSecondTexture(); //ustawienie dodatkowej tekstury
    bool IsClicked(sf::Vector2f mousePosition, sf::Mouse::Button mouseButton); //sprawdzenie czy obiek został kliknięty myszką
    bool IsHover(sf::Vector2f mousePosition); //sprawdzenie czy na obiekcie znajduje się kursor
    void SetWhiteColor();
    void SetGreyColor();
    void SetGreenColor();
    void SetRedColor();
    sf::RectangleShape GetShape(); //zwrócenie _shape

};


#endif //SUDOKU_BASEOBJECT_H
