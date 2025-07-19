CC = g++
ARCH = 32
SRC = ./src/SOElib.cpp
TARGET = SOElibX$(ARCH)
CFLAGS = -Wall -m$(ARCH)


$(shell mkdir -p bin)


dynamic :
	$(CC) $(CFLAGS) -shared -o ./bin/$(TARGET).dll $(SRC)

static :
	$(CC) $(CFLAGS) -c $(SRC) -o ./bin/$(TARGET)
	ar rcs ./bin/$(TARGET).a ./bin/$(TARGET)

clean :
	rm -f ./bin/*