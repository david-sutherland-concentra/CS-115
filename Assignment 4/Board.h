#ifndef BOARD_H
#define BOARD_H

#include <stdexcept>

class Board {
public:
    static const int BOARD_SIZE = 19;
    static const char BOARD_MIN_COL = 'A';
    static const char BOARD_MAX_COL = 'U';
    static const char BOARD_VALUE_EMPTY = '.';
    static const char BOARD_VALUE_BLACK = 'O';
    static const char BOARD_VALUE_WHITE = '@';
    static const char BOARD_VALUE_MARKED = '#';
    char stones[BOARD_SIZE][BOARD_SIZE];
    
    Board();
    void placeStone(int row, char col, char stone);
    char getStone(int row, char col) const;
    bool isValidBoardValue(char value) const;
    void fillConnected(char old_value_in, char new_value_in, char neighbour_value_in);
    bool isANeighbourWithValue(int row, int col, char value) const;

private:
    
};

#endif // BOARD_H
