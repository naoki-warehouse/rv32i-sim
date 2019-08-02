OBJS = decode.o \
       utils.o

main: main.c $(OBJS) utils.h 
	gcc -o main main.c $(OBJS)

.c.o:
	gcc -c $<
clean:
	rm $(OBJS) main

