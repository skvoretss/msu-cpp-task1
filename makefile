CFLAGS = -g -c -O2 -ftrapv -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self -Wswitch-default -Wfloat-equal -Wshadow -Wpointer-arith -Wtype-limits -Wempty-body -Wlogical-op -Wmissing-field-initializers -Wcast-qual -Wwrite-strings

all: P01_
    
P01_: main.o class.o 
	g++ main.o class.o -o P01_out    
    
main.o: main.cpp
	g++ $(CFLAGS) main.cpp -lm 
	
class.o: class.cpp
	g++ $(CFLAGS) class.cpp -lm


clean:
	rm -rf *.o P01_
