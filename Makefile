CC = g++
CFLAGS = -Wall -std=c++11
OBJECTS = *.cpp

test: $(OBJECTS)
	$(CC) $(OBJECTS) -o test $(CFLAGS)

clean:
	rm test *.o