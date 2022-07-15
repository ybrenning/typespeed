/**
 * @file typespeed.h
 * @author Yannick Brenning
 * @brief Simple console typing practice game 
 * @version 0.1
 * @date 2022-07-15
 * 
 * @copyright Copyright (c) 2022
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
     * Four different colors are possible as of now,
     * in the case of the Windows implementation
     * the color yellow is not yet supported. 
     */
    enum color {
        red,
        green,
        blue,
        yellow
    } color;
    bool background; /**< Explains whether background is filled in or not. */
} Style;

/**
 * @brief Selects a sentence at random from <tt> sentences.h </tt>.
 * 
 * @return char* String containing the sentence to be typed.
 */
char *select_sentence();

/**
 * @brief Compares one letter of user input and letter of solution.
 * 
 * @param input Single letter of user input.
 * @param solution Single letter of the sentence to be typed.
 * @return true Letters are the same.
 * @return false Letters are not the same.
 */
bool compare_letters(char input, char solution);

/**
 * @brief Gets console input from the user.
 * 
 * Uses <tt> getch() </tt> so that the input is taken
 * instantly without need for pressing <kbd> ENTER </kbd>.
 * 
 * @return char Letter input by the user.
 */
char take_input();

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
 * @brief Counts down until beginning of the typing session
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
 * @return Stats User's WPM and accuracy for the current game
 */
Stats game_loop();

#endif // TYPESPEED_H
