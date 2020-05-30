FLAGS:=-std=c++11 -I. -I.. -I../include
LIBGPP:=g++ -g -c $(FLAGS)

Graphics.a : ShaderLoader.o lodepng.o Texture.o g2d.a g3d.a
	ar -x g2d.a
	ar -x g3d.a
	ar -rc Graphics.a *.o

g2d.a : FORCE
	cd g2d; make; cp g2d.a ..

g3d.a : FORCE
	cd g3d; make; cp g3d.a ..

lodepng.o : lodepng/lodepng.cpp
	$(LIBGPP) $<

.cpp.o : 
	$(LIBGPP) $<

clean :
	rm g2d/*.o
	rm g3d/*.o
	rm Graphics.a
	rm Texture.o

FORCE:
