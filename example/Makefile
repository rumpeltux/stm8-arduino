CC := sdcc
AR := sdar
LIBDIR := ../src
CFLAGS := -mstm8 --std-c99 --opt-code-size -I../include -L$(LIBDIR)
STM8FLASH := stm8flash -c espstlink -p stm8s103?3
TARGET := demo

all: $(TARGET).ihx

%.rel: %.o %.c
	@echo -n

$(TARGET).ihx: $(TARGET).rel $(LIBDIR)/arduino.lib
	$(CC) $(CFLAGS) -larduino $<

flash: $(TARGET).ihx
	$(STM8FLASH) -w $<

clean:
	rm -f *.asm *.cdb *.ihx *.lnk *.lk *.lst *.map *.mem *.rel *.rst *.sym
