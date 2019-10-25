//
//  Board.cpp
//  Chess
//
//  Created by zili wang on 2019-09-05.
//  Copyright © 2019 Zili. All rights reserved.
//

#include "Board.hpp"
#include "Pieces.hpp"
#include <iostream>

Board::Board() {
}

Board::~Board() {
}



void Board::initializeBoard() {
    pieces_[0][0].setNameandColor(Name::rook, Color::white);
    pieces_[0][1].setNameandColor(Name::knight, Color::white);
    pieces_[0][2].setNameandColor(Name::bishop, Color::white);
    pieces_[0][3].setNameandColor(Name::king, Color::white);
    pieces_[0][4].setNameandColor(Name::queen, Color::white);
    pieces_[0][5].setNameandColor(Name::bishop, Color::white);
    pieces_[0][6].setNameandColor(Name::knight, Color::white);
    pieces_[0][7].setNameandColor(Name::rook, Color::white);
    
    pieces_[7][0].setNameandColor(Name::rook, Color::black);
    pieces_[7][1].setNameandColor(Name::knight, Color::black);
    pieces_[7][2].setNameandColor(Name::bishop, Color::black);
    pieces_[7][3].setNameandColor(Name::king, Color::black);
    pieces_[7][4].setNameandColor(Name::queen, Color::black);
    pieces_[7][5].setNameandColor(Name::bishop, Color::black);
    pieces_[7][6].setNameandColor(Name::knight, Color::black);
    pieces_[7][7].setNameandColor(Name::rook, Color::black);
    
    for (int j = 0; j < 8; j++) {
        pieces_[1][j].setNameandColor(Name::pawn, Color::white);
    }
    
    for (int j = 0; j < 8; j++) {
        pieces_[6][j].setNameandColor(Name::pawn, Color::black);
    }
    
    whiteKing.x = 0;
    whiteKing.y = 3;
    blackKing.x = 7;
    blackKing.y = 3;
}

