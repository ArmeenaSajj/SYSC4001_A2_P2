CC=gcc
CFLAGS=-O2 -Wall -Wextra

.PHONY: part1 part2 part3 part4 part5 clean

part1:
	$(CC) $(CFLAGS) part1.c -o part1

part2:
	$(CC) $(CFLAGS) process2.c -o process2
	$(CC) $(CFLAGS) process1.c -o process1

part3:
	$(CC) $(CFLAGS) -DPART3_STRICT process2.c -o process2
	$(CC) $(CFLAGS) -DPART3_STRICT process1.c -o process1

clean:
	rm -f part1 process1 process2
