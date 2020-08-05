#pragma once

#include "Vector2D.hpp"
#include "Field.hpp"
#include "Const.hpp"

/**
 * \brief Board of game
 *
 * TODO:
 *  todo: tworzenie mapy, losowanie pozycji min
 *  todo: wykonywanie ruchu
 *  todo:
 */
class Board {
private:
    Vector2D size {0,0};    //< Size od board
    Field** board {NULL};   //< Array of fields on the board. Coordinates: Board[ x ][ y ]

public:
    /**
     * \brief Construct a new Board object
     */
    Board(){
        //todo konstruktor
    }



    /**
     * \brief Destroy the Board object
     */
    ~Board(){
        //todo dekonstruktor
    }


private:

    /**
     * \brief Value of field. Without checking a correct of position!
     * \param vec -
     * \return Field& -
     */
    inline Field& operator () ( const Vector2D& vec )
    { return board[ vec.y ][ vec.x ]; }

    inline const Field& operator () ( const Vector2D& vec ) const
    { return board[ vec.y ][ vec.x ]; }


private:
    /**
     * \brief Create a array of board.
     * \param size_ - Vector2D of new boards sizes.
     */
    void alloc( const Vector2D& size_ );

    /**
     * \brief Rand mines position on the board.
     * \exception
     *  - Too much mines!
     *      Maximum number of mines is area of board - 9 (first click is on the empty field!)
     *  - Too least mines!
     *      Minumum number of mines is const in Const.hpp.
     * \param num_mines -
     */
    void randMines( const Vector2D& click, unsigned num_mines );

};