CC = g++
CFLAGS = -g -Wall -std=c++11
OBJECTS = *.cpp

test: $(OBJECTS)
	$(CC) $(OBJECTS) -o test $(CFLAGS)

clean:
	rm test *.o