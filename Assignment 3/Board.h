//
//  Board.h
//

#pragma once

#include <string>

#include "BoardSize.h"
#include "BoardValue.h"



const int STAR_POINT_SPACING = 6;

//Stones removed record

struct StonesRemoved
{
  int us;  
  int them;
};

//Board class
class Board
{
  private:

int column;

int row;

char value;

char opponentValue = 'O';

int index;

char places[19][19];

int old_value;

int new_value;

char neighbour_value;

bool isAlignedForStarPoint (int index_in) const;

void printRowNumber (int row_in) const;

void printColumnLetters () const;

int capturePlayer (char player_value_in);

bool isInvariantTrue () const;  // new

  public:

Board ();  // was named boardClear, now the default constructor 

Board(const Board& b1); //Copy constructor

char getAt (int row_in, int column_in) const;

void print () const;

int countWithValue (char value_in) const;

int calculateScore (char us_value_in) const;

void setAt (int row_in, int column_in,
            char value_in);

void load (const std::string& filename_in);

StonesRemoved playStone (int row_in, int column_in,
                         char us_value_in);

void replaceAll (char old_value_in,
                 char new_value_in);

void fillConnected (char old_value_in,
                    char new_value_in,
                    char neighbour_value_in);

bool isANeighbourWithValue (int row_in, int column_in,
                            char value_in) const;
};