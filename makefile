CC=cc
CFLAGS=-Wall -Wextra
BINS=libtest libhm.so

all: $(BINS) 

libhm.so: hm.c hm.h
	$(CC) $(CFLAGS) -fPIC -shared -o $@ hm.c -lc

libtest: test.c libhm.so 
	$(CC) $(CFLAGS) -o $@ $^ -L. -lhm

clean:
	rm $(BINS)

