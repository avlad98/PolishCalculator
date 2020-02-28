FLAGS  = -Wall -Wextra -g
TARGET = tema3
INPUT  = ./in/test2.in
OUTPUT = ./out.txt

build:	tema3.c lista.c arbore.c evaluari.c
	gcc $(FLAGS) $^ -o $(TARGET) -lm

run:	tema3
	./tema3 $(INPUT) $(OUTPUT)

clean:
	rm -rf $(TARGET)
