//
//  Board.h
//

#include "Board.h"

#include <cassert>
#include <iostream>
#include <iomanip>
#include <fstream>

#include "BoardSize.h"
#include "BoardValue.h"

using namespace std;


char Board::getAt (int row_in, int column_in) const
{
// assert(isInvariantTrue ());
	assert(isOnBoard(row_in, column_in));

	return places[row_in][column_in];
}

int Board::calculateScore (char us_value_in) const
{
//  us_value_in = value; 
//  assert(isInvariantTrue());

  char other_value;
  if (us_value_in == BOARD_VALUE_BLACK)
  {
    other_value = BOARD_VALUE_WHITE;
  }
  else if (us_value_in == BOARD_VALUE_WHITE)
  {
    other_value = BOARD_VALUE_BLACK;
  }

  Board copy = *this;

  copy.fillConnected(other_value, other_value, us_value_in);

  copy.fillConnected(us_value_in, us_value_in, other_value);

  int counter = 0;
  
	for(int r = 0; r < BOARD_SIZE; r++)
	{
		for(int c = 0; c < BOARD_SIZE; c++)
		{
			if (copy.places[r][c] == us_value_in)
        {
          counter++;
        }
		}
	}
  //assert(isInvariantTrue());
  return counter;
}

void Board::setAt (int row_in, int column_in, char value_in)
{
 assert(isInvariantTrue ());
	assert(isOnBoard(row_in, column_in));
	assert(isBoardValueValid(value_in));

places[row_in][column_in] = value_in;

 assert(isInvariantTrue ());
}

Board::Board () //***** Change to defaul constructor
{
  row = 0;
  column = 0;
  value = ' ';
  opponentValue = ' ';
  index = 0;
  old_value = 0;
  new_value = 0;
  neighbour_value = ' ';
	for(int r = 0; r < BOARD_SIZE; r++)
	{
		for(int c = 0; c < BOARD_SIZE; c++)
		{
			places[r][c] = BOARD_VALUE_EMPTY;
		}
	}
  assert(isInvariantTrue ());
}

Board::Board(const Board& b1) // Copy constructor I don't even think I need this 
{
  for(int r = 0; r < BOARD_SIZE; r++)
	{
		for(int c = 0; c < BOARD_SIZE; c++)
		{
			places[r][c] = b1.places[r][c];
		}
	}
}

void Board::load (const string& filename_in)
{
		assert(filename_in != "");

	// open file with name filename_in
	// fin will read from that file
	// use fin like you use cin
	ifstream fin(filename_in);

	if(!fin)
	{
		cout << "Error: Could not open file \"" << filename_in << "\"" << endl;
		return;  // end function immediately
	}

	// read in the board size
	string line;
	int board_size_read;
	fin >> board_size_read;
	if(!fin)
	{
		cout << "Error: File \"" << filename_in << "\" does not start with board size" << endl;
		return;  // end function immediately
	}
	if(board_size_read != BOARD_SIZE)
	{
		cout << "Error: File \"" << filename_in << "\" has board size "
		     << board_size_read << ", but must be " << BOARD_SIZE << endl;
		return;  // end function immediately
	}
	assert(fin);
	string dummy;
	getline(fin, dummy);  // throw away whatever else is on the line

	// read in board state
	bool is_print_error = true;
	for(int r = 0; r < BOARD_SIZE; r++)
	{
		string line;
		getline(fin, line);
		if(!fin)
		{
			if(is_print_error)
			{
				cout << "Error: Could not read line " << r
				     << " of file \"" << filename_in << "\"" << endl;
				cout << "       Replacing with '.'s" << endl;
				is_print_error = false;
			}
			line = string(BOARD_VALUE_EMPTY, BOARD_SIZE);  // set to '.'s
		}
		else if((int)(line.length()) < BOARD_SIZE)
		{
			if(is_print_error)
			{
				cout << "Error: Line " << r << " of file \"" << filename_in
				     << "\" only contains " << line.length()
				     << " / " << BOARD_SIZE << " characters" << endl;
				cout << "       Adding '.'s to end" << endl;
				is_print_error = false;
			}
			line += string(BOARD_VALUE_EMPTY, BOARD_SIZE);  // add '.'s
		}

		for(int c = 0; c < BOARD_SIZE; c++)
		{
			if(isBoardValueValid(line[c]))
				setAt(r, c, line[c]);
			else
			{
				setAt(r, c, BOARD_VALUE_EMPTY);
				if(is_print_error)
				{
					cout << "Error: Line " << r << ", character " << c
						 << " of file \"" << filename_in
						 << "\" is an invalid '" << line[c] << "' character" << endl;
					cout << "       Substituting '" << BOARD_VALUE_EMPTY << "'" << endl;
					is_print_error = false;
				}
			}
		}
	}
assert(isInvariantTrue ());
	// file will be closed automatically when fin goes out of scope
}

