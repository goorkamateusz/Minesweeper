#include "Display.hpp"
#include "Error.hpp"
#include "Func.hpp"
#include <sstream>

using namespace sf;
using namespace std;

////-----------------------------------------------------
/// Declaration od Template[]
TField* Display::Template[ NUM_FIELD_VIEW ] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};

////-----------------------------------------------------
TField* const Display::pointer( const Field& field ){
    ///- Find the code of field
    short int id;   ///< id of field
    if( field.flagged() )       id = 10;
    else if( field.covered() )  id = 11;
    else                        id = field.val();

    ///- First time create new TField
    if( Display::Template[ id ] == NULL )
        Display::Template[ id ] = new TField( id );

    ///- Return pointer
    return Display::Template[ id ];
}

////-----------------------------------------------------
void Display::config( const Vector2D& size ){
    ///- Load button textures
    flag_texture = LoadTextureFromResource("BFLAG");
    click_texture = LoadTextureFromResource("BCLICK");

    ///- Set positions and default texture of mode button
    mode_butt.setPosition( (size.x*FIELD_SIZE - MODE_BUTT_W)/2, MODE_BUTT_Y  );
    mode_butt.setTexture( this->click_texture );

    ///- Load font
    font = LoadFontFromResource("CONSOLA");

    ///- Score counter text config
    mine_txt.setFont( font );
    mine_txt.setPosition( size.x*FIELD_SIZE - COUNTER_X, COUNTER_Y );
    mine_txt.setCharacterSize( COUNTER_FONT );
    mine_txt.setFillColor( sf::Color::White );
    mine_txt.setStyle( sf::Text::Bold) ;

    ///- Set position and texture of mine counter
    mine_texture = LoadTextureFromResource("MINEC");

    mine_bg.setTexture( mine_texture );
    mine_bg.setPosition( size.x*FIELD_SIZE - COUNTER_X_BG, COUNTER_Y_BG );

    ///- Stopwatch text config
    stopwatch_txt.setFont( font );
    stopwatch_txt.setPosition( STOPWATCH_X, STOPWATCH_Y );
    stopwatch_txt.setCharacterSize( STOPWATCH_FONT );
    stopwatch_txt.setFillColor( sf::Color::White );

    ///- Set position and texture of stopwatch
    stopwatch_texture = LoadTextureFromResource("STOPW");

    stopwatch_bg.setTexture( stopwatch_texture );
    stopwatch_bg.setPosition( STOPWATCH_X_BG, STOPWATCH_Y_BG );

    ///- Load start button
    start_texture = LoadTextureFromResource("STARTI");

    start_butt.setTexture( start_texture );
    start_butt.setPosition( (size.x*FIELD_SIZE)/2 + START_X, START_Y );

}

////-----------------------------------------------------
void Display::changeButt( const bool mode ){
    if( mode )  this->mode_butt.setTexture( this->flag_texture );
    else        this->mode_butt.setTexture( this->click_texture );
}

////-----------------------------------------------------
Display::~Display(){
    ///- Delete Template array
    for( short int i=0; i<NUM_FIELD_VIEW; ++i )
        if( Display::Template[ i ] != NULL )
            delete Display::Template[ i ];
}

////-----------------------------------------------------
void Display::stopwatch( unsigned int seconds ){
    stringstream strm;
    if( seconds / 60 < 10 )     strm << '0';
    strm << seconds / 60 << ':';
    if( seconds % 60 < 10 )     strm << '0';
    strm << seconds % 60;
    stopwatch_txt.setString( strm.str() );
}

////-----------------------------------------------------
void Display::mineCounter( unsigned int mine ){
    stringstream strm;
    strm << mine;
    mine_txt.setString( strm.str() );
}

////-----------------------------------------------------
void Display::draw( sf::RenderTarget& target ) const {
    ///- Mode button draw
    target.draw( mode_butt );

    ///- Score counter draw
    target.draw( mine_bg );
    target.draw( mine_txt );

    ///- Stopwatch draw
    target.draw( stopwatch_bg );
    target.draw( stopwatch_txt );
}

////-----------------------------------------------------
void Display::board( sf::RenderTarget& target, const Board* const board ) const{
    Vector2D pos;
    TField *pointer = Display::pointer( Field() );

    if( ! board->created() ){
        for( pos.y = 0; pos.y < board->h(); ++pos.y ){
            for( pos.x = 0; pos.x < board->w(); ++pos.x ){
                pointer->set( pos );
                target.draw( *pointer );
            }
        }
    }
    else {
        /// Draw every field
        for( pos.y = 0; pos.y < board->h(); ++pos.y ){
            for( pos.x = 0; pos.x < board->w(); ++pos.x ){
                pointer = Display::pointer( (*board)(pos) );
                pointer->set( pos );
                target.draw( *pointer );
            }
        }
    }
}