bool Board::isValidtoMove(const Coordinate& oldCoord,
                          const Coordinate& newCoord, const Color& color) {
    Pieces curr = getPiece(oldCoord);
    Pieces next = getPiece(newCoord);
    Name currName = curr.getName();
    Name nextName = next.getName();
    if (curr.getName() == Name::none || curr.getColor() != color
        || (currName != Name::king && next.getColor() == color)) return false;
    Color currColor = curr.getColor();
    Color nextColor = next.getColor();
    switch (currName) {
        case Name::pawn:
            if (currColor == Color::white) {
                if (nextColor == Color::empty && newCoord.y - oldCoord.y == 0) {
                    if (newCoord.x - oldCoord.x == 1) return true;
                    if (oldCoord.x == 1 && newCoord.x == 3) return true;
                }
                if (nextColor == Color::black && abs(newCoord.y - oldCoord.y) == 1
                    && newCoord.x - oldCoord.x == 1) return true;
                // en passant
                if (nextColor == Color::black && abs(newCoord.y - oldCoord.y) == 1
                    && oldCoord.x == 1 && newCoord.x == 4) return true;
                return false;
            } else {
                if (nextColor == Color::empty && newCoord.y - oldCoord.y == 0) {
                    if( oldCoord.x - newCoord.x == 1) return true;
                    if( oldCoord.x == 6 && newCoord.x == 4) return true;
                }
                if (nextColor == Color::white && abs(newCoord.y - oldCoord.y) == 1
                    && oldCoord.x - newCoord.x == 1) return true;
                // en passant
                if (nextColor == Color::white && abs(newCoord.y - oldCoord.y) == 1
                    && oldCoord.x == 6 && newCoord.x == 3) return true;
                return false;
            }
        case Name::rook:
            if (newCoord.x == oldCoord.x || newCoord.y == oldCoord.y) {
                int xDiff = newCoord.x - oldCoord.x;
                int yDiff = newCoord.y - oldCoord.y;
                return isEmptyBettwen(oldCoord, xDiff, yDiff,
                                      std::max(abs(xDiff),abs(yDiff)) - 1);
            }
            return false;
        case Name::knight:
            if (abs(newCoord.x - oldCoord.x) == 2 && abs(newCoord.y - oldCoord.y) == 1) {
                return true;
            }
            if (abs(newCoord.x - oldCoord.x) == 1 && abs(newCoord.y - oldCoord.y) == 2) {
                return true;
            }
            return false;
        case Name::bishop:
            if (abs(newCoord.x - oldCoord.x) == abs(newCoord.y - oldCoord.y)) {
                int xDiff = newCoord.x - oldCoord.x;
                int yDiff = newCoord.y - oldCoord.y;
                return isEmptyBettwen(oldCoord, xDiff, yDiff,
                                      std::max(abs(xDiff),abs(yDiff)) - 1);
            }
            return false;
        case Name::king:
            if (abs(newCoord.x - oldCoord.x) <= 1 && abs(newCoord.y - oldCoord.y) <=1 && nextColor != currColor) {
                if (currColor == Color::white) {
                    whiteKing = newCoord;
                } else {
                    blackKing = newCoord;
                }
                return true;
            } else if (!isCastling && nextName == Name::rook && nextColor == color) {
                if (newCoord.x == oldCoord.x) {
                    int yDiff = newCoord.y - oldCoord.y;
                    if (abs(yDiff) <= 2) return false;
                    if (isEmptyBettwen(oldCoord, 0, yDiff, yDiff - 1)) {
                        Coordinate kingCoord = currColor == Color::white ? whiteKing : blackKing;
                        if (!isKingChecked(currColor, kingCoord.x, kingCoord.y + yDiff / std::abs(yDiff)) &&
                           !isKingChecked(currColor, kingCoord.x, kingCoord.y + 2 * yDiff / std::abs(yDiff))) {
                            isCastling = true;
                            pieces_[oldCoord.x][oldCoord.y].setNameandColor(Name::none, Color::empty);
                            pieces_[newCoord.x][newCoord.y].setNameandColor(Name::none, Color::empty);
                            pieces_[oldCoord.x][oldCoord.y + 2 * yDiff / std::abs(yDiff)].setNameandColor(currName, currColor);
                            pieces_[oldCoord.x][oldCoord.y + yDiff / std::abs(yDiff)].setNameandColor(nextName, nextColor);
                            if (currColor == Color::white) {
                                whiteKing.y = oldCoord.y + 2 * yDiff / std::abs(yDiff);
                            } else {
                                blackKing.y = oldCoord.y + 2 * yDiff / std::abs(yDiff);
                            }
                            return true;
                        }
                    }
                }
                if (newCoord.y == oldCoord.y) {
                    int xDiff = newCoord.x - oldCoord.x;
                    if (abs(xDiff) <= 2) return false;
                    if (isEmptyBettwen(oldCoord, xDiff, 0, xDiff - 1)) {
                        Coordinate kingCoord = currColor == Color::white ? whiteKing : blackKing;
                        if (!isKingChecked(currColor, kingCoord.x + xDiff / std::abs(xDiff), kingCoord.y ) &&
                           !isKingChecked(currColor, kingCoord.x + 2 * xDiff / std::abs(xDiff), kingCoord.y)) {
                            isCastling = true;
                            pieces_[oldCoord.x][oldCoord.y].setNameandColor(Name::none, Color::empty);
                            pieces_[newCoord.x][newCoord.y].setNameandColor(Name::none, Color::empty);
                            pieces_[newCoord.x + 2 * xDiff / std::abs(xDiff)][newCoord.y].setNameandColor(currName, currColor);
                            pieces_[newCoord.x + xDiff / std::abs(xDiff)][newCoord.y].setNameandColor(nextName, nextColor);
                            if (currColor == Color::white) {
                                whiteKing.x = oldCoord.x + 2 * xDiff / std::abs(xDiff);
                            } else {
                                blackKing.x = oldCoord.x + 2 * xDiff / std::abs(xDiff);
                            }
                            return true;
                        }
                    }
                }
            }
            return false;
        case Name::queen:
            if (abs(newCoord.x - oldCoord.x) == abs(newCoord.y - oldCoord.y)) {
                int xDiff = newCoord.x - oldCoord.x;
                int yDiff = newCoord.y - oldCoord.y;
                return isEmptyBettwen(oldCoord, xDiff, yDiff, std::max(abs(xDiff),abs(yDiff)) - 1);
            } else if (newCoord.x == oldCoord.x || newCoord.y == oldCoord.y) {
                int xDiff = newCoord.x - oldCoord.x;
                int yDiff = newCoord.y - oldCoord.y;
                return isEmptyBettwen(oldCoord, xDiff, yDiff, std::max(abs(xDiff),abs(yDiff)) - 1);
            }
            return false;
    }
    return false;
}

bool Board::isEmptyBettwen(Coordinate coor, int xDiff, int yDiff, int steps) {
    for (int i = 0; i < steps; i++) {
        if (pieces_[coor.x+xDiff/steps][coor.y+yDiff/steps].getName() != Name::none) {
            return false;
        }
        coor.x += xDiff/steps;
        coor.y += yDiff/steps;
    }
    return true;
}

void Board::updateBoard(const Coordinate& oldCoord, const Coordinate& newCoord) {
    Pieces temp = pieces_[oldCoord.x][oldCoord.y];
    pieces_[oldCoord.x][oldCoord.y].setNameandColor(Name::none, Color::empty);
    pieces_[newCoord.x][newCoord.y] = temp;
}

const bool Board::isKingChecked(const Color& color, const int x, const int y) {
    Coordinate kingCoord(x,y);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Pieces curr = getPiece(Coordinate(i,j));
            if (curr.getName() == Name::none || curr.getColor() == color) continue;
            Color oppColor = color == Color::white ? Color::black : Color::white;
            if (isValidtoMove(Coordinate(i,j), kingCoord, oppColor)) return true;
        }
    }
    return false;
}

const bool Board::hasKing(const Color& color) {
    for (int i = 0; i < 8; i++) {
        for (int j =0; j < 8; j++) {
            Coordinate c(i,j);
            Pieces p = getPiece(c);
            if (p.getName() == Name::king && p.getColor() == color) {
                return true;
            }
        }
    }
    return false;
}

const Pieces& Board::getPiece(const Coordinate& coordinate) {
    int i = coordinate.x;
    int j = coordinate.y;
    return pieces_[i][j];
}

void Board::print() {
    for (int i = 0; i < 8; i++) {
        for (int j =0; j < 8; j++) {
            Coordinate c(i,j);
            Pieces p = getPiece(c);
            std::cout << p << " ";
        }
        std::cout << " " << std::endl;
    }
}

