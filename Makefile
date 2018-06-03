DIR = `basename "$(PWD)"`
CXXFLAGS = -std=c++11 -O2
CXXFLAGS += `pkg-config --cflags gtk+-2.0`
LDFLAGS += `pkg-config --libs gtk+-2.0`

.PHONY: all run clean tar

all: T9 dictionary.txt

dictionary.txt:
		wget -O $@ https://raw.githubusercontent.com/first20hours/\
google-10000-english/master/google-10000-english-no-swears.txt

T9: *.cpp *.h
		$(CXX) $(CXXFLAGS) -o $@ *.cpp $(LDFLAGS)

run: all
		./T9 dictionary.txt

clean:
		rm -f T9 dictionary.txt

tar: clean
		tar -cvzf $(DIR).tar.gz *.h *.cpp Makefile
