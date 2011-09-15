INC_DIR= ../../include
LIB_DIR= ../../lib
BIN_DIR= ../../bin

LDFLAG=-pthread -lgstreamer-0.10 -lgobject-2.0 -lgmodule-2.0 -lxml2 -lgthread-2.0 -lrt -lglib-2.0 -L/usr/X11R6/lib -L/usr/local/lib -L$(LIB_DIR)
LIBS= -lARgsub -lARvideo -lARMulti -lAR -lpthread -lglut -lGLU -lGL -lXi -lX11 -lm
CFLAG= -O -pthread -I/usr/include/gstreamer-0.10 -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -I/usr/include/libxml2 -I/usr/X11R6/include -g -I$(INC_DIR)

OBJS = paddle.o
HEADDERS = paddle.h

all: $(BIN_DIR)/paddleInteractionTest

$(BIN_DIR)/paddleInteractionTest: paddleInteractionTest.o $(OBJS)
	cc -o $(BIN_DIR)/paddleInteractionTest paddleInteractionTest.o $(OBJS) $(LDFLAG) $(LIBS)

paddleInteractionTest.o: paddleInteractionTest.c $(HEADDERS)
	cc -c $(CFLAG) paddleInteractionTest.c

paddle.o: paddle.c $(HEADDERS)
	cc -c $(CFLAG) paddle.c

clean:
	rm -f *.o
	rm -f $(BIN_DIR)/paddleInteractionTest

allclean:
	rm -f *.o
	rm -f $(BIN_DIR)/paddleInteractionTest
	rm -f Makefile
