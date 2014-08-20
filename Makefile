SOURCES=counter.cpp
OBJECTS=$(SOURCES:.cpp=.o)
CXXFLAGS= -c -Wall -std=c++11 
LIBS=-lMinuit -lboost_program_options
OUT=counter.out
CC=g++
all : $(SOURCES) $(OUT)

$(OUT) :  $(OBJECTS)
		g++ $(OBJECTS) $(LIBS) -o $@
		
.cpp.o :  $(SOURCES)
		  $(CC) $(CXXFLAGS) $< -o $@
clean :
		rm -f *.o rm *.so* *.out

