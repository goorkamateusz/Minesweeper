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

	/// 3. Make w new argv list
	menu.output( argc, argv );

}

////-----------------------------------------------
void Menu::clean( const int argc, char** &argv ){
	delete[] argv[0];
	delete[] argv;
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
	Menu::clean( argc, argv );

	///- Create new argv
	stringstream strm;

	//hints
	argc = (allowHints) ? 8 : 7;
	argv = new char*[ argc ];

	//empty
	argv[0] = new char;
	argv[0][0] = '\0';

	//width
	argv[1] = new char[3];
	strm << "-w\0" << ' ';
	strm >> argv[1];

	argv[2] = new char[3];
	strm << out_width << ' ';
	strm >> argv[2];

	//height
	argv[3] = new char[3];
	strm << "-h\0" << ' ';
	strm >> argv[3];

	argv[4] = new char[3];
	strm << out_height << ' ';
	strm >> argv[4];

	//mines
	argv[5] = new char[3];
	strm << "-m\0" << ' ';
	strm >> argv[5];

	argv[6] = new char[4];
	strm << out_mines << ' ';
	strm >> argv[6];

	//hints
	if( allowHints ){
		argv[7] = new char[4];
		strm << "-H\0" << ' ';
		strm >> argv[7];
	}
}

////-----------------------------------------------
bool Menu::click( const sf::RenderWindow& window ){

    Vector2i mouse_pos = Mouse::getPosition(window);

	// Buttons of sizes
	const Vector2i butt_sizes = Vector2i( MENU_W_SIZES, MENU_H_SIZES );

	//width
	if( mouse_pos.y > MENU_Y_WIDTH && mouse_pos.y < MENU_Y_WIDTH+MENU_H_PM ){
		if     ( mouse_pos.x > MENU_X_2PLUS	 && mouse_pos.x < MENU_X_2PLUS + MENU_W_PM	) change( out_width,  5, 7, 100 );
		else if( mouse_pos.x > MENU_X_PLUS	 && mouse_pos.x < MENU_X_PLUS + MENU_W_PM	) change( out_width,  1, 7, 100 );
		else if( mouse_pos.x > MENU_X_2MINUS && mouse_pos.x < MENU_X_2MINUS + MENU_W_PM ) change( out_width, -5, 7, 100 );
		else if( mouse_pos.x > MENU_X_MINUS	 && mouse_pos.x < MENU_X_MINUS + MENU_W_PM	) change( out_width, -1, 7, 100 );
	}
	//height
	else if( mouse_pos.y > MENU_Y_HEIGHT && mouse_pos.y < MENU_Y_HEIGHT + MENU_H_PM ){
		if     ( mouse_pos.x > MENU_X_2PLUS	 && mouse_pos.x < MENU_X_2PLUS + MENU_W_PM	) change( out_height,  5, 1, 100 );
		else if( mouse_pos.x > MENU_X_PLUS	 && mouse_pos.x < MENU_X_PLUS + MENU_W_PM	) change( out_height,  1, 1, 100 );
		else if( mouse_pos.x > MENU_X_2MINUS && mouse_pos.x < MENU_X_2MINUS + MENU_W_PM ) change( out_height, -5, 1, 100 );
		else if( mouse_pos.x > MENU_X_MINUS	 && mouse_pos.x < MENU_X_MINUS + MENU_W_PM	) change( out_height, -1, 1, 100 );
	}
	//mines
	else if( mouse_pos.y > MENU_Y_MINES && mouse_pos.y < MENU_Y_MINES + MENU_H_PM ){
		if     ( mouse_pos.x > MENU_X_2PLUS_B && mouse_pos.x < MENU_X_2PLUS_B + MENU_W_PM ) change( out_mines,  5, 0, 1000 );
		else if( mouse_pos.x > MENU_X_PLUS_B  && mouse_pos.x < MENU_X_PLUS_B + MENU_W_PM  ) change( out_mines,  1, 0, 1000 );
		else if( mouse_pos.x > MENU_X_2MINUS  && mouse_pos.x < MENU_X_2MINUS + MENU_W_PM  ) change( out_mines, -5, 0, 1000 );
		else if( mouse_pos.x > MENU_X_MINUS	  && mouse_pos.x < MENU_X_MINUS + MENU_W_PM	  ) change( out_mines, -1, 0, 1000 );
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

	///- Update width txt
	strm << out_width << ' '; strm >> s;
	width_txt.setString( s );

	///- Update height txt
	strm << out_height << ' '; strm >> s;
	height_txt.setString( s );

	///- Update mines txt
	strm << out_mines << ' '; strm >> s;
	mines_txt.setString( s );

	///- Update hints state
	if( allowHints ) hints_txt.setString("on");
	else 			 hints_txt.setString("off");
}

////-----------------------------------------------
void Menu::change( unsigned short &val, const short int change, const short int minval, const short int maxval ){
	if( val + change > minval && val + change < maxval ) val += change;

	if( out_mines + 9 > out_width * out_height )
		out_mines = out_width * out_height - 9;
}

////-----------------------------------------------
bool Menu::inside( const Vector2i& pos, const Vector2i& coo, const Vector2i& size ){
	if( pos.y > coo.y && pos.y < coo.y + size.y )
		if( pos.x > coo.x && pos.x < coo.x + size.x )
			return true;
	return false;
}
