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
    Board board;            ///< Board of game
    Display display;        ///< Care about display a game

    bool buttRev {false};   ///< Current button mode. 0 - normal, 1 - revers button.
    bool running {false};   ///< Is game running on?

    sf::Clock clock;        ///< Stopwatch clock
    int stopwatch {0};      ///< Stopwatch value
    int lastClickTime {0};  ///< Time of last on the board click (or last hint serching)

    bool allowHint {false};  ///< Is hint is allowed.

public:
    /// Constructor deleted.
    Game() = delete;

    /**
     * \brief Construct a new Game object
     * \param argc - number of args
     * \param argv - values of argso
     */
    Game( const int argc, char* argv[] );

    /**
     * \brief Destroy the Game object (default destructor)
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
     * \brief Stopwatch clock
     * \return int -
     */
    inline int time() const { return stopwatch; }

    /**
     * \brief Is needed to change clock on the screen? + Change stopwatch value
     * \post stopwatch value change
     * \return true - yes
     * \return false - no
     */
    inline bool changeClock(){
        if( running )
            if( stopwatch != clock.getElapsedTime().asSeconds() ){
                stopwatch = clock.getElapsedTime().asSeconds();
                return true;
            }
        return false;
    }

    /**
     * \brief Is game on?
     * \return true - yes
     * \return false - no
     */
    inline bool isOn() const
    { return running; }

    /**
     * \brief Finish the game.
     */
    void finish();

    /**
     * \brief Start the game.
     */
    void start();

private:
    /**
     * \brief Is it first mouse action now?
     * \param butt - value of button
     * \return true - yes
     * \return false - no
     */
    inline bool firstAction( const sf::Mouse::Button butt ) const
    { return butt == sf::Mouse::Left ? ! this->buttRev : this->buttRev; }

    /**
     * \brief Convert coordinates.
     * \param pos - position on the window
     * \return Vector2D - position on the board
     */
    static Vector2D position( const sf::Vector2i& pos );

public:
    /**
     * \brief Update values on the interface (stopwatch, score)
     */
    void update();

    /**
     * \brief Draw method
     * \param target -
     * \param states -
     */
    void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;

    /**
     * \brief Width of game window.
     * \return short int - width
     */
    inline short int width() const
    { return this->board.w()*FIELD_SIZE; }

    /**
     * \brief Height of game window.
     * \return short int - height
     */
    inline short int height() const
    { return this->board.h()*FIELD_SIZE + GUI_MARGIN_T; }

};