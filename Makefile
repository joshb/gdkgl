PREFIX=/opt/gnome2
CC=gcc
CFLAGS=-g -Wall -ansi `pkg-config gtk+-2.0 --cflags`
LDFLAGS=`pkg-config gtk+-2.0 --libs` -L/usr/X11R6/lib -lGL -lGLU
OBJS=gdkgl-x11.o gdkgl.o test.o

all: $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o test

clean:
	rm -f $(OBJS)
	rm -f test

gdkgl-x11.o: gdkgl-x11.c
gdkgl.o: gdkgl.c
test.o: test.c
