#pragma once
/**
 * - coordinates is a bottom-left corner of objects
 * - [0,0] position in the window is a top-left corner of window
 */

////--------------------------------------------------
#define DEFAULT_Y_SIZE 10 		///< Default Y size of board
#define DEFAULT_X_SIZE 20 		///< Default X size of board
#define DEFAULT_MINE   30 		///< Default number of mines
#define HINT_TIME  		5 		///< Time to display a hint after correct click [s]

////--------------------------------------------------
#define MIN_SIZE        5       ///< Minimum sizes of board
#define MIN_MINES       1       ///< Minimum numbers of mines on the board
#define MIN_AREA        9       ///< Minum area of board

////--------------------------------------------------
#define FIELD_SIZE   	22		///< Sizes of field on the board
#define GUI_MARGIN_T 	40		///< GUI top margin

////--------------------------------------------------
#define MODE_BUTT_W     36      ///< Width of mode button
#define MODE_BUTT_Y     2 	    ///< Y position of mode button (x is variable)

////--------------------------------------------------
#define STOPWATCH_X_BG  0 		///< x position of stopwatch background (from top-right corner)
#define STOPWATCH_Y_BG  0 		///< y position of stopwatch background (from top-right corner)
#define STOPWATCH_X     32 		///< x position of stopwatch text (from top-right corner)
#define STOPWATCH_Y     6 		///< y position of stopwatch text (from top-right corner)
#define STOPWATCH_FONT  25		///< size of stopwatch font [px]

////--------------------------------------------------
#define COUNTER_X_BG      40   	///< x position of mine counter background (from top-left corner)
#define COUNTER_Y_BG      0   	///< y position of mine counter background (from top-left corner)
#define COUNTER_X         70	///< x position of mine counter text (from top-left corner)
#define COUNTER_Y         0		///< y position of mine counter text (from top-left corner)
#define COUNTER_FONT      35	///< size of stopwatch font [px]

////--------------------------------------------------
#define START_X			-59		///< x position of start button (from center point)
#define START_Y			0		///< y position of start button (from top edge

////--------------------------------------------------
#define SLEEP_LOOP      80      ///< Sleep time of game loop
#define SLEEP_CLICK     200     ///< Sleep time after click
#define SLEEP_ENDGAME 	800 	///< Sleep after end game click
#define MAX_ATTEMPTS    10000	///< Max amount of attempts of rand

////--------------------------------------------------
#define NUM_FIELD_VIEW  12		///< Number of fields views.

////--------------------------------------------------
#define SMALL_WIDTH		15 		///< Width of small board
#define SMALL_HEIGHT 	10 		///< Height of small board
#define SMALL_MINES		40 		///< Mines of small board

#define BIG_WIDTH		20 		///< Width of big board
#define BIG_HEIGHT 		15 		///< Height of big board
#define BIG_MINES		65 		///< Mines of big board

#define HUGE_WIDTH		30 		///< Width of huge board
#define HUGE_HEIGHT 	20 		///< Height of huge board
#define HUGE_MINES		115		///< Mines of huge board

////--------------------------------------------------
#define GUI_MENU_W 		260		///< Width of GUI menu window
#define GUI_MENU_H		320		///< Height of GUI menu window

#define MENU_X_SMALL 	8 		///< GUI Menu X of button 'small'
#define MENU_X_BIG	 	94		///< GUI Menu X of button 'big'
#define MENU_X_HUGE 	179		///< GUI Menu X of button 'huge'
#define MENU_Y_SIZES 	43 		///< GUI Menu Y of sizes buttons
#define MENU_W_SIZES 	72	 	///< GUI Menu width of sizes buttons
#define MENU_H_SIZES 	32	 	///< GUI Menu height of sizes buttons

#define MENU_X_MINUS 	90	 	///< GUI Menu X of button '-'
#define MENU_X_2MINUS 	114	 	///< GUI Menu X of button '--'
#define MENU_X_PLUS 	210	 	///< GUI Menu X of button '+'
#define MENU_X_2PLUS 	186	 	///< GUI Menu X of button '++'
#define MENU_X_PLUS_B 	232	 	///< GUI Menu X of button '+' for number of mines
#define MENU_X_2PLUS_B 	208	 	///< GUI Menu X of button '++' for number of mines
#define MENU_W_PM		20		///< GUI Menu width of buttons -, --, +, ++
#define MENU_H_PM		32 		///< GUI Menu height of buttons -, --, +, ++

#define MENU_SIZE_VAL 	36 		///< GUI Menu size of font size of width, height and mines values
#define MENU_X_VALUES	139	 	///< GUI Menu X of text values width, height, number of mines
#define MENU_Y_WIDTH	85	 	///< GUI Menu Y of text of width
#define MENU_Y_HEIGHT	125	 	///< GUI Menu Y of text of height
#define MENU_Y_MINES	167	 	///< GUI Menu Y of text of number of mines

#define MENU_XY_HINT 	153, 234	///< GUI Menu X, Y position of hints button
#define MENU_WH_HINT 	99, 28		///< GUI Menu width, height of hints button
#define MENU_XY_HINTTXT	215, 236 	///< GUI Menu position of off/on txt on hits button
#define MENU_SIZE_HINTTXT	18 		///< GUI Menu size of font hints state

#define MENU_XY_START 	64, 273		///< GUI Menu X, Y position of start button
#define MENU_WH_START 	132, 40		///< GUI Menu width, height of start button