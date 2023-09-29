OBJS	= main.o Utils.o Grafo.o
SOURCE	= main.cc Utils.cc Grafo.cc
HEADER	= ../include/Grafo.hh ../include/Utils.hh
OUT	= grafo.out
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.cc
	$(CC) $(FLAGS) main.cc 

Grafo.o: Grafo.cc
	$(CC) $(FLAGS) Grafo.cc 

Utils.o: Utils.cc
	$(CC) $(FLAGS) Utils.cc 


clean:
	rm -f $(OBJS) $(OUT)
