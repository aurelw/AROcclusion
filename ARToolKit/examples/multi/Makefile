INC_DIR= ../../include
LIB_DIR= ../../lib
BIN_DIR= ../../bin

LDFLAG=-pthread -lgstreamer-0.10 -lgobject-2.0 -lgmodule-2.0 -lxml2 -lgthread-2.0 -lrt -lglib-2.0 -L/usr/X11R6/lib -L/usr/local/lib -L$(LIB_DIR)
LIBS= -lARgsub -lARvideo -lARMulti -lAR -lpthread -lglut -lGLU -lGL -lXi -lX11 -lm
CFLAG= -O -pthread -I/usr/include/gstreamer-0.10 -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -I/usr/include/libxml2 -I/usr/X11R6/include -g -I$(INC_DIR)

OBJS =
HEADDERS =

all: $(BIN_DIR)/multiTest

$(BIN_DIR)/multiTest: multiTest.o $(OBJS)
	cc -o $(BIN_DIR)/multiTest multiTest.o $(OBJS) $(LDFLAG) $(LIBS)

multiTest.o: multiTest.c $(HEADDERS)
	cc -c $(CFLAG) multiTest.c

clean:
	rm -f *.o
	rm -f $(BIN_DIR)/multiTest

allclean:
	rm -f *.o
	rm -f $(BIN_DIR)/multiTest
	rm -f Makefile
