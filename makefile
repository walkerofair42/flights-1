CC = gcc
CFLAGS = -g
OBJECTS = main.o list.o fileconverter.o utils.o
OUT_FILES = AA.txt DL.txt F.txt OO.txt

prog: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS)
%.o: %.c
	$(CC) $(CFLAGS) -c $<
clean:
	rm -f *.o core
cleanoutput:
	rm -f $(OUT_FILES)