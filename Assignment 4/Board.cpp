#include "Board.h"
#include <cassert>

Board::Board() {
    // Initialize all stones to the empty value
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            stones[i][j] = BOARD_VALUE_EMPTY;
        }
    }
}

void Board::placeStone(int row, char col, char stone) {
    // Check if the row and column values are within the valid range
    if (row < 1 || row > BOARD_SIZE || col < BOARD_MIN_COL || col > BOARD_MAX_COL) {
        throw std::out_of_range("Invalid row or column value");
    }

    // Check if the stone value is valid
    if (!isValidBoardValue(stone)) {
        throw std::invalid_argument("Invalid stone value");
    }

    // Place the stone at the given row and column 
    stones[row-1][col-BOARD_MIN_COL] = stone;
}

char Board::getStone(int row, char col) const {
    // Check if the row and column values are within the valid range
    if (row < 1 || row > BOARD_SIZE || col < BOARD_MIN_COL || col > BOARD_MAX_COL) {
        throw std::out_of_range("Invalid row or column value");
    }

    // Return the stone at the given row and column
    return stones[row-1][col-BOARD_MIN_COL];
}

bool Board::isValidBoardValue(char value) const {
    return (value == BOARD_VALUE_EMPTY ||
            value == BOARD_VALUE_BLACK ||
            value == BOARD_VALUE_WHITE ||
            value == BOARD_VALUE_MARKED);
}

void Board::fillConnected(char old_value_in, char new_value_in, char neighbour_value_in) {
    assert(isValidBoardValue(old_value_in) && "Invalid old value");
    assert(isValidBoardValue(new_value_in) && "Invalid new value");
    assert(isValidBoardValue(neighbour_value_in) && "Invalid neighbour value");

    bool keep_going = true;
    while (keep_going) {
        keep_going = false;
        for (int r = 0; r < BOARD_SIZE; r++) {
            for (int c = 0; c < BOARD_SIZE; c++) {
                if (stones[r][c] == old_value_in ||
                    (isANeighbourWithValue(r, c, neighbour_value_in) && stones[r][c] == old_value_in)) {
                    stones[r][c] = new_value_in;
                    keep_going = true;
                }
            }
        }
    }
}

// Helper function to check if a neighbour has the given value
bool Board::isANeighbourWithValue(int row, int col, char value) const {
    // Check the neighbouring cells
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) {
                // Skip the current cell
                continue;
            }
            int new_row = row + i;
            int new_col = col + j;
            if (new_row >= 0 && new_row < Board::BOARD_SIZE && new_col >= 0 && new_col < Board::BOARD_SIZE) {
                if (stones[new_row][new_col] == value) {
                    return true;
                }
            }
        }
    }
    return false;
}
