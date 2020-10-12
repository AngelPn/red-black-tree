OBJS= main.o RedBlackTree.o
CFLAGS = -g -Wall -I.
PROGRAM= rbt

$(PROGRAM): clean $(OBJS)
	g++ -g $(OBJS) -o $(PROGRAM)

clean:
	rm -f $(PROGRAM) $(OBJS)