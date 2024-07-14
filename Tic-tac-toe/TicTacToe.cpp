/*
* Tic tac toe
* 
* Author: Farhan Syed
* Year: 2024

*/

#include <iomanip>
#include <array>

#include "TicTacToe.h"

// TTTPiece
TTTPiece::TTTPiece(const Vec2d<int> & pos, bool is_cross)
    : m_pos(pos), m_is_cross(is_cross), m_placed(false) {}
void TTTPiece::placeAt(const Vec2d<int> & pos) {
    m_pos = pos;
    m_placed = true;
}
char TTTPiece::getMarker() const { return (m_is_cross) ? 'X' : 'O'; }
const Vec2d<int> & TTTPiece::getPosition() const { return m_pos; }
bool TTTPiece::isPlaced() { return m_placed; }



// TTTPiecePlacement
TTTPiecePlacement::TTTPiecePlacement(const Vec2d<int> pos, bool is_cross)
    : m_pos(pos), m_is_cross(is_cross) {}
const Vec2d<int> & TTTPiecePlacement::getPosition() const { return m_pos; }
bool TTTPiecePlacement::isCross()const { return m_is_cross; }



// Main game, TicTacToe
TicTacToe::TicTacToe(const Vec2d<int>& board_size, const int& in_a_row)
    : m_placed_pieces(0)
    , m_in_a_row(in_a_row)
    , m_next_player(true)
    , m_board_size(board_size) {}

bool TicTacToe::nextPlayer()const { return m_next_player; }
char TicTacToe::nextMarker()const { return (m_next_player) ? 'X' : 'O'; }

char TicTacToe::occupied(const Vec2d<int> & p) const {
    // The position should be in the board...
    if ((Vec2d<int>(0, 0) <= p) && (p < m_board_size)) {
        for (auto& tttp : m_pieces) {
            if (tttp.getPosition() == p) return tttp.getMarker();
        }
    }
    return '_';
}

bool TicTacToe::placePiece(const TTTPiecePlacement & ttt_piece_placement) {
    // Make sure there's nothing already there.
    auto check_piece_position_collision = [&](const std::vector<TTTPiece>& pieces) {
        for (auto& p : pieces)
            if (p.getPosition() == ttt_piece_placement.getPosition())
                return false;
        return true;
    };
  
    // Correct player?
    if (ttt_piece_placement.isCross() != m_next_player) return false;

    // Valid location?
    Vec2d<int> pPos = ttt_piece_placement.getPosition();
    if (! ( (Vec2d<int>(0, 0) <= pPos) && (pPos < m_board_size)) ) return false;

    // Does the new piece collide with any one already placed?
    if (!check_piece_position_collision(m_pieces))
        return false;
	
    // If not, place a new piece on the "board", aka list of pieces. The board is a lie...
    m_pieces.push_back(TTTPiece(ttt_piece_placement.getPosition(), ttt_piece_placement.isCross()));

    ++m_placed_pieces;
    m_next_player = !m_next_player;
    return true;
}

int TicTacToe::gameState() const {
    // Make sure the game is still valid to play and there is no winner.
    // Find a bunch of positions in a row direction of piece type.
    auto findRow = [&](const TTTPiece& piece, const Vec2d<int>& scan_dir, char marker) {
        std::vector<Vec2d<int>> in_row;
        for (int i = -m_in_a_row + 1; i < m_in_a_row; ++i) {
            auto position = piece.getPosition() + scan_dir * i;
            if (occupied(position) == piece.getMarker() && piece.getMarker() == marker) {
                in_row.push_back(position);
                if (in_row.size() == m_in_a_row)
                    return in_row;
            }
            else
                in_row.clear();
        }
        return in_row;
    };
	
    // Go through all directions, find any longest chain of same marker
    std::vector<Vec2d<int>> directions = { {0,1}, {1,1}, {1,0}, {1,-1} };
    auto check_rows_for_pieces = [&](char marker) {
        std::vector<Vec2d<int>> longest_row;
        for (auto& p : m_pieces) {
            for (auto& d : directions) {
                auto in_row = findRow(p, d, marker);
                if (in_row.size() == m_in_a_row) {
                    // Yup, we have a winner.
                    return in_row;
                }
                else if (in_row.size() > longest_row.size()) {
                    longest_row = in_row;
                }
            }
        }
        return longest_row;
    };

    // Check winner
    auto longest_cross_row = check_rows_for_pieces('X');
    auto longest_o_row = check_rows_for_pieces('O');

    if (longest_cross_row.size() >= m_in_a_row) return XWON;
    if (longest_o_row.size() >= m_in_a_row) return OWON;

    if (m_placed_pieces == m_board_size.x * m_board_size.y) return TIE;

    return PLAYING;
}

// local help function
static std::array<int, MAXBOARDSIZE> calcNrDigits() {
    std::array<int, MAXBOARDSIZE> veks{};
    int nr_digits = 1;
    int pot10 = 10;
    for (int i(0); i < MAXBOARDSIZE; ++i) {
        if (i == pot10) {
            ++nr_digits;
            pot10 *= 10;
        }
        veks[i] = nr_digits;
    }
    return veks;
}
static std::array<int, MAXBOARDSIZE> nr_digits = calcNrDigits();

std::ostream& operator<<(std::ostream& out, const TicTacToe& ttt) {
    int colSize = nr_digits[ ttt.m_board_size.x ];
    out << "Current Board:\n" << std::setw( colSize + 3 ) << 0;
    for (int i = 1; i < ttt.m_board_size.x; ++i) {
        std::cout << std::setw( 3 ) << i;
    }
    std::cout << "\n";
    for (int y = 0; y < ttt.m_board_size.y; ++y) {
        std::cout << std::setw( colSize ) << y << ": ";
      
        for (int x = 0; x < ttt.m_board_size.x; ++x) {
            out << ttt.occupied(Vec2d<int>(x, y)) << "  ";
        }
        out << "\n";
    }
    return out;
}