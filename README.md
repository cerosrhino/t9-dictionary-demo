# T9 dictionary demo
## Description
This is a T9 dictionary toy; I'm not sure if you'll find it useful. I made it as an assignment for an algorithms and data structures course at my university. It's been unmaintained for a while, but I might come back to it given sufficient time and motivation.

## An animated example
![demo GIF](http://img.rhino.ws/t9-dictionary-demo.gif)

## Technical details
The application works by loading words from the dictionary into a [ternary search tree](https://en.wikipedia.org/wiki/Ternary_search_tree). There's also a deque class. I'm aware of the existence of [std::deque](http://en.cppreference.com/w/cpp/container/deque), but part of the assignment was to avoid readily available containers, for obvious reasons (it was an algorithms and data structures course, remember?).

Uses words from [first20hours' dictionary](https://github.com/first20hours/google-10000-english), but any dictionary can be used.

The UI is controlled entirely with the mouse, there's no keyboard input. Sorry. I don't think it would make much sense anyway.

At the moment GTK+ 2 is used, since I've had some technical difficulties getting GTK+ 3 or gtkmm to work on the destination (university's) server, so I went with what worked there. However, if I decide to work some more on this project in the future, I'll likely move to gtkmm.

The code probably needs a lot of refactoring, which I might choose to do if I have the time. If I *do* switch to gtkmm, that will sure help a lot.

## Build instructions

To build on a GNU/Linux system, simply issue `make` (or `make run` to run immediately after building).

## Where's my punctuation?
Oops. There is none. Only letters and spaces can be entered. Sorry!

## Bottom line
As I said, this probably isn't the most useful thing in the universe by itself. However, you might find parts of it at least somewhat useful or informative in a way. So... uh... enjoy or whatever!