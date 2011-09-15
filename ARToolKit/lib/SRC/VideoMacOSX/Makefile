UNAME = $(shell uname)

AR_HOME = ../../..

CPPFLAGS = -I$(AR_HOME)/include
CFLAGS = -fpascal-strings -O -pthread -I/usr/include/gstreamer-0.10 -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -I/usr/include/libxml2 -I/usr/X11R6/include -g
CXXFLAGS = -O -pthread -I/usr/include/gstreamer-0.10 -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -I/usr/include/libxml2 -I/usr/X11R6/include -g
LDFLAGS = -L$(AR_HOME)/lib -pthread -lgstreamer-0.10 -lgobject-2.0 -lgmodule-2.0 -lxml2 -lgthread-2.0 -lrt -lglib-2.0 -L/usr/X11R6/lib -L/usr/local/lib
LIBS = -lpthread -lglut -lGLU -lGL -lXi -lX11 -lm
AR = ar
ARFLAGS = rs
RANLIB = 

TARGET = $(AR_HOME)/lib/libARvideo.a

HEADERS = \
	$(AR_HOME)/include/AR/video.h \
    videoInternal.h \
	ARVideoSettingsController.h

OBJS = \
    video.o \
    ARVideoSettingsController.o
	
# Implicit rule, to compile Objective-C files with the .m suffix.
%.o : %.m
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $< -o $@

default build all: $(TARGET)

$(OBJS) : $(HEADERS)

$(TARGET): $(OBJS)
	$(AR) ruv $@ $?
	$(RANLIB) $@

clean:
	-rm -f *.o *~ *.bak
	-rm $(TARGET)

allclean:
	-rm -f *.o *~ *.bak
	-rm $(TARGET)
	-rm -f Makefile
