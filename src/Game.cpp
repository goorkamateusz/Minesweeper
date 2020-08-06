#include "Game.hpp"
#include <sstream>

using namespace std;
using namespace sf;

////----------------------------------------------------------------------
Game::Game( const int argc, const char* const argv[] ){
    int id = 1;
    unsigned int w = DEFAULT_X_SIZE,
                 h = DEFAULT_Y_SIZE,
                 m = DEFAULT_MINE;
    stringstream strm;

    while( id < argc ){

        if( argv[id][0] == '-' ){
            switch( argv[id][1] ){

            ///- `w` - width of the board
            case 'w':
                strm << argv[ ++id ] << ' ';
                strm >> w;
                break;

            ///- `h` - height of the board
            case 'h':
                strm << argv[ ++id ] << ' ';
                strm >> h;
                break;

            ///- `m` - number of mines
            case 'm':
                strm << argv[ ++id ] << ' ';
                strm >> m;
                break;

            ///- Unknow argument
            default:
                cerr << "!!! Warning: unknow input argument" << endl
                     << "! " << argv[id] << endl;
            }
        }
        else {
            //?
        }

        ++id;
    }

    //* Set value
    this->board.set( w, h, m );

}

////----------------------------------------------------------------------
void Game::click( const sf::RenderWindow& window, const sf::Mouse::Button butt ){

    Vector2i mouse_pos = Mouse::getPosition(window);

    if( mouse_pos.x > GUI_MARGIN_T ){       //inside board

        if( this->firstAction( butt ) ){
            ///- First action on the board: uncover the field.
            this->board.uncover( Game::position( mouse_pos ) );
        }
        else {
            if( this->board.created() )
                ///- Second action on the board: flag the field.
                this->board.flag( Game::position( mouse_pos ) );
            else
                ///- If board isn't created, second move is create and uncover too.
                this->board.uncover( Game::position( mouse_pos ) );
        }
    }
    else {                                  // outside board

        //todo click mode button
    }
}

////----------------------------------------------------------------------
bool Game::clockChange() const {
    //todo

    return false;
}


////----------------------------------------------------------------------
Vector2D Game::position( const sf::Vector2i& pos )
{ return Vector2D( pos.x/FIELD_SIZE, (pos.y-GUI_MARGIN_T)/FIELD_SIZE ); }

////----------------------------------------------------------------------
unsigned int Game::width() const
{ return this->board.w()*FIELD_SIZE; }

unsigned int Game::height() const
{ return this->board.h()*FIELD_SIZE + GUI_MARGIN_B + GUI_MARGIN_T; }

////----------------------------------------------------------------------
void Game::draw( sf::RenderTarget& target, sf::RenderStates states ) const {
    this->display.board( target, &this->board );
    // this->display.score( ... ); //todo <- score value
    // this->display.stopwatch( ... ) //todo <- run stopwatch
}




////----------------------------------------------------------------------




////----------------------------------------------------------------------




////----------------------------------------------------------------------




