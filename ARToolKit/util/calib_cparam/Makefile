INC_DIR= ../../include
LIB_DIR= ../../lib
BIN_DIR= ../../bin

LDFLAG=-pthread -lgstreamer-0.10 -lgobject-2.0 -lgmodule-2.0 -lxml2 -lgthread-2.0 -lrt -lglib-2.0 -L/usr/X11R6/lib -L/usr/local/lib -L$(LIB_DIR)
LIBS= -lARgsub_lite -lARvideo -lAR -lpthread -lglut -lGLU -lGL -lXi -lX11 -lm
CFLAG= -O -pthread -I/usr/include/gstreamer-0.10 -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -I/usr/include/libxml2 -I/usr/X11R6/include -g -I$(INC_DIR)


all: $(BIN_DIR)/calib_cparam

$(BIN_DIR)/calib_cparam: calib_cparam.o calib_cparam_sub.o
	cc -o $(BIN_DIR)/calib_cparam calib_cparam.o calib_cparam_sub.o\
	   $(LDFLAG) $(LIBS)

calib_cparam.o: calib_cparam.c calib_cparam.h
	cc -c $(CFLAG) calib_cparam.c

calib_cparam_sub.o: calib_cparam_sub.c calib_cparam.h
	cc -c $(CFLAG) calib_cparam_sub.c

clean:
	rm -f calib_cparam.o calib_cparam_sub.o
	rm -f $(BIN_DIR)/calib_cparam

allclean:
	rm -f calib_cparam.o calib_cparam_sub.o
	rm -f $(BIN_DIR)/calib_cparam
	rm -f Makefile
