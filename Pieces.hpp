//
//  Pieces.hpp
//  Chess
//
//  Created by zili wang on 2019-09-05.
//  Copyright © 2019 Zili. All rights reserved.
//

#ifndef Pieces_hpp
#define Pieces_hpp

#include <string>

enum class Color{
    white,
    black,
    empty
};

enum class Name{
    rook,
    knight,
    bishop,
    queen,
    king,
    pawn,
    none
};

struct Coordinate {
    Coordinate() = default;
    Coordinate(int px, int py) : x(px), y(py) {}
    int x = 0;
    int y = 0;
};

/*
 * Each Pieces structure represents a single square on the board.
 * A piece knows its name and color
 */
class Pieces {
public:
    Name name;
    Color color;
    Pieces(Name name = Name::none, Color color = Color::empty);
    ~Pieces();
    void setNameandColor(const Name& newName, const Color& newColor);
    const Name& getName();
    const Color& getColor();
    
};
    std::ostream& operator <<(std::ostream& out, const Pieces& piece); //for debug purpose

#endif /* Pieces_hpp */
