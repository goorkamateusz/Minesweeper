#include "Board.hpp"
#include "Error.hpp"
#include <stdlib.h>
#include <time.h>

using namespace std;

////----------------------------------------------------------------
Board::~Board(){
    //todo
}

////----------------------------------------------------------------
void Board::alloc( const Vector2D& size_ ){
    /// Delete old board
    if( size.x > 0 && size.y > 0 ){
        for( short int i; i<size.y; ++i )
            delete[] this->board[i];

        delete[] this->board;
    }

    /// Create new board
    this->size = size_;
    this->board = new Field*[ size_.x ];

    if( this->board == NULL ) throw ErrAlloc();

    for( short int i; i<size_.y; ++i ){
        this->board[i] = new Field[ size_.y ];
        if( this->board[i] == NULL ) throw ErrAlloc();
    }
}

////----------------------------------------------------------------
//todo make a best rand function!
void Board::randMines( const Vector2D& click, unsigned num_mines ){
    /// Exception controll.
    if( num_mines < MIN_MINES ) throw ErrInput("To least mines!");
    if( num_mines > size.area() - 9 ) throw ErrInput("To much mines!");

    /// Rand a position of mines on the board.
    Vector2D pos;
    unsigned max_att = MAX_ATTEMPTS;
    srand( time(NULL) + click.area() );

    while( num_mines > 0 ){
        pos.x = (rand() + pos.y) % size.x;
        pos.y = (rand() + pos.x) % size.y;

        if( (*this)( pos ).mine() == false && ! click.adj( pos ) ){
            (*this)( pos ) = FieldCode::Mine;
            --num_mines;
        }
        else {
            if( --max_att ){
                //todo
            }
        }
    }

}