INC_DIR= ../../include
LIB_DIR= ../../lib
BIN_DIR= ../../bin

LDFLAG=-pthread -lgstreamer-0.10 -lgobject-2.0 -lgmodule-2.0 -lxml2 -lgthread-2.0 -lrt -lglib-2.0 -L/usr/X11R6/lib -L/usr/local/lib -L$(LIB_DIR)
LIBS= -lARgsub_lite -lARvideo -lAR -lpthread -lglut -lGLU -lGL -lXi -lX11 -lm
CFLAG= -O -pthread -I/usr/include/gstreamer-0.10 -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -I/usr/include/libxml2 -I/usr/X11R6/include -g -I$(INC_DIR)


all: $(BIN_DIR)/calib_camera2

$(BIN_DIR)/calib_camera2: main.o calib_dist.o calib_inp.o
	cc -o $(BIN_DIR)/calib_camera2 main.o calib_dist.o calib_inp.o\
	   $(LDFLAG) $(LIBS)

main.o: main.c calib_camera.h
	cc -c $(CFLAG) main.c

calib_dist.o: calib_dist.c calib_camera.h
	cc -c $(CFLAG) calib_dist.c

calib_inp.o: calib_inp.c calib_camera.h
	cc -c $(CFLAG) calib_inp.c

clean:
	rm -f main.o calib_dist.o calib_inp.o
	rm -f $(BIN_DIR)/calib_camera2

allclean:
	rm -f main.o calib_dist.o calib_inp.o
	rm -f $(BIN_DIR)/calib_camera2
	rm -f Makefile
