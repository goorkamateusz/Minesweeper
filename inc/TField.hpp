#pragma once

#include "SFML/Graphics.hpp"
#include "Const.hpp"
#include "Vector2D.hpp"
#include <stdint.h>

/**
 * \brief Templete of field view.
 *
 * \see Display
 */
class TField : public sf::Drawable {
private:
    sf::Texture texture;    ///< Texture of field
    sf::Sprite sprite;      ///< Sprite of field

public:
    TField() = delete;

    /**
     * \brief Construct a new TField object
     * \param id - code of field.
     */
    TField( const uint8_t id );

    /**
     * \brief Set position.
     * \param pos -
     */
    inline void set( const Vector2D& pos )
    { sprite.setPosition( pos.x*FIELD_SIZE,  pos.y*FIELD_SIZE + GUI_MARGIN_T ); }

    /**
     * \brief Set a hint style
     */
    inline void hint()
    {
        sprite.setScale( 0.9, 0.9 );
    }

    /**
     * \brief Remove hint style
     */
    inline void normal()
    {
        sprite.setScale( 1, 1 );
    }

public:
    /**
     * \brief Draw method
     * \param target -
     * \param state -
     */
    inline void draw( sf::RenderTarget& target, sf::RenderStates state ) const override
    { target.draw( sprite ); }


public:
    /**
     * \brief Array of texture file path.
     */
    static const char* const TEXTURE_ARR[ NUM_FIELD_VIEW ];

};