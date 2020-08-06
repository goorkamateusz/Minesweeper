#pragma once

#include "Board.hpp"
#include "Const.hpp"
#include "SFML/Graphics.hpp"

/**
 * \brief Interface and game organization.
 */
class Game : public sf::Drawable {
private:
    Board board;        //< Board of game

public:
    Game() = delete;

    /**
     * \brief Construct a new Game object
     * \param argc -
     * \param argv -
     */
    Game( int argc, const char* const argv[] );

    /**
     * \brief Destroy the Game object
     */
    ~Game();


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