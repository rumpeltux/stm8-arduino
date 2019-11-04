all:
	make -C src
	make -C example

flash: all
	make -C example flash

clean:
	make -C src clean
	make -C example clean
