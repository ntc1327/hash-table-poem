OBJECTS = node.o main.o
HEADERS = node.h
Project3: $(OBJECTS)
	g++ $^ -o $@

%.o: %.cpp $(HEADERS)
	g++ -c $< -o $@

clean:
	rm -i *.o Project3

run:
	./Project3 poem.txt paper.txt


