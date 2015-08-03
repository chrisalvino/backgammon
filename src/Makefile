
CC = g++
CFLAGS = -Wall -Werror -g
LDFLAGS = -lm
LD = ld

DIRS = common
MAIN = zeno

# define the C source files
OBJS = main.o common.o

SRCS = $(OBJS:.o=.cpp)

#
# The following part of the makefile is generic; it can be used to 
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

$(MAIN): ${OBJS}
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

.PHONY: depend clean common

common.o:
	cd common && $(MAKE)
	cp common/common.o .

all: $(MAIN)
	@echo  Simple compiler named mycc has been compiled

clean:
	-$(RM) -f $(MAIN) $(OBJS)
	-for d in $(DIRS); do (cd $$d; $(MAKE) clean ); done	

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

depend: $(SRCS)
	makedepend $(INCLUDES) $^	

# DO NOT DELETE THIS LINE -- make depend needs it