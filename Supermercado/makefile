COMP      := g++ -std=c++11
CPPFLAGs  := -I include
CFLAGS    := -Wall -pedantic -ansi

diary: src/main.cpp
	$(COMP) $(CPPFLAGs) $(CFLAGS) -o SPM src/main.cpp

.PHONY: clean
clean:
	-rm SPM
