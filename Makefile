TARGET=main
CXX=g++
CXXFLAGS=-O2 -ftrapv -fsanitize=undefined -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self -Wswitch-default -Wfloat-equal -Wshadow -Wpointer-arith -Wtype-limits -Wempty-body -Wlogical-op -Wmissing-field-initializers -Wcast-qual -Wwrite-strings -lm
OBJECTS=genetic_algo.o gene.o population.o map_data.o point.o polygon.o segment.o vector.o

all:$(TARGET)

clean:
	rm -f *.o $(TARGET) core

$(TARGET): $(OBJECTS)
	$(CXX) -o $(TARGET) $(CXXFLAGS) test/main.cpp $(OBJECTS)

genetic_algo.o: 
	$(CXX) -c $(CXXFLAGS) genetic_algorithm/genetic_algo.cpp

gene.o: 
	$(CXX) -c $(CXXFLAGS) genetic_algorithm/gene.cpp

population.o: 
	$(CXX) -c $(CXXFLAGS) genetic_algorithm/population.cpp

map_data.o: 
	$(CXX) -c $(CXXFLAGS) genetic_data/map_data.cpp

point.o: 
	$(CXX) -c $(CXXFLAGS) geometry/point.cpp

polygon.o: 
	$(CXX) -c $(CXXFLAGS) geometry/polygon.cpp

segment.o: 
	$(CXX) -c $(CXXFLAGS) geometry/segment.cpp

vector.o: 
	$(CXX) -c $(CXXFLAGS) geometry/vector.cpp

