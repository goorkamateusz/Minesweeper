#pragma once

#include "SFML/Graphics.hpp"
#include "Board.hpp"
#include "TField.hpp"

/**
 * \brief Care about display on the interface.
 *
 */
class Display {
private:
    /**
     * \brief Templates of Field view. Default: array of NULL.
     *
     * id   | name
     * :----|:--------
     * 0    | empty
     * 1-8  | values
     * 9    | mine
     * 10   | flag
     * 11   | covered
     *
     * \see NUM_FIELD_VIEW, TField
     */
    static TField* Template[ NUM_FIELD_VIEW ];

private:
    /**
     * \brief Field code to element on Templete array.
     * \param field - value of field
     * \return short int - id in the Templete array.
     */
    static TField* const pointer( const Field& field );

public:
    /**
     * \brief Construct a new Display object
     */
    Display();

    /**
     * \brief Destroy the Display object
     */
    ~Display();

public:
    /**
     * \brief Display clock on the window
     * \param seconds - time
     */
    void stopwatch( sf::RenderTarget& target, unsigned int seconds ) const; //??? const?

    /**
     * \brief Display score on the window
     * \param score - points
     */
    void score( sf::RenderTarget& target, unsigned int score ) const; //??? const?

    /**
     * \brief Display board on the window
     * \param board - game board
     */
    void board( sf::RenderTarget& target, const Board* const board ) const;


};