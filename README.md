# Typespeed

This is a simple console game that lets you practice your touch typing on a variety of \
sentences ranging from around 80-120 words each. You can finish the game by completing \
the text or stop at any time by pressing `ENTER`. At the end, the game lets you view \
basic statistics about your typing such as your speed in WPM (gross words per minute) and your accuracy percentage.

## Instructions

First, clone this repository locally using `git clone`:

```shell
git clone https://github.com/ybrenning/typespeed.git
cd typespeed
```

Build and run the project with CMake:

```shell
mkdir build
cd build
cmake ..
cmake --build . --config Release
./Release/typespeed
```
