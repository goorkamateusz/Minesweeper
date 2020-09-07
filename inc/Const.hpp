#pragma once

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