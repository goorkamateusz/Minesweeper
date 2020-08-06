#include "TField.hpp"
#include "Error.hpp"

////--------------------------------------------
const char* const TField::TEXTURE_ARR[NUM_FIELD_VIEW] = {
    "img/empty.png",
    "img/field_1.png",
    "img/field_2.png",
    "img/field_3.png",
    "img/field_4.png",
    "img/field_5.png",
    "img/field_6.png",
    "img/field_7.png",
    "img/field_8.png",
    "img/mine.png",
    "img/flag.png",
    "img/covered.png"
};

////--------------------------------------------
TField::TField( const uint8_t id ){
    /// - Load a texture
    if( ! texture.loadFromFile( TField::TEXTURE_ARR[ id ]) )
        throw ErrSys("Can't load file of texture.");

    /// - Create a sprite
    sprite.setTexture( texture );
}