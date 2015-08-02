
DIRS = common
CC = g++
CFLAGS = -Wall -Werror -g
LDFLAGS = -lm


# define the C source files
SRCS = board.cpp

MAIN = zeno

OBJS = $(SRCS:.cpp=.o)

LIB1 = common

#
# The following part of the makefile is generic; it can be used to 
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

.PHONY: depend clean common

common:
	cd common && $(MAKE)

all: $(MAIN)
	@echo  Simple compiler named mycc has been compiled

$(MAIN): $(OBJS) 
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

clean:
	-$(RM) -f $(MAIN) $(OBJS)
	-for d in $(DIRS); do (cd $$d; $(MAKE) clean ); done	

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

depend: $(SRCS)
	makedepend $(INCLUDES) $^	

# DO NOT DELETE THIS LINE -- make depend needs it