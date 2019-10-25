//
//  Pieces.cpp
//  Chess
//
//  Created by zili wang on 2019-09-05.
//  Copyright © 2019 Zili. All rights reserved.
//

#include "Pieces.hpp"
#include <iostream>


Pieces::Pieces(Name name, Color color):
    name(name), color(Color::empty) {}

Pieces::~Pieces(){
}

void Pieces::setNameandColor(const Name& newName, const Color& newColor) {
    name = newName;
    color = newColor;
}

const Name& Pieces::getName() {
    return name;
}

const Color& Pieces::getColor() {
    return color;
}

inline std::string colorToString(Color color) {
    switch (color) {
        case Color::white: return "white";
        case Color::black: return "black";
        case Color::empty: return "empty";
    }
}

inline std::string nameToString(Name name) {
    switch (name) {
        case Name::rook: return "rook";
        case Name:: knight: return "knight";
        case Name::bishop: return "bishop";
        case Name::queen: return "queen";
        case Name::king: return "king";
        case Name::pawn: return "pawn";
        case Name::none: return "none";
    }
}

//for debug purpose
std::ostream& operator <<(std::ostream& out, const Pieces& piece) {
    return out << "{ " << nameToString(piece.name) <<
    " , " << colorToString(piece.color) << " }";
}
