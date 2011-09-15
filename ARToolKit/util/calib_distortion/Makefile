INC_DIR= ../../include
LIB_DIR= ../../lib
BIN_DIR= ../../bin

LDFLAG=-pthread -lgstreamer-0.10 -lgobject-2.0 -lgmodule-2.0 -lxml2 -lgthread-2.0 -lrt -lglib-2.0 -L/usr/X11R6/lib -L/usr/local/lib -L$(LIB_DIR)
LIBS= -lARgsub_lite -lARvideo -lAR -lpthread -lglut -lGLU -lGL -lXi -lX11 -lm
CFLAG= -O -pthread -I/usr/include/gstreamer-0.10 -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -I/usr/include/libxml2 -I/usr/X11R6/include -g -I$(INC_DIR)


all: $(BIN_DIR)/calib_dist

$(BIN_DIR)/calib_dist: calib_dist.o check_dist.o
	cc -o $(BIN_DIR)/calib_dist calib_dist.o check_dist.o\
	   $(LDFLAG) $(LIBS)

calib_dist.o: calib_dist.c calib_dist.h
	cc -c $(CFLAG) calib_dist.c

check_dist.o: check_dist.c calib_dist.h
	cc -c $(CFLAG) check_dist.c

clean:
	rm -f calib_dist.o check_dist.o
	rm -f $(BIN_DIR)/calib_dist

allclean:
	rm -f calib_dist.o check_dist.o
	rm -f $(BIN_DIR)/calib_dist
	rm -f Makefile
