FLAGS:=-std=c++11 -I../../ -I../../include
LIBGPP:=g++ -g -c $(FLAGS)

g3d.a : DuplicatedPanel.o Line.o LineShader.o Panel.o TexturedShader.o Camera.o Scene.o
	ar cr g3d.a $^

.cpp.o :
	$(LIBGPP) $<

