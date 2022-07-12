# Typespeed

This is a simple console game that lets you practice your touch typing on a variety of sentences ranging from around 80-120 words each.
You can finish the game by completing the text or stop at any time by pressing <kbd>ENTER</kbd> .

At the end, the game lets you view basic statistics about your typing such as your speed in WPM (gross words per minute) and your accuracy percentage.

![Demo](https://github.com/ybrenning/typespeed/blob/master/img/demo.gif)

## Instructions

### Prerequisites

A standards-compliant C compiler as well as the standard C library and CMake. \
An additional library necessary for cross-platform usage is `curses.h`.

#### Linux

```bash
$ sudo apt-get install libncurses5-dev libncursesw5-dev
```

#### Mac OS

```
$ brew install ncurses
```

#### Windows

* Open the MinGW Installation Manager
* Install the following packages:
    1. mingw32-libncurses (dll)
    2. mingw32-libcurses (dev)
    3. mingw32-libpdcurses (dll)
    4. mingw32-libpdcurses (dev)


### Build

First, clone this repository locally using `git clone`:

```bash
$ git clone https://github.com/ybrenning/typespeed.git
$ cd typespeed
```

Build and run the project with CMake:

```bash
$ mkdir build
$ cd build

$ cmake ..
$ cmake --build . --config Release
$ ./Release/typespeed
```

## References

[The Practice Text](https://thepracticetest.com/) \
[Agile Fingers](https://agilefingers.com/) \
[Speed Typing Online](https://www.speedtypingonline.com/typing-equations) \
[Network-Science](http://www.network-science.de/ascii/)
