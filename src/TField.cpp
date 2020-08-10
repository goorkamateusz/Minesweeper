#include "TField.hpp"
#include "Error.hpp"
#include "Func.hpp"

////--------------------------------------------
const char* const TField::TEXTURE_ARR[NUM_FIELD_VIEW] = {
    "FE",
    "F1",
    "F2",
    "F3",
    "F4",
    "F5",
    "F6",
    "F7",
    "F8",
    "FM",
    "FF",
    "FC",
};

////--------------------------------------------
TField::TField( const uint8_t id ){
    /// - Load a texture
    texture = LoadTextureFromResource( TField::TEXTURE_ARR[ id ] );

    /// - Create a sprite
    sprite.setTexture( texture );
}