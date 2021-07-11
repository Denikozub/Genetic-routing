TARGET=main
CXX=g++
CXXFLAGS=-O2 -ftrapv -fsanitize=undefined -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self -Wswitch-default -Wfloat-equal -Wshadow -Wpointer-arith -Wtype-limits -Wempty-body -Wlogical-op -Wmissing-field-initializers -Wcast-qual -Wwrite-strings -lm
OBJECTS=main.o matrix.o dense.o sparse.o

all:$(TARGET)

clean:
	rm -f *.o $(TARGET) core

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $<

matrix.o: matrix.hpp
dense.o: dense.hpp
sparse.o: sparse.hpp
