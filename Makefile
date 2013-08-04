MMCU=atmega328p
F_CPU=16000000L
CXX=avr-g++
OBJCOPY=avr-objcopy
CXXFLAGS=-Wall -mmcu=$(MMCU) -DF_CPU=$(F_CPU) -O3

all: test.hex
	avrdude -P /dev/ttyACM0 -p m328p -c arduino -U flash:w:test.hex

%.hex:%.elf
	$(OBJCOPY) $< -O ihex $@

test.elf: test.o servo.o
	$(CXX) -o $@ $(CXXFLAGS) $^

%.o:%.cc %.h
	$(CXX) -c -o $@ $< $(CXXFLAGS)

test.o:test.cc
	$(CXX) -c -o $@ $< $(CXXFLAGS)
