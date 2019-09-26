# Makefile for Rt, a simple raytracer.
#
# Brian Hammond <RtDev@BrianHammond.com>
# $Id$
#
# Targets:
# 
# <default>        build standalone executable that renders a test scene of 
#                  400x300 to ./output.png

CC        := gcc
EXE       := Rt
SRCS      := $(wildcard *.cpp)
OBJS      := $(patsubst %.cpp,%.o,$(filter %.cpp, $(SRCS)))

CXX_FLAGS += -DSTANDALONE -DSCALAR_DOUBLE
CXX_FLAGS += -ansi -Wall -pedantic

#CXX_FLAGS += -DDEBUG -fomit-frame-pointer -Wno-deprecated -funroll-all-loops 
CXX_FLAGS += -DDEBUG -g 

#CXX_FLAGS += -pg
CXX_FLAGS += -O3 -ffast-math 
CXX_FLAGS += -I../include

#TODO I guess this should be part of a configure script.
#CXX_FLAGS += -mfpmath=sse #altivec ?

#LD_FLAGS  += -pg
LD_FLAGS  += -lstdc++ -lm -lz -lpng

.PHONY: setup clean install

$(EXE): $(OBJS)
	$(CC) -o $(EXE) $(OBJS) $(LD_FLAGS)

$(OBJS): %.o: %.cpp
	$(CC) $(CXX_FLAGS) -c $< -o $@

.%.d: %.cpp
	@echo building dependencies for $< ...
	@set -e; $(CC) -MM $(CXX_FLAGS) $< \
        | sed 's/\($*\)\.o[ :]*/\1.o $@ : /g' > $@; \
        [ -s $@ ] || rm -f $@

clean:
	rm -f .*d $(OBJS) *~ .*~ core $(EXE)

install:
	install -m 0644 $(EXE) /usr/local/bin/$(EXE)

run: $(EXE)
	./Rt 400 300 && display output.png

-include $(SRCS:%.cpp=.%.d)

