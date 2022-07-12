#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <conio.h>
#include <string.h>
#include "sentences.h"

#define ARRAY_SIZE(arr) sizeof(arr) / sizeof(arr[0])

#ifdef _WIN32
    #include <windows.h>
#else
    #define ANSI_COLOR_RED     "\x1b[31m"
    #define ANSI_COLOR_GREEN   "\x1b[32m"
    #define ANSI_COLOR_YELLOW  "\x1b[33m"
    #define ANSI_COLOR_RESET   "\x1b[0m"
#endif

typedef struct Stats {
    double wpm;
    double accuracy;
} Stats;

char *select_sentence() {
    srand(time(NULL));
    size_t total = ARRAY_SIZE(sentences);
    return (sentences[rand() % total]);
}

bool compare_letters(char input, char solution) {
    return (input == solution ? true : false);
}

char take_input() {
    char c = _getch();
    return c;
}

Stats game_loop() {
    #ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        WORD saved_attributes;

        GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
        saved_attributes = consoleInfo.wAttributes;
    #endif

    Stats current_stats = {
        0.0, 
        100.0
    };

    char current_input;
    char *sentence = select_sentence();

    unsigned int correct = 0, incorrect = 0;

    printf("\n\n%s\n\n", sentence);

    Sleep(1000);
    printf("Starting... 3...");
    Sleep(1000);
    printf(" 2...");
    Sleep(1000);
    printf(" 1...\n\n");
    Sleep(1000);

    clock_t start = clock();
    int i = 0;
    while (sentence[i] != '\0') {
        current_input = take_input();

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

        if (compare_letters(current_input, sentence[i])) {
            ++correct;

            #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
            #else
                printf(ANSI_COLOR_GREEN);
            #endif

            printf("%c", current_input);
        } else {
            ++incorrect;

            #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            #else 
                printf(ANSI_COLOR_RED);
            #endif

            printf("%c", current_input);
        }

        #ifdef _WIN32
            SetConsoleTextAttribute(hConsole, saved_attributes);
        #else
            printf(ANSI_COLOR_RESET);
        #endif

        ++i;
    }

    current_stats.accuracy = (correct + incorrect == 0) ? 0.0 : (double) correct / ((double) (correct + incorrect)) * 100;

    clock_t end = clock();
    double minutes = ((double) (end - start) / CLOCKS_PER_SEC) / 60;

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
    char input = getche();

    if (input == '\n' || input == '\r') {
        Stats game_stats = game_loop();
        printf("\n\n=====\n");

        printf("Accuracy: %.2f%%\n", game_stats.accuracy);
        printf("WPM: %.2f\n", game_stats.wpm);

        printf("Score: ");

        #ifdef _WIN32
            SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN);
        #else 
            printf(ANSI_COLOR_YELLOW);
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
