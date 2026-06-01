# just defining variables
MCU = atmega328p
F_CPU = 16000000UL

CC = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

# i bet -0s means to optimize its size???
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -0s

TARGET = main

all: $(TARGET).hex


