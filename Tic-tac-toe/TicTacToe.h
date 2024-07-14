/*
* Tic tac toe
* 
* Author: Farhan Syed
* Year: 2024

*/

#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <iostream>
#include <vector>
#include "Vec2d.hpp"

#define MAXBOARDSIZE 140 

// Chess piece, kind of.
class TTTPiece {
private:
    Vec2d<int> m_pos;
    bool m_is_cross, m_placed;

public:
    TTTPiece(const Vec2d<int> & pos, bool is_cross);
    void placeAt(const Vec2d<int> & pos);
    char getMarker() const;
    const Vec2d<int> & getPosition() const;
    bool isPlaced();
};

// Like ChessMove... // (implemented here for convenience. Don't!
struct TTTPiecePlacement {
    Vec2d<int> m_pos;
    bool m_is_cross;
    TTTPiecePlacement(const Vec2d<int> pos, bool is_cross);
    const Vec2d<int> & getPosition()const;
	bool isCross()const;
};

class TicTacToe
{
private:
    std::vector<TTTPiece> m_pieces;
    int m_placed_pieces;
    int m_in_a_row;
    bool m_next_player;    //true: X, false: O
    Vec2d<int> m_board_size;

public:
    enum GameStates {
        PLAYING,
        TIE,
        XWON,
        OWON
    };

    //Yep, you can run tictac on other board sizes. 
    TicTacToe(const Vec2d<int> & board_size, const int & in_a_row);
    
    bool nextPlayer()const;
    char nextMarker()const;

    // Anything on a particular position already? X, O if occupied, or _ if unoccupied.
    char occupied(const Vec2d<int> & p) const;

    // The corresponding in chess is move_piece.
    // PlacePiece does a bunch of tests, and falses out if any of them fails.
    // Otherwise, places a new piece and updates the state machine.
    bool placePiece(const TTTPiecePlacement & ttt_piece_placement);

    // Get the state of the game as an enum value of GAMESTATES
    int gameState() const;
    friend std::ostream& operator<<(std::ostream & out, const TicTacToe & ttt);
};

#endif  // TICTACTOE_H