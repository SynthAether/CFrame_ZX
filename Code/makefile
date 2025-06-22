
IDIR =../include
CC=zcc
CFLAGS=+zxn -vn -c -SO3 -compiler sdcc -clib=sdcc_iy -pragma-include:zpragma.inc -clib=sdcc_iy --max-allocs-per-node30000
ODIR=obj
LDIR =../lib
LIBS=-lm




OBJS = main.o Kernel.o IRQs.o data.o


hello_world.nex: $(OBJS) 
	$(CC) +zxn -vn -m -clib=sdcc_iy -pragma-include:zpragma.inc -startup=1 $(OBJS) -o hello_world.nex -create-app -subtype=nex


# Main program at $8000
main.o: 	main.c FrameWork.h Kernel.h
		$(CC) $(CFLAGS) main.o main.c
data.o: 	data.c FrameWork.h Kernel.h
		$(CC) $(CFLAGS) data.o data.c


# Kernel section
kernel.o: Kernel.asm includes.inc
	$(CC) $(CFLAGS) --codesegPAGE_02_KERNEL_CODE --constsegPAGE_02_KERNEL_CODE -o Kernel.o Kernel.asm
irqs.o: IRQs.asm includes.inc
	$(CC) $(CFLAGS) --codesegPAGE_02_KERNEL_IRQ --constsegPAGE_02_KERNEL_IRQ -o IRQs.o IRQs.asm



clean:
	del -f *.o 
	del -f *.lis
	del -f *.bin
	del -f *.nex
	del -f *.map


