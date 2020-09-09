#include "Menu.hpp"
#include "Func.hpp"
#include <sstream>
#include <iostream>
#include <string>

using namespace std;
using namespace sf;

////-----------------------------------------------
Menu::Menu(){
	///- Load menu GUI background texture
	menu_texture = LoadTextureFromResource("BMENU");

	///- Init spirte of menu background
	menu_bg.setTexture( menu_texture );
	menu_bg.setPosition( 0, 0 );

	///- Load font
	font = LoadFontFromResource("CONSOLA");
	//IDEA font from Display::font ???

	///- Texts init
	width_txt.setFont( font );
	width_txt.setCharacterSize( MENU_SIZE_VAL );
	width_txt.setColor( Color::White );
	width_txt.setPosition( MENU_X_VALUES , MENU_Y_WIDTH );

	height_txt.setFont( font );
	height_txt.setCharacterSize( MENU_SIZE_VAL );
	height_txt.setColor( Color::White );
	height_txt.setPosition( MENU_X_VALUES , MENU_Y_HEIGHT );

	mines_txt.setFont( font );
	mines_txt.setCharacterSize( MENU_SIZE_VAL );
	mines_txt.setColor( Color::White );
	mines_txt.setPosition( MENU_X_VALUES , MENU_Y_MINES );

	hints_txt.setFont( font );
	hints_txt.setCharacterSize( MENU_SIZE_HINTTXT );
	hints_txt.setColor( Color::White );
	hints_txt.setPosition( MENU_XY_HINTTXT );
}

////-----------------------------------------------
void Menu::handling( int &argc, char** &argv ){

	/// 1. Create window and GUI object
	RenderWindow window(
		VideoMode( GUI_MENU_W, GUI_MENU_H ),
		"Minesweeper | maatiug",
		Style::Close | Style::Titlebar  );
	Event event;

	Menu menu;

	/// 2. GUI loop
	bool change = true;

	while( window.isOpen() ){

		//* Process events
		while( window.pollEvent(event) ){

			// Close window: exit
			if (event.type == Event::Closed)
				window.close();

			// Buttons
			if( ! change ){
				if( Mouse::isButtonPressed( Mouse::Left ) ){

					if( menu.click( window ) )
						window.close();

					sf::sleep( milliseconds(SLEEP_CLICK) );
				}

				change = true;
			}
		}

		//* Display
		if( change ){

			menu.update();

			// Clear screen
			window.clear();
			// Draw the string
			window.draw( menu );
			// Update the window
			window.display();

			change = false;
		}

		sf::sleep( milliseconds( SLEEP_LOOP ) );

	}

	/// 3. Make w new argv listx`
	menu.output( argc, argv );

}

////-----------------------------------------------
void Menu::clean( const int argc, char** &argv ){
	//todo clean

}

////-----------------------------------------------
void Menu::draw( sf::RenderTarget& target, sf::RenderStates states ) const {
	target.draw( menu_bg );
	target.draw( width_txt );
	target.draw( height_txt );
	target.draw( mines_txt );
	target.draw( hints_txt );
}

////-----------------------------------------------
void Menu::output( int &argc, char** &argv ){

	///- Clean existing argv
	this->clean( argc, argv );

	//todo output
	///- Create new argv
	argv = new char*[ 5 ];

	//empty
	argv[0] = new char;
	argv[0][0] = '\0';

	//width
	// argv[1] =

}

