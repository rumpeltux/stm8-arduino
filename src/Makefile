CC := sdcc
AR := sdar
CFLAGS := -mstm8 --std-c99 --opt-code-size -I../include
LIB := arduino.lib

all: $(LIB)

%.rel: %.o %.c
	@echo -n

$(LIB): $(patsubst %.c, %.rel, $(wildcard *.c))
	$(AR) rcs $@ $^

clean:
	rm -f *.asm *.cdb *.ihx *.lnk *.lk *.lst *.map *.mem *.rel *.rst *.sym $(LIB)
