#include "Board.h"

void Board::Create() {
    _shape.setPosition(0.f,0.f);
    _shape.setSize(sf::Vector2f(700.f, 700.f));
    _texture.loadFromFile("../Objects/Board/Textures/board.png");
    _shape.setTexture(&_texture);
}

Board::Board() {
    Create();
}
