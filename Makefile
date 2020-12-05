# Copyright (c) 2020, Patrik Nyström
# All rights reserved.
# This source code is licensed under the BSD-style license found in the
# LICENSE file in the root directory of this source tree.

CXX := g++
CXXFLAGS := -O2 -Wall -Wextra -pedantic
OBJS := hangman.o
PREFIX := /usr
BINDIR := ${PREFIX}/local/bin

.PHONY: all clean

all: hangman

hangman: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

hangman.o: hangman.cpp
	$(CXX) $(CXXFLAGS) -c hangman.cpp

install:
	install -Dm755 hangman $(DESTDIR)$(BINDIR)/hangman

uninstall:
	rm -f $(DESTDIR)$(BINDIR)/hangman

clean:
	rm -f hangman $(OBJS)