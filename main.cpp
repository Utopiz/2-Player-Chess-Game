//
//  main.cpp
//  Chess
//
//  Created by zili wang on 2019-09-05.
//  Copyright © 2019 Zili. All rights reserved.
//

#include <iostream>
#include "Board.hpp"
#include "Pieces.hpp"

int main(int argc, const char * argv[]) {
    using namespace std;
    cout << "Are you ready to play a game (true/false) ?" << endl;
    string isPlay;
    cin >> isPlay;
    while (isPlay == "true"){
        Board b;
        b.initializeBoard();
        b.print();
        Color player = Color::white;
        while(b.hasKing(player)) {
            if (player == Color::white) {
                cout << "White Turn: ";
            } else {
                cout << "Black Turn: ";
            }
            cout << "Make a move (oldX oldY newX newY)" << endl;
            int oldx; int oldy; int newx; int newy;
            cin >> oldx >> oldy >> newx >> newy;
            while (!b.isValidtoMove(Coordinate(oldx,oldy),Coordinate(newx,newy),player)) {
                cout << "Invalid move! Make a move again (oldX oldY newX newY)" << endl;
                cin >> oldx >> oldy >> newx >> newy;
            }
            b.updateBoard(Coordinate(oldx,oldy),Coordinate(newx,newy));
            b.print();
            player = player == Color::white ? Color::black : Color::white;
        }
        if (player == Color::white) {
            cout << "Black win! ";
        } else {
            cout << "White win! ";
        }
        cout << "Want to play again (true/false) ?" << endl;
        cin >> isPlay;
    }
    return 0;
}