StonesRemoved Board::playStone (int row_in, int column_in, char us_value_in)
{
//  assert(isInvariantTrue ());
//  assert(isOnBoard(row_in, column_in));
//  assert(places[row_in][column_in] == BOARD_VALUE_EMPTY);
//  assert(isBoardValuePlayer(us_value_in)); // Says I have a function for this but idk which one

  //Add Stone for current player
  places[row_in][column_in] = us_value_in;

  
  

  StonesRemoved result;

  return result;
  
  }

int Board::countWithValue (char value_in) const
{
	assert(isBoardValueValid(value_in));

	int count = 0;

	for(int r = 0; r < BOARD_SIZE; r++)
	{
		for(int c = 0; c < BOARD_SIZE; c++)
		{
			if(getAt(r, c) == value_in)
				count++;
		}
	}

	return count;
}

void Board::print () const
{
//assert(isInvariantTrue ());
	printColumnLetters();

	for(int r = 0; r < BOARD_SIZE; r++)
	{
		printRowNumber(r);
		cout << " ";

		for(int c = 0; c < BOARD_SIZE; c++)
		{
			if(getAt(r, c) == BOARD_VALUE_EMPTY &&
			  isAlignedForStarPoint(r) &&
			   isAlignedForStarPoint(c))
			{
				cout << "*";
			}
			else
				cout << getAt(r, c);
			cout << " ";
		}

		printRowNumber(r);
		cout << endl;
	}

	printColumnLetters();
}

bool Board::isAlignedForStarPoint (int index_in) const
{
	assert(index_in >= 0);

	int center_modulus = (BOARD_SIZE / 2) % STAR_POINT_SPACING;
	int index_modulus  = index_in         % STAR_POINT_SPACING;

	if(index_modulus == center_modulus)
		return true;
	else
		return false;
}

void Board::printRowNumber (int row_in) const
{
	cout << right << setw(2) << row_in;
}

void Board::printColumnLetters () const
{
	cout << "   ";  // space for row numbers

	// column headings
	for(int c = 0; c < BOARD_SIZE; c++)
	{
		char letter = 'A' + c;
		if(letter >= 'I')
			letter++;
		if(letter >= 'O')
			letter++;
		cout << letter << " ";
	}

	// don't need to leave space at end of line
	cout << endl;
}

int Board::capturePlayer (char player_value_in)
{
  int counter = 0;
  	for(int r = 0; r < BOARD_SIZE; r++)
	{
		for(int c = 0; c < BOARD_SIZE; c++)
		{
			if (places[r][c] == player_value_in)
      {
        player_value_in = BOARD_VALUE_MARKED;
        counter++;
        fillConnected (player_value_in, BOARD_VALUE_MARKED, BOARD_VALUE_EMPTY);
      }
		}
	}
  return counter;
}

bool Board::isInvariantTrue () const
{
if (column <= BOARD_SIZE && column >=0 && row <= BOARD_SIZE && row >=0)
{
  if (places[row][column] == BOARD_VALUE_EMPTY)
    return true;
  }
  return false;
}

void Board::replaceAll (char old_value_in, char new_value_in)
{
//  assert(isInvariantTrue());
  for (int r = 0; r < 19; r++)
    for (int c = 0; c < 19; c++ )
      {
        if ( places[c][r] == old_value_in)
          places[c][r] = new_value_in;
      }
}

void Board::fillConnected (char old_value_in,
                    char new_value_in,
                    char neighbour_value_in)
{
bool keep_going = true;  
  
  while(keep_going) {
     
 keep_going = false;
     
    for (int r = 0; r < 19; r++)
    {
    for (int c = 0; c < 19; c++ )
      {
          if (places[r][c] == old_value_in && (isANeighbourWithValue(r, c, neighbour_value_in) || isANeighbourWithValue(r, c, new_value_in))){
            places[r][c] = new_value_in;
            keep_going = true;
          }
        }
      }
    }
  }


bool Board::isANeighbourWithValue (int row_in, int column_in, char value_in) const
{
    
    if (row_in > 0 && places[row_in-1][column_in] == value_in)
    {
      return true;
    }
    if (row_in < 18 && places[row_in+1][column_in] == value_in)
    {
      return true;
    }
    if (column_in > 0 && places[row_in][column_in-1] == value_in)
    {
      return true;
    }
    if (column_in < 18 && places[row_in][column_in+1] == value_in)
    {
      return true;
    }
      return false;
  }

