#ifndef TYPESPEED_H
#define TYPESPEED_H

#include <stdbool.h>

#define ARRAY_SIZE(arr) sizeof(arr) / sizeof(arr[0])

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"

typedef struct Stats {
    double wpm;
    double accuracy;
} Stats;

typedef struct Style {
    enum color {
        red,
        green,
        blue,
        yellow
    } color;
    bool background;
} Style;

char *select_sentence();
bool compare_letters(char input, char solution);
char take_input();

#ifdef _WIN32
    #include <windows.h>

    void set_console_style_win32(HANDLE hConsole, Style style);
#else
    #include <unistd.h>

    void set_console_style_unix(Style style);
#endif

void set_console_style(Style style);

Stats game_loop();

#endif // TYPESPEED_H
