CROSS_COMPILE ?= /usr/local/oecore-x86_64/sysroots/x86_64-angstromsdk-linux/usr/bin/arm-angstrom-linux-gnueabi/arm-angstrom-linux-gnueabi-
CC = $(CROSS_COMPILE)gcc -mfpu=neon -mfloat-abi=hard --sysroot=/usr/local/oecore-x86_64/sysroots/armv7at2hf-neon-angstrom-linux-gnueabi


all: main.c
	${CC} -g -o main main.c
	
#main.o: main.c 
#	${CC} -g -c main.c 

#all: gpio_output.o getkey.o
#	$(CC) -g -o gpio_output gpio_output.o getkey.o

#gpio_output.o: gpio_output.c pathmacros.h
#	$(CC) -g -c gpio_output.c

#getkey.o: getkey.c getkey.h
#	$(CC) -g -c getkey.c

clean:
	rm -rf *.o
	rm -rf gpio_output