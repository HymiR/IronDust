#!/bin/make
CC=g++
LDFLAGS=-lGL -lGLU -lglfw -lboost_system -lboost_filesystem -lcg
CFLAGS=-g -O3 -pipe -Wall -fomit-frame-pointer
CXXFLAGS=$(CFLAGS)
APPNAME=irondust
BUILDNAME=$(APPNAME)
SRCS=irondust.cpp
OBJDIR=.

all: $(SRCS) $(APPNAME)

objects: clean
	$(CC) $(CXXFLAGS) -c $(SRCS)

$(APPNAME): objects
	$(CC) $(LDFLAGS) -o $(BUILDNAME) $(OBJDIR)/*.o

run: $(SRCS) $(APPNAME)
	./$(BUILDNAME) &

clean:
	rm -vf $(BUILDNAME)
	rm -vf $(OBJDIR)/*.o
