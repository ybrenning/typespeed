/**
 * @file typespeed.h
 * @author Yannick Brenning
 * @brief Simple console typing practice game 
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef TYPESPEED_H
#define TYPESPEED_H

#include <stdbool.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#define ARRAY_SIZE(arr) sizeof(arr) / sizeof(arr[0])

#ifndef _WIN32
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define NANO_PER_SEC 1000000000.0
#endif

/**
 * @brief Stores the stats of the particular game.
 * 
 * Meant to be returned after finishing a single text as it 
 * contains the player's typing statistics.
 * 
 * @see https://www.speedtypingonline.com/typing-equations
 */
typedef struct Stats {
    double wpm; /**< (Gross) Words per Minute. */
    double accuracy; /**< Percentage of correctly typed letters. */
} Stats;

/**
 * @brief Contains the console text style.
 * 
 * <tt> Style </tt> contains the color of the next
 * section of console text, as well as whether the
 * background is filled in or not.
 */
typedef struct Style {
    /**
     * @brief Contains the color of the text.
     * 
     * Four different colors are possible as of now --
     * in the case of the Windows implementation
     * the color yellow is not yet supported. 
     */
    enum color {
        red,
        green,
        blue,
        yellow
    } color;
    bool background; /**< Denotes whether background is filled in or not. */
} Style;

/**
 * @brief Selects a sentence at random from <tt> sentences.h </tt>.
 * 
 * @return String containing the sentence to be typed.
 */
char *select_sentence();

/**
 * @brief Compares one char of user input to the char of the solution.
 * 
 * @param input Single letter of user input.
 * @param solution Single letter of the sentence to be typed.
 * 
 * @return true if letters are the same, false otherwise
 */
bool compare_chars(char input, char solution);

#ifdef _WIN32
/**
 * @brief Implementation of `getch()` function from the unix curses library.
 * 
 * @return Single letter typed into console by the user.
 */
TCHAR getch();
#else
/**
 * @brief Initialize new terminal i/o settings.
 *
 */
void initTermios(int echo);

/**
 * @brief Restore old terminal i/o settings.
 *
 */
void resetTermios(void);

/**
 * @brief Read 1 character - echo defines echo mode
 *
 * @param echo whether to write the user input to console.
 * @return Single letter typed into console by the user.
 */
char getch_(int echo);

/**
 * @brief Read 1 character without echo.
 * 
 * @return Single letter typed into console by the user.
 */
char getch(void) 

/**
 * @brief Read 1 character with echo.
 *
 * @return Single letter typed into console by the user.
 */
char getche(void) 
#endif

#ifdef _WIN32
void set_console_style_win32(HANDLE hConsole, Style style);
#else
void set_console_style_unix(Style style);
#endif

/**
 * @brief Set the console style based on a given
 * #Style struct and the current user's operating system.
 * 
 * @param style #Style to which the console will be set.
 */
void set_console_style(Style style);

/**
 * @brief Counts down until beginning of the typing session.
 */
void countdown();

/**
 * @brief Executes the main game loop.
 * 
 * Initializes all stats and begins looping through a sentence
 * randomly selected by select_sentence(). Keeps track of 
 * correctly and incorrectly typed letters throughout and sets
 * the console #Style using set_console_style() depending on
 * the input.
 * 
 * At the end, stop the timer and use counted values to
 * calculate the user's stats using the #Stats struct.
 * 
 * @return User's WPM and accuracy for the current game
 */
Stats game_loop();

#endif // TYPESPEED_H
