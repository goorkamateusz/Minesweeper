#include "Board.hpp"
#include "Error.hpp"
#include <random>

#include <iomanip>  //to debug
#include <iostream> //to debug
using namespace std;

////----------------------------------------------------------------
Board::~Board(){
    this->free();
}

////----------------------------------------------------------------
void Board::uncover( const Vector2D& pos ){

    if( this->created() ){

        cout << "JESTEM TU!" << endl;
        this->debug();


    }
    else {
        ///- Create, randMines and uncover the field (recursive!)
        alloc();
        randMines( pos );
        this->uncover( pos );
    }
}

////----------------------------------------------------------------
void Board::set( unsigned int w, unsigned int h, unsigned int m ){
    ///- Check exceptions
    if( m < MIN_MINES )         throw ErrInput("Too least mines!");
    if( m > size.area() - 9 )   throw ErrInput("Too much mines!");

    if( size.area() > MIN_AREA ) throw ErrInput("Too little area!");

    ///- Set values
    this->mines = m;
    this->size = Vector2D( w, h );

    /* Test fragment <---
    for( int i=0; i<10; ++i ){
        (*this)(Vector2D(1,i)).val( i );
        (*this)(Vector2D(1,i)).uncover();
    }
    (*this)(Vector2D(3,3)).flag();
    // ---> */
}

////----------------------------------------------------------------
void Board::free(){
    if( this->board != NULL ){
        for( short int i=0; i<size.y; ++i )
            delete[] this->board[i];

        delete[] this->board;
    }
}

////----------------------------------------------------------------
void Board::alloc(){
    /// Free space
    // this->free();

    if( size.x < 1 || size.y < 1 ) throw ErrSys("001");

    /// Create new board
    this->board = new Field*[ size.x ];
    if( this->board == NULL ) throw ErrAlloc();

    for( int i=0; i<size.x; ++i ){
        this->board[i] = new Field[ size.y ];
        if( this->board[i] == NULL ) throw ErrAlloc();
    }
}

////----------------------------------------------------------------
//todo make a best rand function!
void Board::randMines( const Vector2D& click ){
    /// Rand a position of mines on the board.
    Vector2D pos;
    short unsigned int num_mines = mines;
    unsigned max_att = MAX_ATTEMPTS;

    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution_x( 0, size.x );     //fixme size.x - 1 ???
    std::uniform_int_distribution<int> distribution_y( 0, size.y );

    while( num_mines > 0 ){
        pos.x = distribution_x(generator);
        pos.y = distribution_y(generator);

        if( (*this)( pos ).mine() == false && ! click.adj( pos ) ){
            (*this)( pos ) = FieldCode::Mine;
            --num_mines;
        }
        else {
            if( 0 == --max_att )
                throw ErrSys("Too much attempts to rand location of mines.");
        }
    }

}


////----------------------------------------------------------------
void Board::debug() const {
    cout << "  ";
    for(int x=0;x<size.x;++x) cout << "|" << setw(4) << x << " ";
    cout << endl;
    for(int y=0;y<size.y;++y){
        cout << y << " ";
        for(int x=0;x<size.x;++x)
            cout << (*this)(Vector2D(x,y));
        cout << endl;
    }
}
