
CC = g++
CFLAGS = -Wall -Werror -g
LDFLAGS = -lm
LD = ld

# define the C source files
SRCS = board.cpp

OBJS = $(SRCS:.cpp=.o)

common.o: ${OBJS} 
	$(LD) -arch x86_64 -r -o $@ $<

#
# The following part of the makefile is generic; it can be used to 
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

.PHONY: depend clean

clean:
	$(RM) *.o *~ $(MAIN)

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

depend: $(SRCS)
	makedepend $(INCLUDES) $^	

# DO NOT DELETE THIS LINE -- make depend needs it