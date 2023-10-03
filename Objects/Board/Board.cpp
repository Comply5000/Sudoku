#include "Board.h"

void Board::Create() {
    Shape.setPosition(0.f,0.f);
    Shape.setSize(sf::Vector2f(700.f, 700.f));
    Texture.loadFromFile("../Objects/Board/Textures/board.png");
    Shape.setTexture(&Texture);
}

Board::Board() {
    Create();
}
