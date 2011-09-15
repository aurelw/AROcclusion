UNAME = $(shell uname)

AR_HOME = ../..
AR_CPPFLAGS = -I$(AR_HOME)/include
AR_LDFLAGS = -L$(AR_HOME)/lib

VRML_HOME = /usr
ifeq "$(UNAME)" "Darwin"
    VRML_HOME = /sw
endif
VRML_CPPFLAGS =
VRML_LDFLAGS = -L$(VRML_HOME)/lib

CPPFLAGS = $(AR_CPPFLAGS) $(VRML_CPPFLAGS)
CFLAGS = -O -pthread -I/usr/include/gstreamer-0.10 -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -I/usr/include/libxml2 -I/usr/X11R6/include -g
CXXFLAGS = -O -pthread -I/usr/include/gstreamer-0.10 -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -I/usr/include/libxml2 -I/usr/X11R6/include -g
LDFLAGS = $(AR_LDFLAGS) $(VRML_LDFLAGS) -pthread -lgstreamer-0.10 -lgobject-2.0 -lgmodule-2.0 -lxml2 -lgthread-2.0 -lrt -lglib-2.0 -L/usr/X11R6/lib -L/usr/local/lib
LIBS = -lARvrml -lARgsub_lite -lARvideo -lAR \
    -lopenvrml -lopenvrml-gl -lstdc++ -ljpeg -lpng -lz -lm \
    -lpthread -lglut -lGLU -lGL -lXi -lX11 -lm
AR = ar
ARFLAGS = rs
RANLIB = 

TARGET = $(AR_HOME)/bin/simpleVRML

HEADERS = \
    object.h

OBJS = \
    object.o \
    simpleVRML.o

default build all: $(TARGET)

$(OBJS) : $(HEADERS)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

clean:
	-rm -f *.o *~ *.bak
	-rm $(TARGET)

allclean:
	-rm -f *.o *~ *.bak
	-rm $(TARGET)
	-rm -f Makefile
