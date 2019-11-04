# STM8-Arduino

Low-overhead Arduino compatibility library for STM8 microcontrollers.

This project tries to lower the bar when writing code for STM8. It’s for you if:

* you are familiar with Arduino APIs and don't want to bother reading
  the STM8 datasheet
* you want to port an existing Arduino library to work with STM8

NOTE: sdcc doesn’t support C++ and there are a few constraints, so the APIs
don't match 100%.

## Supported Features

* GPIO: `digitalRead`, `digitalWrite`, `pinMode`, `attachInterrupt`
* UART: serial output, use `puts`, `putchar` or even `printf` natively
* ADC: `analogRead`
* SPI: `spi_transfer`

## Usage

0. `sudo apt-get install sdcc make`
1. Put your code into `example/demo.c`
2. Adjust `example/Makefile` with your `stm8flash` command. I recommend to use
   [stm8flash](https://github.com/vdudouyt/stm8flash) with the ESP8266-based
   [esp-stlink](https://github.com/rumpeltux/esp-stlink).
3. Run: `make flash`

## Bug reports

Please file bugs if you run into any issues.
