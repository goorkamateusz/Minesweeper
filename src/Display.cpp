#include "Display.hpp"

////-----------------------------------------------------
/// Declaration od Template[]
TField* Display::Template[ NUM_FIELD_VIEW ] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};

////-----------------------------------------------------
TField* const Display::pointer( const Field& field ){
    ///- Find the code of field
    short int id;   ///< id of field
    if( field.flaged() )        id = 10;
    else if( field.covered() )  id = 11;
    else                        id = field.val();

    ///- First time create new TField
    if( Display::Template[ id ] == NULL )
        Display::Template[ id ] = new TField( id );

    ///- Return pointer
    return Display::Template[ id ];
}

////-----------------------------------------------------
Display::Display(){
    //todo konstruktor - tworzenie zegara
    //todo konstr. - tworzenie licznika punktow
}

////-----------------------------------------------------
Display::~Display(){
    ///- Delete Template array
    for( short int i=0; i<NUM_FIELD_VIEW; ++i )
        delete Display::Template[ i ];
}

////-----------------------------------------------------
void Display::stopwatch( sf::RenderTarget& target, unsigned int seconds ) const{
    //todo
}

////-----------------------------------------------------
void Display::score( sf::RenderTarget& target, unsigned int score ) const{
    //todo
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