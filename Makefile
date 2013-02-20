BIN=skt-monitor
SOURCE=main.c
#CFLAGS=-D__KERNEL__ -I/usr/src/linux-headers-3.2.0-38/include
#LDFLAGS=

all: clean $(BIN)

$(BIN): $(SOURCE)
	gcc $(CFLAGS) -o $(BIN) $(SOURCE)

clean:
	rm -f *.o $(BIN)
