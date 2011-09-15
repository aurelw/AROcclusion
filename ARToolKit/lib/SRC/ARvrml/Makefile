UNAME = $(shell uname)

AR_HOME = ../../..
AR_CPPFLAGS = -I$(AR_HOME)/include

VRML_HOME = /usr
ifeq "$(UNAME)" "Darwin"
	VRML_HOME = /sw
endif
VRML_CPPFLAGS = -I$(VRML_HOME)/include/openvrml -I/usr/X11R6/include

CPPFLAGS = $(AR_CPPFLAGS) $(VRML_CPPFLAGS)
CFLAGS = -O -pthread -I/usr/include/gstreamer-0.10 -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -I/usr/include/libxml2 -I/usr/X11R6/include -g
CXXFLAGS = -O -pthread -I/usr/include/gstreamer-0.10 -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -I/usr/include/libxml2 -I/usr/X11R6/include -g
AR = ar
ARFLAGS = rs
RANLIB = 

TARGET = $(AR_HOME)/lib/libARvrml.a

HEADERS = \
    $(AR_HOME)/include/AR/arvrml.h \
    arViewer.h

OBJS = \
	arViewer.o \
	arViewerCapi.o

# Implicit rule, to compile C++ files with the .cpp suffix (rule already exists for .cc).
%.o : %.cpp
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $< -o $@

default build all: $(TARGET)

$(OBJS): $(HEADERS)

$(TARGET): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^
	$(RANLIB) $@ 

clean:
	-rm -f *.o *~ *.bak
	-rm $(TARGET)

allclean:
	-rm -f *.o *~ *.bak
	-rm $(TARGET)
	-rm -f Makefile
