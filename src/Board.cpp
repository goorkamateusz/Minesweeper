#include "Board.hpp"
#include "Error.hpp"
#include <random>
#include <time.h>

#include <iomanip>  //to debug
#include <iostream> //to debug
using namespace std;

////----------------------------------------------------------------
const Vector2D Board::AROUND[8] = {               // vector around
    {-1,-1},{0,-1},{1,-1},
    {-1,0},{1,0},
    {-1,1},{0,1},{1,1}
};

////----------------------------------------------------------------
Board::~Board(){
    this->free();
}

////----------------------------------------------------------------
void Board::uncover( const Vector2D& click ){

    //idea optymalise!

    if( this->created() ){

        ///- Nothing do when click on the uncovered
        if( (*this)(click).uncoverAble() ){

            (*this)(click).uncover();
            --this->covered;

            if( (*this)(click).empty() ){
                ///- Uncover around if click on the empty field
                for(uint8_t i=0; i<8; ++i ){
                    if( this->inside( click + Board::AROUND[i] ) )
                        this->uncover( click + Board::AROUND[i] );  //recursive!
                }
            }
            else
                ///- Lose the game when uncover a mine
                if( (*this)(click).mine() )
                    throw EndGame("Boooom!");

            ///- Win the game when uncover every right fields
            if( this->covered == 0 )
                throw EndGame("Win!");
        }
    }
    else {
        ///- Create, randMines and uncover the field (recursive!)
        alloc();
        randMines( click );
        countFields();
        this->uncover( click );
    }
}

////----------------------------------------------------------------
void Board::action( const Vector2D& click ){

    if( (*this)(click).flagged() ){
        ///- If field is flagged, unflag.
        (*this)(click).unflag();
        ++this->mines;
    }
    else {
        ///- If field is covered, flag.
        if( (*this)(click).covered() ){
            (*this)(click).flag();
            --this->mines;
        }
        ///- If field is uncover, uncover around (if it's possible).
        else{
            // uncover around
            uint8_t nflags = 0;         ///< number of flags around

            for(uint8_t i=0; i<8; ++i )
                if( this->inside( click + Board::AROUND[i] ) )
                    if( (*this)(click + Board::AROUND[i] ).flagged() )
                        ++nflags;

            // uncover around is possible
            if( nflags == (*this)(click).val() ){
                for(uint8_t i=0; i<8; ++i )
                    if( this->inside( click + Board::AROUND[i] ) )
                        this->uncover( click + Board::AROUND[i] );
            }

        }
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
    this->covered = size.area() - m;

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
void Board::randMines( const Vector2D& click ){
    /// Rand a position of mines on the board.
    Vector2D pos;
    short unsigned int num_mines = mines;
    unsigned max_att = MAX_ATTEMPTS;

    std::default_random_engine generator( time(NULL) );
    std::uniform_int_distribution<int> distribution_x( 0, size.x-1 );
    std::uniform_int_distribution<int> distribution_y( 0, size.y-1 );

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
void Board::countFields(){

    uint8_t count;                          // counter
    Vector2D pos, around;

    for( pos.x=0; pos.x < size.x; ++pos.x )
        for( pos.y=0; pos.y < size.y; ++pos.y ){

            if( ! (*this)(pos).mine() ){
                count = 0;                      // clear counter

                for(uint8_t i=0; i<8; ++i ){    // check around
                    around = pos + Board::AROUND[i];
                    if( this->inside( around ) )
                        if( (*this)(around).mine() ) ++count;
                }

                (*this)(pos).val( count );      // set values
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
