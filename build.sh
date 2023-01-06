set -xe

cc -Wall -c hm.c
ar -cvq libhm.a hm.o
