###################################
# OS COURSE - CS 433 example
# 
###################################
CC = g++			# use g++ for compiling c++ code or gcc for c code
CFLAGS = -O3 -Wall -std=c++17		# compilation flags: -g for debugging. Change to -O2 or -O3 for optimized code.
LIB = -lm			# linked libraries	
LDFLAGS = -L.			# link flags
PROG = test1 test2			# target executables (output)
SRCS = test1.cpp test2.cpp pcbtable.cpp readyqueue.cpp        # .c or .cpp source files.
OBJ = $(SRCS:.cpp=.o) 	# object files for the target. Add more to this and next lines if there are more than one source files.

all : $(PROG)

test1:  test1.o pcbtable.o readyqueue.o
	$(CC) -o test1 test1.o pcbtable.o readyqueue.o $(LDFLAGS) $(LIB)

test2:  test2.o pcbtable.o readyqueue.o
	$(CC) -o test2 test2.o pcbtable.o readyqueue.o $(LDFLAGS) $(LIB)

.cpp.o:
	$(CC) -c $(CFLAGS) $< -o $@
	

# cleanup
clean:
	/bin/rm -f *.o $(PROG) .depend

# DO NOT DELETE
