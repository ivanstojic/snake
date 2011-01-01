INPUTSOURCE=input-keyboard.o
OBJ=snake.o drawing.o motion.o $(INPUTSOURCE) animation.o collision.o food.o game-odd.o game-even.o level.o
EXE=snake.exe
LIBS=-lalleg

default: snake.exe

clean:
	rm -f *.o
	rm -f snake.exe

snake.exe: $(OBJ)
	gcc $(OBJ) -o $(EXE) $(LIBS)

*.o: *.h

