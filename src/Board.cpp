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
bool Board::uncover( const Vector2D& click ){

    if( this->created() ){

        ///- Nothing do when click on the uncovered
        if( (*this)(click).covered() ){

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
                if( (*this)(click).mine() ){
                    this->uncoverAll();
                    throw EndGame("Boooom!");
                }

            ///- Win the game when uncover every right fields
            if( this->covered == 0 ){
                this->flagAll();
                this->mines = 0;
                throw EndGame("Win!");
            }
        }
        else return false;      // move unavailable
    }
    else {
        ///- Create, randMines and uncover the field (recursive!)
        alloc();
        randMines( click );
        calcFields();
        this->uncover( click );

        /* Test fragment <---
        for( int i=0; i<10; ++i ){
            (*this)(Vector2D(1,i)).val( i );
            (*this)(Vector2D(1,i)).uncover();
        }
        (*this)(Vector2D(3,3)).flag();
        // ---> */
    }

    return true;
}

////----------------------------------------------------------------
bool Board::action( const Vector2D& click ){

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
            uint8_t nflags = 0;         // number of flags around

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
            else
                return false;   //action is unavailable!
        }
    }

    return true;
}

////----------------------------------------------------------------
bool Board::hint( Vector2D*& pos ) const {

    ///- Clear hint position
    if( pos != NULL ){
        delete pos;
        pos = NULL;
    }

    Vector2D vec, next;
    Field value;
    uint8_t probably_mine, hidden;
    //** Bool array of probable position mines
    bool *mines_arr = new bool[ size.x * size.y ];

    // Set false on the whole mines_arr array
    for( short int i=0; i < (size.x * size.y); ++i )
        mines_arr[i] = false;

    ///- Find probably mines position
    for( next.x = 0; next.x < size.x; ++next.x )
        for( next.y = 0; next.y < size.y; ++next.y ){

            if( (*this)( next ).uncovered() ){              // uncovered
                if( (*this)( next ).empty() ) continue;     // and not empty

                // count all of uncovered fields around
                hidden = 0;
                for( uint8_t i=0; i<8; ++i ){
                    vec = next + Board::AROUND[i];

                    if( this->inside( vec ) )               // inside the board
                        if( (*this)( vec ).hidden() )       // count hidden
                            ++hidden;
                }

                // if hidden == value then all of them is probably mines
                // hidden = covered + flagged
                if( hidden == (*this)( next ).val() )
                    for( uint8_t i=0; i<8; ++i ){
                        vec = next + Board::AROUND[i];

                        if( this->inside( vec ) )
                            if( (*this)( vec ).hidden() )
                                mines_arr[ vec.y*size.x + vec.x ] = true;
                    }
            }
        }

    /* test: display mines_arr
    for( next.y = 0; next.y < size.y; ++next.y ){
        for( next.x = 0; next.x < size.x; ++next.x )
            std::cout << mines_arr[ next.y*size.x + next.x ] << " ";
        std::cout << std::endl;
    } // test end */

    ///- Find safe position
    for( next.x = 0; next.x < size.x; ++next.x )
        for( next.y = 0; next.y < size.y; ++next.y ){

            if( (*this)( next ).uncovered() ){              // uncovered
                if( (*this)( next ).empty() ) continue;     // and not empty

                // count all flag around
                probably_mine = 0;
                for( uint8_t i=0; i<8; ++i ){
                    vec = next + Board::AROUND[i];

                    if( this->inside( vec ) )            // inside
                        if( mines_arr[ vec.y*size.x + vec.x ] )
                            ++probably_mine;
                }

                // if probably_mine == value then covered and ! mines_arr[] fields are safe
                if( probably_mine == (*this)( next ).val() )
                    for( uint8_t i=0; i<8; ++i ){
                        vec = next + Board::AROUND[i];

                        if( this->inside( vec ) )
                            if( ! mines_arr[ vec.y*size.x + vec.x ] && (*this)( vec ).covered() ){
                                // found the hint
                                pos = new Vector2D(vec);
                                delete[] mines_arr;
                                return true;
                            }
                    }
            }
        }

    // end of fun.
    delete[] mines_arr;
    return false;
}


void Board::set( unsigned int w, unsigned int h, unsigned int m ){
    ///- Check exceptions
    if( m < MIN_MINES )         throw ErrInput("Too least mines!");
    if( m > size.area() - 9 )   throw ErrInput("Too much mines!");

    if( size.area() > MIN_AREA ) throw ErrInput("Too little area!");

    ///- Set values
    this->mines = m;
    this->mines_init = m;
    this->size = Vector2D( w, h );
    this->covered = size.area() - m;
}

////----------------------------------------------------------------
void Board::restart(){
    /// \post
    ///- Free board
    this->free();

    ///- Restart covered value
    this->mines = this->mines_init;
    covered = size.area() - this->mines_init;
}

////----------------------------------------------------------------
void Board::free(){
    if( this->board != NULL ){
        for( short int i=0; i<size.y; ++i )
            delete[] this->board[i];

        delete[] this->board;
    }
    this->board = NULL;
}

////----------------------------------------------------------------
void Board::alloc(){
    if( size.x < 1 || size.y < 1 ) throw ErrSys("ALLOC 001");

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
void Board::calcFields(){

    uint8_t count;                          // counter of mines around
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
void Board::uncoverAll(){
    Vector2D pos;
    for(; pos.x < size.x; ++pos.x )
        for( pos.y=0; pos.y < size.y; ++pos.y )
            (*this)(pos).uncover();
}

////----------------------------------------------------------------
void Board::flagAll(){
    Vector2D pos;
    for(; pos.x < size.x; ++pos.x )
        for( pos.y=0; pos.y < size.y; ++pos.y )
            if( (*this)(pos).mine() ) (*this)(pos).flag();
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
