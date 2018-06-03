# t9-dictionary-demo
This is a T9 dictionary toy, I'm not sure if you'll find this useful. I made it as an assignment for an algorithms and data structures course at my university.

Here's an animated example:  
![demo GIF](http://img.rhino.ws/t9-dictionary-demo.gif)

Uses words from [first20hours' dictionary](https://github.com/first20hours/google-10000-english), but any dictionary can be used.

The application works by loading words from the dictionary into a [ternary search tree](https://en.wikipedia.org/wiki/Ternary_search_tree).

At the moment GTK+ 2 is used, since I've had some technical difficulties getting GTK+ 3 or gtkmm to work on the destination (university's) server, so I went with what worked there. However, if I decide to work some more on this project in the future, I'll likely move to gtkmm.

The code probably needs a lot of refactoring, which I might choose to do if I have the time. If I *do* switch to gtkmm, that will sure help a lot.

To build on a GNU/Linux system, simply issue `make` (or `make run` to run immediately after building).

So... uh... enjoy or whatever!