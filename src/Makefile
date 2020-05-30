ifeq ($(GLCOMP), yes)
  GLFLAG:=-DOLDGL
endif

ifeq ($(OS), osx)
  FLAGS:=-g -std=c++14 -I.
  LIBGPP:=g++ -c $(FLAGS)
  SHARES:=-lassimp -lglew -lglfw -framework OpenGL
  Frameworks:=-F ./lib/macosx/Frameworks -framework SFML -framework sfml-audio -framework sfml-system -framework OpenGL
else
ifeq ($(OS), win)
  FLAGS:=-std=c++1z -I. -I./include -L./lib/win
  STATIC_FLAGS:=-static -static-libgcc -static-libstdc++ 
  LIBGPP:=g++ -c $(FLAGS)
  SHARES_SFML:=-lsfml-audio -lsfml-system
  SHARES:=-lglew32 -lglfw3 -lopengl32 -lgdi32 $(SHARES_SFML)
#VS2015 required
  SHARES_SFML_STATIC:=-DSFML_STATIC -lsfml-audio-s -lsfml-system-s -lwinmm -lgdi32 -lopenal32 -lflac -lvorbisenc -lvorbisfile -lvorbis -logg
  Frameworks:=
else
  FLAGS:=-g -std=c++14 -DOLDGL -I. $(shell pkg-config --cflags --libs sfml-audio glew glfw3)
  LIBGPP:=g++ -c $(FLAGS)
  Frameworks:=
endif
endif

SRCS:=Sky.o FrameController.o KeyConfigurator.o Frame.o EditorFrame.o GameFrame.o EditorChart.o EditorTap.o Effector.o JudgeEffect.o Bad.o Nice.o Singletons.o Mook.o ResourceFiler.o EditorTraceBuilder.o TraceBuilder.o ChartBuilder.o TraceRenderer.o KeyBuffer.o Pacemaker.o Alice.o Chart.o CameraHolder.o EditorNoteBuilder.o NoteBuilder.o  Note.o Tap.o Press.o Graphics.a


AlicesMusicFlight : Otoge2019_main.cpp $(SRCS)
	g++ $(FLAGS) $(GLFLAG) $^ -o AlicesMusicFlight $(SHARES) $(Frameworks)
	mv AlicesMusicFlight ..

default : main.cpp
	g++ $(FLAGS) $(STATIC_FLAGS) main.cpp $(Frameworks) -o main $(SHARES_SFML)

ShaderLoader.o : ./common/ShaderLoader.cpp ./common/ShaderLoader.hpp
	$(LIBGPP) ./common/ShaderLoader.cpp

Texture.o : Texture.cpp ./Texture.hpp
	$(LIBGPP) Texture.cpp

lodepng.o : ./lodepng/lodepng.cpp
	$(LIBGPP) ./lodepng/lodepng.cpp

Image.o : Graphics/g2d/Image.cpp
	$(LIBGPP) Graphics/g2d/Image.cpp

ImageShader.o : Graphics/g2d/ImageShader.cpp
	$(LIBGPP) Graphics/g2d/ImageShader.cpp

Panel.o : Graphics/g3d/Panel.cpp
	$(LIBGPP) Graphics/g3d/Panel.cpp

Graphics.a : FORCE
	cd Graphics; make; cp Graphics.a ..

KeyBuffer.o : KeyBuffer.cpp
	$(LIBGPP) KeyBuffer.cpp

Tester : Mook.o Graphics.a
	g++ $(FLAGS) g2d_sample.cpp Mook.o KeyBuffer.o Graphics.a -o Tester $(SHARES)

.cpp.o :
	$(LIBGPP) $(GLFLAG) $<

PlaneTest : plane_test.cpp EditorChart.o EditorTap.o Effector.o JudgeEffect.o Bad.o Nice.o Singletons.o Mook.o ResourceFiler.o EditorTraceBuilder.o TraceBuilder.o ChartBuilder.o TraceRenderer.o KeyBuffer.o Pacemaker.o Alice.o Chart.o CameraHolder.o EditorNoteBuilder.o NoteBuilder.o  Note.o Tap.o Press.o Graphics.a
	g++ $(FLAGS) $(GLFLAG) $^ -o PlaneTester $(SHARES) $(Frameworks)
	./PlaneTester

ChartEditor : ChartEditor_main.cpp $(SRCS)
	g++ $(FLAGS) $(GLFLAG) $^ -o ChartEditor $(SHARES) $(Frameworks)
	mv ChartEditor ..

clean :
	rm *.o
	cd Graphics; make clean

FORCE :

