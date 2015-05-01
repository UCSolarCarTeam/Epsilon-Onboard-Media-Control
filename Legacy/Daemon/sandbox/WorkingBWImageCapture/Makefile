CODE_FILES=test.cpp
OBJECTS=$(CODE_FILES:.cpp=.o)
OUTPUT=Test
CC=g++


all: $(CODE_FILES) $(OUTPUT)

$(OUTPUT): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

%.o : %.cpp
	$(CC) -c $< -o $@

# '%' is a wildcard, which remains consistent. $< is the dependencies, while $@ is the target.


.phony : clean run size

run: $(OUTPUT)
	./$(OUTPUT)

size: $(OUTPUT)
	wc -c $(OUTPUT)

clean:
	rm -rf $(OUTPUT) $(OBJECTS)

