# Typespeed

This is a simple console game that lets you practice your touch typing on a variety of sentences ranging from around 80-120 words each.
You can finish the game by completing the text or stop at any time by pressing <kbd>ENTER</kbd> .

At the end, the game lets you view basic statistics about your typing such as your speed in WPM (gross words per minute) and your accuracy percentage.

![Demo](https://github.com/ybrenning/typespeed/blob/master/img/demo.gif)

## Instructions

### Prerequisites

A standards-compliant C compiler as well as the standard C library and CMake.

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
[Speed Typing Online](https://www.speedtypingonline.com/typing-equations) \
[Network-Science](http://www.network-science.de/ascii/)
