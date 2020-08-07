#pragma once

#include "FieldCode.hpp"
#include <cstdint>
#include <iostream>
using std::uint8_t;

/**
 * \brief Field of the board.
 *
 * number 	| posible vales				| code		| hex
 * :-		|:-							|:-			|:-
 * 0        | empty						| ----0000	| 0x00
 * 1 - 8    | number of mines around	|			| 0x01-0x8
 * 15       | mine						| ----1001	| 0x09
 * Last 4 bites.
 *
 * States		| code		| hex
 * :-			|:-			|:-
 * cover		| 0000----	| 0x00
 * flag			| 0001----	| 0x10
 * uncover		| 0010----	| 0x20
 * First 4 bites.
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
	 * \brief Destroy the Field object
	 */
	~Field() = default;

public:
	/**
	 * \brief Operator ..
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
	 * \brief Set value of field
	 * \param value -
	 */
	inline void val( const uint8_t value )
	{ code &= 0xF0; code |= value; }

public:
	/**
	 * \brief Set flag on the field
	 */
	inline void flag()
	{ code &= 0x0F; code |= 0x10; }

	/**
	 * \brief Uncover the field
	 */
	inline void uncover()
	{ code &= 0x0F; code |= 0x20; }

public:
	/**
	 * \brief Is field flaged?
	 * ** flaged fild is covered! **`
	 * \return true - yes
	 * \return false - no
	 */
	inline bool flaged() const
	{ return ( code & 0xF0 ) == 0x10; }

	/**
	 * \brief Is field covered
	 * \return true - yes
	 * \return false - no
	 */
	inline bool covered() const
	{ return ( code & 0xF0 ) != 0x20; }

	/**
	 * \brief Is the mine?!
	 * \return true - yes
	 * \return false - no
	 */
	inline bool mine() const
	{ return ( code & 0x0F ) == 0x09; }


	/**
	 * \brief Is the file empty?
	 * \return true - yes
	 * \return false - no
	 */
	inline bool empty() const
	{ return ( code & 0x0F ) == 0x00; }

};


////------------------------------------------------

/**
 * \brief Operator to display a field information.
 * \param strm -
 * \param field -
 * \return std::ostream& -
 */
std::ostream& operator << ( std::ostream& strm, const Field& field );