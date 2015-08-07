
CC = g++
CFLAGS = -Wall -Werror -g
LDFLAGS = -lm
LD = ld

# define the C source files
OBJS = board.o game.o evaluation.o randomplayer.o defaultdie.o die.o

SRCS = $(OBJS:.o=.cpp)

common.o: ${OBJS} 
	$(LD) -arch x86_64 -r -o $@ $^

#
# The following part of the makefile is generic; it can be used to 
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

.PHONY: clean

clean:
	$(RM) *.o *.d *~ $(MAIN)

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@
	$(CC) -MM $(CFLAGS) $*.cpp > $*.d
	@mv -f $*.d $*.d.tmp
	@sed -e 's|.*:|$*.o:|' < $*.d.tmp > $*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $*.d.tmp | fmt -1 | \
	    sed -e 's/^ *//' -e 's/$$/:/' >> $*.d
	@rm -f $*.d.tmp	

-include $(OBJS:.o=.d)
