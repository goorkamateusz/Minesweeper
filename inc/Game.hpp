#pragma once

#include "Board.hpp"
#include "Display.hpp"
#include "Const.hpp"
#include "SFML/Graphics.hpp"

/**
 * \brief Interface and game organization.
 */
class Game : public sf::Drawable {
private:
    Board board;          ///< Board of game
    Display display;      ///< Care about display a game

    bool buttRev {false}; ///< Current button mode. 0 - normal, 1 - revers button.


public:
    Game() = delete;

    /**
     * \brief Construct a new Game object
     * \param argc - number of args
     * \param argv - values of argso
     */
    Game( const int argc, const char* const argv[] );

    /**
     * \brief Destroy the Game object
     */
    ~Game() = default;

public:
    /**
     * \brief Click managment
     * \param window - window handle
     * \param butt - mouse button
     */
    void click( const sf::RenderWindow& window, const sf::Mouse::Button butt );

    /**
     * \brief Have clock been changed?
     * \return true -
     * \return false -
     */
    bool clockChange() const;

private:
    /**
     * \brief Is it first mouse action now?
     * \param butt - value of button
     * \return true - yes
     * \return false - no
     */
    inline bool firstAction( const sf::Mouse::Button butt ) const
    { return butt == sf::Mouse::Left ? this->buttRev : ! this->buttRev; }

    /**
     * \brief Convert coordinates.
     * \param pos -
     * \return Vector2D -
     */
    static Vector2D position( const sf::Vector2i& pos );

public:
    /**
     * \brief Draw method
     * \param target -
     * \param states -
     */
    void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;

    /**
     * \brief Width of game window.
     * \return unsigned int -
     */
    unsigned int width() const;

    /**
     * \brief Height of game window.
     * \return unsigned int -
     */
    unsigned int height() const;

};