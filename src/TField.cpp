#include "TField.hpp"
#include "Error.hpp"

////--------------------------------------------
const char* const TField::TEXTURE_ARR[NUM_FIELD_VIEW] = {
    "gui/empty.png",
    "gui/field_1.png",
    "gui/field_2.png",
    "gui/field_3.png",
    "gui/field_4.png",
    "gui/field_5.png",
    "gui/field_6.png",
    "gui/field_7.png",
    "gui/field_8.png",
    "gui/mine.png",
    "gui/flag.png",
    "gui/covered.png"
};

////--------------------------------------------
TField::TField( const uint8_t id ){
    /// - Load a texture
    if( ! texture.loadFromFile( TField::TEXTURE_ARR[ id ]) )
        throw ErrSys("Can't load file of texture.");

    /// - Create a sprite
    sprite.setTexture( texture );
}