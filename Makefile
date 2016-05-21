CC=g++-4.9
CFLAGS=
LDFLAGS=
SOURCES=graph_parser.cpp Graph.hpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=graph_parser

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@