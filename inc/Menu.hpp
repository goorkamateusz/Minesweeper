#pragma once

#include "Const.hpp"
#include "SFML/Graphics.hpp"

/**
 * \brief Mange a menu GUI on the begin of game.
 *
 */
class Menu : sf::Drawable {

	sf::Font 	font; 			///< Font
	//IDEA use a Display::font ???????
	sf::Texture menu_texture;	///< Menu GUI background texture
	sf::Sprite 	menu_bg;		///< Menu GUI background spirte

	sf::Text 	width_txt;		///< Text to display width of the board
	sf::Text 	height_txt;		///< Text to display height of the board
	sf::Text 	mines_txt;		///< Text to display number mines on the board
	sf::Text 	hints_txt;		///< Text to display number mines on the board

	unsigned short int out_width {SMALL_WIDTH}; 	///< Width of window
	unsigned short int out_height {SMALL_HEIGHT}; 	///< Height of window
	unsigned short int out_mines {SMALL_MINES}; 	///< Number of mines on the window
	bool allowHints {false}; 						///< Is hints will be allowed

public:
	/**
	 * \brief Construct a new Menu object
	 *
	 */
	Menu();

	/**
	 * \brief Destroy the Menu object (default)
	 */
	~Menu() = default;

public:
	/**
	 * \brief Click manage on menu GUI
	 *
	 * \param window - window
	 */
	bool click( const sf::RenderWindow& window );

	/**
     * \brief Draw method
     * \param target -
     * \param states -
     */
    void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;

	/**
	 * \brief Update text values to display
	 */
	void update();

public:
	/**
	 * \brief Menu GUI handling
	 *
	 * \post
	 * 	-
	 *
	 * \param argc - size of argv[] (out)
	 * \param argv - values of init argument to game (out)
	 */
	static void handling( int &argc, char** &argv );

	/**
	 * \brief Create argv and argc based on GUI menu
	 *
	 * \param argc - [out] length of argument list
	 * \param argv - [out] argument list (array)
	 */
	void output( int &argc, char** &argv );

	/**
	 * \brief Delete argv table
	 *
	 * \param argc - size of argv[]
	 * \param argv - char** array of arrays to delete
	 */
	static void clean( const int argc, char** &argv );

	/**
	 * \brief Is position `pos` is in the rectangle of coordinates `coo` and sizes `size`
	 * - coo is a bottom-left corner of rectangle
	 * - [0,0] pos is a top-left corner of window
	 * \param pos - position
	 * \param coo - cooridnates of rectangle
	 * \param size - sizes of rectangle
	 */
	static bool inside( const sf::Vector2i& pos, const sf::Vector2i& coo, const sf::Vector2i& size );

	//todo dox and test
	inline static bool insideX( const sf::Vector2i& pos, const sf::Vector2i& coo, const sf::Vector2i& size )
	{
		return pos.x > coo.x && pos.x < coo.x + size.x;
	}

	//todo dox and test
	inline static bool insideY( const sf::Vector2i& pos, const sf::Vector2i& coo, const sf::Vector2i& size )
	{
		return pos.y > coo.y && pos.y < coo.y + size.y;
	}

};