////-----------------------------------------------
bool Menu::click( const sf::RenderWindow& window ){

    Vector2i mouse_pos = Mouse::getPosition(window);

	///- Buttons of sizes
	const Vector2i butt_sizes = Vector2i( MENU_W_SIZES, MENU_H_SIZES );

	//width
	if( mouse_pos.y > MENU_Y_WIDTH && mouse_pos.y < MENU_Y_WIDTH+MENU_H_SIZES ){
		if     ( mouse_pos.x > MENU_X_2PLUS	 && mouse_pos.x < MENU_X_2PLUS+MENU_W_SIZES	 ) out_width += 5;
		else if( mouse_pos.x > MENU_X_PLUS	 && mouse_pos.x < MENU_X_PLUS+MENU_W_SIZES	 ) ++out_width;
		else if( mouse_pos.x > MENU_X_2MINUS && mouse_pos.x < MENU_X_2MINUS+MENU_W_SIZES )
			{ if( out_width > 5 ) out_width -= 5; }
		else if( mouse_pos.x > MENU_X_MINUS	 && mouse_pos.x < MENU_X_MINUS+MENU_W_SIZES	 )
			{ if( out_width > 1 ) --out_width; }
	}
	//height
	else if( mouse_pos.y > MENU_Y_HEIGHT && mouse_pos.y < MENU_Y_HEIGHT+MENU_H_SIZES ){
		if     ( mouse_pos.x > MENU_X_2PLUS	 && mouse_pos.x < MENU_X_2PLUS+MENU_W_SIZES	 ) out_height += 5;
		else if( mouse_pos.x > MENU_X_PLUS	 && mouse_pos.x < MENU_X_PLUS+MENU_W_SIZES	 ) ++out_height;
		else if( mouse_pos.x > MENU_X_2MINUS && mouse_pos.x < MENU_X_2MINUS+MENU_W_SIZES )
			{ if( out_height > 5 ) out_height -= 5; }
		else if( mouse_pos.x > MENU_X_MINUS	 && mouse_pos.x < MENU_X_MINUS+MENU_W_SIZES	 )
			{ if( out_height > 1 ) --out_height; }
	}
	//mines
	else if( mouse_pos.y > MENU_Y_MINES && mouse_pos.y < MENU_Y_MINES+MENU_H_SIZES ){
		if     ( mouse_pos.x > MENU_X_2PLUS_B && mouse_pos.x < MENU_X_2PLUS_B+MENU_W_SIZES 	) out_mines += 5;
		else if( mouse_pos.x > MENU_X_PLUS_B  && mouse_pos.x < MENU_X_PLUS_B+MENU_W_SIZES   ) ++out_mines;
		else if( mouse_pos.x > MENU_X_2MINUS  && mouse_pos.x < MENU_X_2MINUS+MENU_W_SIZES   )
			{ if( out_mines > 5 ) out_mines -= 5; }
		else if( mouse_pos.x > MENU_X_MINUS	  && mouse_pos.x < MENU_X_MINUS+MENU_W_SIZES	)
			{ if( out_mines > 1 ) --out_mines; }
	}
	//small
	else if( Menu::inside( mouse_pos, Vector2i( MENU_X_SMALL, MENU_Y_SIZES ), butt_sizes ) ){
		out_width  = SMALL_WIDTH; out_height = SMALL_HEIGHT; out_mines  = SMALL_MINES;
	}
	//big
	else if( Menu::inside( mouse_pos, Vector2i( MENU_X_BIG, MENU_Y_SIZES ), butt_sizes ) ){
		out_width  = BIG_WIDTH; out_height = BIG_HEIGHT; out_mines  = BIG_MINES;
	}
	//huge
	else if( Menu::inside( mouse_pos, Vector2i( MENU_X_HUGE, MENU_Y_SIZES ), butt_sizes ) ){
		out_width  = HUGE_WIDTH; out_height = HUGE_HEIGHT; out_mines  = HUGE_MINES;
	}
	// start button
	else if( Menu::inside( mouse_pos, Vector2i( MENU_XY_START ), Vector2i( MENU_WH_START ) ) ){
		return true;
	}
	// hints button
	else if( Menu::inside( mouse_pos, Vector2i( MENU_XY_HINT ), Vector2i( MENU_WH_HINT ) ) ){
		allowHints = !allowHints;
	}

	return false;
}

////-----------------------------------------------
void Menu::update(){
	stringstream strm;
	string s;

	strm << out_width << ' '; strm >> s;
	width_txt.setString( s );

	strm << out_height << ' '; strm >> s;
	height_txt.setString( s );

	strm << out_mines << ' '; strm >> s;
	mines_txt.setString( s );

	if( allowHints ) hints_txt.setString("on");
	else 			 hints_txt.setString("off");
}

////-----------------------------------------------
bool Menu::inside( const Vector2i& pos, const Vector2i& coo, const Vector2i& size ){
	if( pos.y > coo.y && pos.y < coo.y + size.y )
		if( pos.x > coo.x && pos.x < coo.x + size.x )
			return true;
	return false;
}
