FLAGS:=-std=c++11 -I../ -I../.. -I../../include
LIBGPP:=g++ -g -c $(FLAGS)

g2d.a : Image.o ImageShader.o
	ar cr g2d.a $^

.cpp.o :
	$(LIBGPP) $<

