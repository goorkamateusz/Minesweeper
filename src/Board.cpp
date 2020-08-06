#include "Board.hpp"
#include "Error.hpp"
#include <stdlib.h>
#include <time.h>


using namespace std;

////----------------------------------------------------------------
Board::~Board(){
    alloc( Vector2D(0,0) );     // Delete board array
}

////----------------------------------------------------------------
void Board::create( unsigned int w, unsigned int h, unsigned int m ){
    ///- Set values
    this->alloc( Vector2D( w, h ) );

    ///- Check exceptions
    if( m < MIN_MINES ) throw ErrInput("To least mines!");
    if( m > size.area() - 9 ) throw ErrInput("To much mines!");

    this->mines = m;

    /* Test fragment <---
    for( int i=0; i<10; ++i ){
        (*this)(Vector2D(1,i)).val( i );
        (*this)(Vector2D(1,i)).uncover();
    }
    (*this)(Vector2D(3,3)).flag();
    // ---> */

}

////----------------------------------------------------------------
void Board::alloc( const Vector2D& size_ ){
    /// Delete old board
    if( size.x > 0 && size.y > 0 ){
        for( short int i=0; i<size.y; ++i )
            delete[] this->board[i];

        delete[] this->board;
    }

    /// Create new board
    if( size_.area() > MIN_AREA ){
        this->size = size_;
        this->board = new Field*[ size_.x ];

        if( this->board == NULL ) throw ErrAlloc();

        for( short int i=0; i<size_.x; ++i ){
            this->board[i] = new Field[ size_.y ];
            if( this->board[i] == NULL ) throw ErrAlloc();
        }
    }
}

////----------------------------------------------------------------
//todo make a best rand function!
void Board::randMines( const Vector2D& click ){
    /// Rand a position of mines on the board.
    Vector2D pos;
    short unsigned int num_mines = mines;
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