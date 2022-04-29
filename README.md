# Matrix_SFML

A recreation of the ["digital rain" effect from The Matrix](https://en.wikipedia.org/wiki/Matrix_digital_rain)

This is one of my favorite things to make when I try out a new graphics library

I first made this in Processing about a year ago but this one is in Visual C++ 15 with [SFML](https://www.sfml-dev.org/)

The font is [Noto Sans JP](https://fonts.google.com/noto/specimen/Noto+Sans+JP/) from Google Fonts

## How to build

I have zero idea how to package C++ projects for GitHub so you'll have to bear with my inexperience here lol

1. Download the repo
2. Download [SFML 2.5.1](https://www.sfml-dev.org/download/sfml/2.5.1/) (Visual C++ 15 (2017)) and put it into a folder called "SFML-2.5.1" in directory of the solution
3. Build the solution with Visual Studio
4. Copy the .dll files from SFML-2.5.1/bin and NotoSansJP-Regular.otf into the same folder as your executable
5. Run your executable
