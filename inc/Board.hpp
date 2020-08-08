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
    Vector2D size {0,0};        ///< Size od board
    Field** board {NULL};       ///< Array of fields on the board. Coordinates: Board[ x ][ y ]
    short int mines;            ///< Number of no flagged mines.
    short unsigned int covered; ///< Number of covered fields.

public:
    /**
     * \brief Construct a new Board object
     */
    Board() = default;

    /**
     * \brief Destroy the Board object
     */
    ~Board();

public:
    /**
     * \brief Set values on the board
     * \param w - width
     * \param h - height
     * \param m - number of minse
     * \post Modifly `size` and `mines`
     */
    void set( unsigned int w, unsigned int h, unsigned int m );

    /**
     * \brief Uncover the choosen field
     * \param click - position of the field
     */
    void uncover( const Vector2D& pos );

    /**
     * \brief Do second action on selected field.
     * \param click - position of the field
     */
    void action( const Vector2D& click );

    /**
     * \brief Display debug.
     */
    void debug() const;

    /**
     * \brief Number of flags
     * \return short int -
     */
    inline short int noFlaggedMines() const
    { return mines; }

public:
    /**
     * \brief Width of board
     * \return unsigned int -
     */
    inline int w() const
    { return this->size.x; }

    /**
     * \brief Height of board
     * \return unsigned int -
     */
    inline int h() const
    { return this->size.y; }

    /**
     * \brief Is array created?
     * \return true - yes
     * \return false - no
     */
    inline bool created() const
    { return this->board != NULL; }

    /**
     * \brief Is filel inside the board.
     * \param pos - position of field
     * \return true - yes
     * \return false - no
     */
    inline bool inside( const Vector2D& pos ) const
    { return ( pos.x >= 0 && pos.x < size.x ) && ( pos.y >= 0 && pos.y < size.y ); }

public:
    /**
     * \brief Value of field. Without checking a correct of position!
     * \param vec -
     * \return Field& -
     */
    inline const Field& operator () ( const Vector2D& vec ) const
    { return board[ vec.x ][ vec.y ]; }

private:
    /**
     * \brief Value of field. Without checking a correct of position!
     * \param vec -
     * \return Field& -
     */
    inline Field& operator () ( const Vector2D& vec )
    { return board[ vec.x ][ vec.y ]; }

private:
    /**
     * \brief Create a array of board.
     * Default value of field is: empty, covered.
     * \post Modify only `board`.
     * \param size_ - Vector2D of new boards sizes.
     */
    void alloc();

    /**
     * \brief Free memory if board array exist.
     */
    void free();

    /**
     * \brief Rand mines position on the board.
     * \exception
     *  - Too much mines!
     *      Maximum number of mines is area of board - 9 (first click is on the empty field!)
     *  - Too least mines!
     *      Minumum number of mines is const in Const.hpp.
     * \param num_mines -
     */
    void randMines( const Vector2D& click );


    /**
     * \brief Count values of field after rand mines position.
     */
    void countFields();


    /**
     * \brief Vectors of around coordinates.
     */
    static const Vector2D AROUND[8];
};