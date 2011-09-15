INC_DIR= ../../include
LIB_DIR= ../../lib
BIN_DIR= ../../bin

LDFLAG=-pthread -lgstreamer-0.10 -lgobject-2.0 -lgmodule-2.0 -lxml2 -lgthread-2.0 -lrt -lglib-2.0 -L/usr/X11R6/lib -L/usr/local/lib -L$(LIB_DIR)
LIBS= -lARgsub -lARvideo -lAR -lpthread -lglut -lGLU -lGL -lXi -lX11 -lm
CFLAG= -O -pthread -I/usr/include/gstreamer-0.10 -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -I/usr/include/libxml2 -I/usr/X11R6/include -g -I$(INC_DIR)

OBJS = draw_object.o
HEADDERS = draw_object.h

all: $(BIN_DIR)/exview

$(BIN_DIR)/exview: exview.o $(OBJS)
	cc -o $(BIN_DIR)/exview exview.o $(OBJS) $(LDFLAG) $(LIBS)

exview.o: exview.c $(HEADDERS)
	cc -c $(CFLAG) exview.c

draw_object.o: draw_object.c $(HEADDERS)
	cc -c $(CFLAG) draw_object.c

clean:
	rm -f *.o
	rm -f $(BIN_DIR)/exview

allclean:
	rm -f *.o
	rm -f $(BIN_DIR)/exview
	rm -f Makefile
