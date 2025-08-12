CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
LD = arm-none-eabi-ld
BIN = arm-none-eabi-objcopy
STL = st-flash
CFLAGS = -mthumb -mcpu=cortex-m3

all: app.bin

ah.o: ../tools/ah.s
	$(AS) -o ah.o ../tools/ah.s

main.o: main.c
	$(CC) $(CFLAGS) -c -o main.o main.c

app.elf: ../tools/linker.ld ah.o main.o
	$(LD) -T ../tools/linker.ld -o app.elf ah.o main.o

app.bin: app.elf
	$(BIN) -O binary app.elf app.bin
clean:
	rm -f *.o *.elf *.bin


flash: app.bin
	$(STL) write app.bin 0x8000000

erase:
	$(STL) erase
