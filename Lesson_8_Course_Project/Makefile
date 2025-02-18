#Cборка программ с зависимостями
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic -lm

all: program    #Цель по умолчанию

program: main.o functions.o root.o integral.o tests.o
	$(CC) $(CFLAGS) -o program main.o functions.o root.o integral.o tests.o -lm

# Правила для объектных файлов
main.o: main.c functions.h root.h integral.h tests.h
	$(CC) $(CFLAGS) -c main.c

functions.o: functions.c functions.h
	$(CC) $(CFLAGS) -c functions.c

root.o: root.c root.h
	$(CC) $(CFLAGS) -c root.c

integral.o: integral.c integral.h
	$(CC) $(CFLAGS) -c integral.c

tests.o: tests.c tests.h functions.h root.h integral.h
	$(CC) $(CFLAGS) -c tests.c

clean:
	rm -f *.o program  #Очистка проекта
