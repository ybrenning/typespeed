#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "typespeed.h"
#include "sentences.h"

char *select_sentence() {
    srand(time(NULL));
    size_t total = ARRAY_SIZE(sentences);
    return (sentences[rand() % total]);
}

bool compare_chars(char input, char solution) {
    return (input == solution ? true : false);
}

#ifdef _WIN32
    TCHAR getch() {
        DWORD mode, cc;
        HANDLE h = GetStdHandle(STD_INPUT_HANDLE);

        if (h == NULL) {
            return 0;
        }

        GetConsoleMode(h, &mode);
        SetConsoleMode(h, mode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT));

        TCHAR c = 0;
        ReadConsole(h, &c, 1, &cc, NULL);
        SetConsoleMode(h, mode);
        return c;
    }
#else
    #include <conio.h>
#endif

#ifdef _WIN32
    void set_console_style_win32(HANDLE hConsole, Style style) {
        switch(style.color) {
            case(0):
                if (style.background) {
                    SetConsoleTextAttribute(hConsole, BACKGROUND_RED);
                } else {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                }

                break;
            case(1):
                if (style.background) {
                    SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN);
                } else {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                }

                break;
            case(2):
                if (style.background) {
                    SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE);
                } else {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
                }

                break;
            default:
                fprintf(stderr, "An error occurred while generating the console text style.\n");
                exit(1);
        }
    }
#else
    void set_console_style_unix(Style style) {
        switch(style.color) {
            case(0):
                printf(ANSI_COLOR_RED);
                break;
            case(1):
                printf(ANSI_COLOR_GREEN);
                break;
            case(2):
                printf(ANSI_COLOR_BLUE);
                break;
            case(3):
                printf(ANSI_COLOR_YELLOW);
                break;
            default:
                fprintf(stderr, "An error occurred while generating the console text style.\n");
                exit(1);
        }
    }
#endif

void set_console_style(Style style) {
    #ifdef _WIN32
        // hConsole variable is needed for Windows console styling
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        set_console_style_win32(hConsole, style);
    #else 
        // For Unix console coloring, simply use ANSI codes defined above
        set_console_style_unix(style);
    #endif
}

void countdown() {
    // Sleep() function is defined differently between Windows/Unix
    #ifdef _WIN32
        Sleep(1000);
        printf("Starting... 3...");
        Sleep(1000);
        printf(" 2...");
        Sleep(1000);
        printf(" 1...\n\n");
        Sleep(1000);
    #else
        sleep(1);
        printf("Starting... 3...");
        sleep(1);
        printf(" 2...");
        sleep(1);
        printf(" 1...\n\n");
        sleep(1);
    #endif
}

Stats game_loop() {
    #ifdef _WIN32
        // Save default Windows console attributes
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        WORD saved_attributes;

        GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
        saved_attributes = consoleInfo.wAttributes;
    #endif

    char current_input;
    char *sentence = select_sentence();

    // Initialize stats
    Stats current_stats = {0.0, 100.0};
    unsigned int correct = 0, incorrect = 0;

    printf("\n\n%s\n\n", sentence);

    // Start "timer"
    clock_t start = clock();

    int i = 0;
    while (sentence[i] != '\0') {
        current_input = getch();

        // Handling enter (stop game)
        if (current_input == '\n' || current_input == '\r') {
            break;
        }

        // Handling backspace
        if (current_input == 8) {
            if (i != 0) {
                printf("\b");
                --i;
            } 

            continue;
        }

        // Check whether user input was correct
        if (compare_chars(current_input, sentence[i])) {
            ++correct;
            set_console_style((Style){green, false});
            printf("%c", current_input);
        } else {
            ++incorrect;
            set_console_style((Style){red, false});
            printf("%c", current_input);
        }

        // Reset console style to default
        #ifdef _WIN32
            SetConsoleTextAttribute(hConsole, saved_attributes);
        #else
            printf(ANSI_COLOR_RESET);
        #endif

        ++i;
    }

    // Calculate accuracy, handle case for dividing by 0
    current_stats.accuracy = (correct + incorrect == 0) ? 0.0 \
                            : (double) correct / ((double) (correct + incorrect)) * 100;

    // Stop timer and calculate time taken to type in minutes
    clock_t end = clock();
    double minutes = ((double) (end - start) / CLOCKS_PER_SEC) / 60;

    // Calculate (Gross) Words Per Minute
    current_stats.wpm = ((double) (correct + incorrect) / 5) / minutes;

    return current_stats;
}

int main() {
    #ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        WORD saved_attributes;

        GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
        saved_attributes = consoleInfo.wAttributes;
    #endif

    printf(
        "\n\n"
        "_______   _______ _____   _____ _____ _____ _____  \n"
        "|_   _\\ \\ / / ___ \\  ___| |_   _|  ___/  ___|_   _|\n"
        "  | |  \\ V /| |_/ / |__     | | | |__ \\ `--.  | | \n"  
        "  | |   \\ / |  __/|  __|    | | |  __| `--. \\ | | \n"  
        "  | |   | | | |   | |___    | | | |___/\\__/ / | | \n"
        "  \\_/   \\_/ \\_|   \\____/    \\_/ \\____/\\____/  \\_/"  
        "\n\n\n"
    );

    printf("Press ENTER to begin typing :^)\n");
    char input = getch();

    if (input == '\n' || input == '\r') {
        Stats game_stats = game_loop();
        printf("\n\n=====\n");

        printf("Accuracy: %.2f%%\n", game_stats.accuracy);
        printf("WPM: %.2f\n", game_stats.wpm);

        printf("Score: ");
        #ifdef _WIN32
            set_console_style((Style){green, true});
        #else 
            set_console_style((Style){yellow, false});
        #endif
        printf("%.2f", game_stats.accuracy * game_stats.wpm);

        #ifdef _WIN32
            SetConsoleTextAttribute(hConsole, saved_attributes);
        #else
            printf(ANSI_COLOR_RESET);
        #endif

        printf("\n=====\n\n\n");
    }

    return 0;
}
