#include "Game.hpp"
#include "Error.hpp"
#include "Menu.hpp"
#include <sstream>

using namespace std;
using namespace sf;

////----------------------------------------------------------------------
/**
 * \brief Help messege
 */
const char* const HELP_INFO =
    "Minesweeper game by Gorka Mateusz (maatiug).\n"
    "\n"
    "Runing  arguments:\n"
    "arg          | help\n"
    ":-----------:|:--------\n"
    " -w <num>    | width of board (on standard screen max 60)\n"
    " -h <num>    | heigh of boarb (on standard screen max 30)\n"
    " -m <num>    | number of mines\n"
    " -H          | turn on hints in the game\n"
    "\n"
    "example: ./Minesweeper2.exe -w 20 -h 12 -m 60"
    "\n"
    "More you can read in README.md of project!\n"
    "\n"
    "Github: github.com/maatiug/Minesweeper2\n";

////----------------------------------------------------------------------
Game::Game( int argc, char* argv[] ){
    unsigned int w = DEFAULT_X_SIZE,
                 h = DEFAULT_Y_SIZE,
                 m = DEFAULT_MINE;

    /// If user don't give console args, it will open a GUI menu
    if( argc == 1 )
        Menu::handling( argc, argv );


    /// Console arguments:
    int id = 1;
    stringstream strm;

    while( id < argc ){

        if( argv[id][0] == '-' ){
            switch( argv[id][1] ){

            ///- `-w` - width of the board
            case 'w':
                strm << argv[ ++id ] << ' ';
                strm >> w;
                break;

            ///- `-h` - height of the board
            case 'h':
                strm << argv[ ++id ] << ' ';
                strm >> h;
                break;

            ///- `-m` - number of mines
            case 'm':
                strm << argv[ ++id ] << ' ';
                strm >> m;
                break;

            ///- `-H` - hints in the game on
            case 'H':
                this->allowHint = true;
                break;

            case '-':
                ///- `--h`, `--help` flag
                if( argv[id][2] == 'h' ){
                    throw EndGame( HELP_INFO );
                    break;
                }
                //hack: 'else' go to default case

            ///- Unknow argument handling
            default:
                cerr << "!!! Warning: unknow input argument" << endl
                        << "! " << argv[id] << endl;
            }
        }
        else {
            cerr << "!!! Warning: unknow input argument" << endl
                    << "! " << argv[id] << endl;
        }

        ++id;
    }

    /// \post
    ///- Config Board
    this->board.set( w, h, m );

    ///- Config Display
    this->display.config( Vector2D(w,h) );

    ///- Init values
    this->buttRev = false;
}

////----------------------------------------------------------------------
void Game::finish(){
    running = false;                ///- Set running to false
}

////----------------------------------------------------------------------
void Game::start(){
    ///- Stopwatch clear
    clock.restart();
    stopwatch = 0;

    ///- Clear board
    this->board.restart();          ///- Restart the board

    ///- Start running mode
    running = true;
}

////----------------------------------------------------------------------
void Game::click( const sf::RenderWindow& window, const sf::Mouse::Button butt ){

    Vector2i mouse_pos = Mouse::getPosition(window);

    ///- Check the click is in the window
    if( mouse_pos.x < 0 || mouse_pos.x > width() ) return;
    if( mouse_pos.y < 0 || mouse_pos.y > height() ) return;

    if( this->isOn() ){

        if( mouse_pos.y > GUI_MARGIN_T ){       //inside board

            if( this->firstAction( butt ) ){
                ///- First action on the board: uncover the field.
                if( ! this->board.uncover( Game::position(mouse_pos) ) ) return;
            }
            else {
                if( this->board.created() ){
                    ///- Second action on the covered field: flag the field.
                    /// If field is uncovered: if it's possible uncover fields around.
                    if( ! this->board.action( Game::position(mouse_pos) ) ) return;
                }
                else{
                    ///- If board isn't created, second move is create and uncover too.
                    if( ! this->board.uncover( Game::position(mouse_pos) ) ) return;
                }
            }

            ///- After correct move:
            lastClickTime = stopwatch;
            display.hideHint();

        }
        else {                                  // outside board (top bar)
            buttRev = ! buttRev;
            this->display.changeButt( buttRev );
        }
    }
    else {
        ///- Start the game
        this->start();

        ///- If clicked on the board, uncover fields yet
        if( mouse_pos.y > GUI_MARGIN_T ) this->click( window, butt );
    }
}

////----------------------------------------------------------------------
Vector2D Game::position( const sf::Vector2i& pos )
{ return Vector2D( pos.x/FIELD_SIZE, (pos.y-GUI_MARGIN_T)/FIELD_SIZE ); }

////----------------------------------------------------------------------
void Game::draw( sf::RenderTarget& target, sf::RenderStates states ) const {
    this->display.board( target, &this->board );
    this->display.draw( target );

    if( ! this->isOn() ) this->display.drawStart( target );
}

////----------------------------------------------------------------------
void Game::update(){
    ///- Update info in the window
    this->display.mineCounter( this->board.noFlaggedMines() );
    this->display.stopwatch( this->time() );

    ///- Check the hint
    if( allowHint ){

        if( stopwatch - lastClickTime > HINT_TIME && display.hintPos == NULL ){
            lastClickTime = stopwatch;      //to delay serching hint
            this->board.hint( this->display.hintPos );

            /* test: autoplay
            if( this->display.hintPos != NULL ){
                this->board.uncover( *(this->display.hintPos) );
                delete this->display.hintPos;
                this->display.hintPos = NULL;
            }
            // test end */
        }
    }
}