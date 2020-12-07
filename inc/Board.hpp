#pragma once

#include "Vector2D.hpp"
#include "Field.hpp"
#include "Const.hpp"

/**
 * \brief Board of game
 *
 */
class Board {
private:
    Vector2D size {0,0};        ///< Size od board.
    Field** board {NULL};       ///< Array of fields on the board. Coordinates: Board[ x ][ y ].
    short int mines_init;       ///< Number of mines in beginning of the game.
    short int mines;            ///< Number of no flagged mines.
    short unsigned int covered; ///< Number of covered fields.

public:
    /**
     * \brief Construct a new Board object (default constructor)
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
     * \brief Restart the board.
     */
    void restart();

    /**
     * \brief Uncover the choosen field
     * \param click - position of the field
     * \retval true - Done a click
     * \retval false - click unavaliable
     */
    bool uncover( const Vector2D& click );

    /**
     * \brief Do second action on selected field.
     * \param click - position of the field
     * \retval true - Done a move
     * \retval false - move unavaliable
     */
    bool action( const Vector2D& click );

    /**
     * \brief Display board on the console to debuging
     */
    void debug() const;

    /**
     * \brief Number of no flagged mines on the board.
     * \return short int - number of no flagged mines = mines_init - flag
     */
    inline short int noFlaggedMines() const
    { return mines; }

public:
    /**
     * \brief Width of board
     * \return unsigned int - width
     */
    inline int w() const
    { return this->size.x; }

    /**
     * \brief Height of board
     * \return unsigned int - width
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
     * \brief Find a hint for player with AI.
     *
     * \param[out] pos - Position of hint move
     * \return true - is hint
     * \return false - isn't hint
     */
    bool hint( Vector2D*& pos ) const;

public:
    /**
     * \brief Value of field. Without checking a correct of position!
     * \warning Method don't check, is field exist!
     * \param vec - position on the board
     * \return Field& - field const
     */
    inline const Field& operator () ( const Vector2D& vec ) const
    { return board[ vec.x ][ vec.y ]; }

private:
    /**
     * \brief Value of field. Without checking a correct of position!
     * \warning Method don't check, is field exist!
     * \param vec - position on the board
     * \return Field& - field to edit
     */
    inline Field& operator () ( const Vector2D& vec )
    { return board[ vec.x ][ vec.y ]; }

    /**
     * \brief Uncover all fields on the board
     */
    void uncoverAll();

    /**
     * \brief Set flag on the all of mines fields
     */
    void flagAll();

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
     * \exception Possible exceptions:
     *  - Too much mines!
     *      Maximum number of mines is area of board - 9 (first click is on the empty field!)
     *  - Too least mines!
     *      Minumum number of mines is const in Const.hpp.
     * \param click - where was the first click
     */
    void randMines( const Vector2D& click );

    /**
     * \brief Calculate values of field after rand mines position.
     */
    void calcFields();

    /**
     * \brief Vectors of around coordinates.
     */
    static const Vector2D AROUND[8];
};