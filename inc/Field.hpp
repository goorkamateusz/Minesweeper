#pragma once

#include "FieldCode.hpp"
#include <cstdint>
#include <iostream>
using std::uint8_t;

/**
 * \brief Field of the board.
 *
 * - last 4 bites
 * number 	| posible vales				| code		| hex
 * :-		|:-							|:-			|:-
 * 0        | empty						| ----0000	| 0x00
 * 1 - 8    | number of mines around	|			| 0x01-0x8
 * 15       | mine						| ----1001	| 0x09
 *
 * - fisrt 4 bites
 * States		| code		| hex
 * :-			|:-			|:-
 * cover		| 0000----	| 0x00
 * flag			| 0001----	| 0x10
 * uncover		| 0010----	| 0x20
 *
 */
class Field {
private:
    uint8_t code;      ///< Value of fields code

public:
	/**
	 * \brief Construct a new Field object
	 */
	Field(): code(0x0){}

	/**
	 * \brief Construct a new Field object
	 * \param v - uint8_t
	 */
	Field( uint8_t v ){ this->val( v ); }

	/**
	 * \brief Construct a new Field object
	 * \param code - FieldCode
	 */
	Field( FieldCode code )
	{ this->val( static_cast<uint8_t>( code ) ); }

	/**
	 * \brief Copy constructor
	 * \param field -
	 */
	Field( const Field& field ): code(field.code){}

	/**
	 * \brief Destroy the Field object (default destructor)
	 */
	~Field() = default;

public:
	/**
	 * \brief Operator of one side *
	 * \return uint8_t -
	 */
	inline uint8_t& operator * ()
	{ return code; }

	/**
	 * \brief Return value of field
	 * \return uint8_t - value of field
	 */
	inline uint8_t val() const
	{ return (uint8_t) code & 0x0F; }

	/**
	 * \brief Set value of field and cover
	 * \param value - new value
	 * \post After that field allways be covered!
	 */
	inline void val( const uint8_t value )
	{ code = value; code &= 0x0F; }

public:
	/**
	 * \brief Set flag on the field
	 */
	inline void flag()
	{ code &= 0x0F; code |= 0x10; }

	/**
	 * \brief Delete flag from the field
	 */
	inline void unflag()
	{ code &= 0x0F; /*code |= 0x00; //hack */ }

	/**
	 * \brief Uncover the field
	 */
	inline void uncover()
	{ code &= 0x0F; code |= 0x20; }

public:
	/**
	 * \brief Is field flagged?
	 * ** flagged field is covered! **
	 * \return true - yes
	 * \return false - no
	 */
	inline bool flagged() const
	{ return ( code & 0xF0 ) == 0x10; }


	/**
	 * \brief Is field uncovered? (no covered, no flag)
	 * \return true -  yes
	 * \return false - no
	 */
	inline bool uncovered() const
	{ return ( code & 0xF0 ) == 0x20; }

	/**
	 * \brief Is field covered? (is covered)
	 * \return true - yes
	 * \return false - no
	 */
	inline bool covered() const
	{ return ( code & 0xF0 ) == 0x00; }

	/**
	 * todo Zamiania uncover, covered, hidden
	 * \warning
	 * uncoverAble change to covered
	 * covered to hidden
	 */

	/**
	 * \brief Is value of fields hidden?  (is cover or flagged)
	 * \return true - yes
	 * \return false - no
	 */
	inline bool hidden() const
	{ return ( code & 0xF0 ) != 0x20; }

	/**
	 * \brief Is the mine?!
	 * \return true - yes
	 * \return false - no
	 */
	inline bool mine() const
	{ return ( code & 0x0F ) == 0x09; }

	/**
	 * \brief Is the field empty?
	 * \return true - yes
	 * \return false - no
	 */
	inline bool empty() const
	{ return ( code & 0x0F ) == 0x00; }
};


/**
 * \brief Operator to display a field information.
 * \param strm - ostream
 * \param field - field
 * \return std::ostream& - ostream
 */
std::ostream& operator << ( std::ostream& strm, const Field& field );