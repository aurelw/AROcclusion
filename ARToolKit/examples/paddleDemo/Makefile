INC_DIR= ../../include
LIB_DIR= ../../lib
BIN_DIR= ../../bin

LDFLAG=-pthread -lgstreamer-0.10 -lgobject-2.0 -lgmodule-2.0 -lxml2 -lgthread-2.0 -lrt -lglib-2.0 -L/usr/X11R6/lib -L/usr/local/lib -L$(LIB_DIR)
LIBS= -lARgsub -lARvideo  -lARMulti -lAR -lpthread -lglut -lGLU -lGL -lXi -lX11 -lm
CFLAG= -O -pthread -I/usr/include/gstreamer-0.10 -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -I/usr/include/libxml2 -I/usr/X11R6/include -g -I$(INC_DIR)

OBJS = command_sub.o util.o paddle.o
HEADDERS = command_sub.h util.h paddle.h

all: $(BIN_DIR)/paddleDemo

$(BIN_DIR)/paddleDemo: paddleDemo.o $(OBJS)
	cc -o $(BIN_DIR)/paddleDemo paddleDemo.o $(OBJS) $(LDFLAG) $(LIBS)

paddleDemo.o: paddleDemo.c $(HEADDERS)
	cc -c $(CFLAG) paddleDemo.c

command_sub.o: command_sub.c $(HEADDERS)
	cc -c $(CFLAG) command_sub.c

util.o: util.c $(HEADDERS)
	cc -c $(CFLAG) util.c

paddle.o: paddle.c $(HEADDERS)
	cc -c $(CFLAG) paddle.c

clean:
	rm -f *.o
	rm -f $(BIN_DIR)/paddleDemo

allclean:
	rm -f *.o
	rm -f $(BIN_DIR)/paddleDemo
	rm -f Makefile
