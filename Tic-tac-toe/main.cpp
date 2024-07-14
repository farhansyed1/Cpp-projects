/*
* Tic tac toe
* 
* Author: Farhan Syed
* Year: 2024

Compile: g++ -o main main.cpp TicTacToe.cpp

*/

#include <iostream>
#include <cstdlib>

#include "Vec2d.hpp"
#include "TicTacToe.h"

int main(int argc, char ** argv)
{
    int board_size = 3;
    int winning_length = 3;
    if (argc > 1 && atoi(argv[1]) > 3 && atoi(argv[1]) < MAXBOARDSIZE)
        board_size = atoi(argv[1]);
    if (argc > 2 && atoi(argv[2]) > 3 && atoi(argv[2]) <= board_size)
        winning_length =  atoi(argv[2]);

    int state;

    // Create a new game. 
    TicTacToe ttt(Vec2d<int>(board_size, board_size), winning_length);
    std::cout << "Get " << winning_length << " in a row to win!\n";

    // Run the game
    while ( (state = ttt.gameState()) == ttt.PLAYING) {
        // Print the board
        std::cout << ttt << "\n";
        std::cout << "Enter your next {X and Y} position for " << ttt.nextMarker() << "\n";

        // Take in a new marker position, either on one or two rows
        Vec2d<int> new_position;
        std::cin >> new_position.x;
        std::cin >> new_position.y;
        TTTPiecePlacement newPlacement(new_position, ttt.nextPlayer());
        
        // Place marker on board.
        if (!ttt.placePiece(newPlacement)) {
            std::cout << "\n" << "Position off the charts, or other oddities. Try again?" << "\n\n";
        }
    }
   
    // Print out the final board and winner
    std::cout << "Final board!\n" << ttt << "\n\nWinner? ";
    switch (state) {
        case ttt.TIE: std::cout << "Nope, it's a tie.\n\n\n"; break;
        case ttt.XWON: std::cout << "X won!\n\n\n"; break;
        case ttt.OWON: std::cout << "O won!\n\n\n"; break;
        default: break;
    }
    return 0;
}
