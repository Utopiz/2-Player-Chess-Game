//
//  Board.hpp
//  Chess
//
//  Created by zili wang on 2019-09-05.
//  Copyright © 2019 Zili. All rights reserved.
//

#ifndef Board_hpp
#define Board_hpp

#include <stdio.h>
#include <set>
#include "Pieces.hpp"

class Board {
public:
    Board();
    ~Board();
    void initializeBoard();
    bool isValidtoMove(const Coordinate& oldCoord, const Coordinate& newCoord, const Color& color);
    void updateBoard(const Coordinate& oldCoord, const Coordinate& newCoord);
    const bool hasKing(const Color& color);
    void print();
    
private:
    const bool isKingChecked(const Color& color, int x, int y);
    bool isEmptyBettwen(Coordinate coord, int xDiff, int yDiff, int steps);
    const Pieces& getPiece(const Coordinate& coordinate);
    bool isCastling = false;
    Coordinate whiteKing;
    Coordinate blackKing;
    Pieces pieces_[8][8];
};



#endif /* Board_hpp */
