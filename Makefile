BIN=skt-monitor
SOURCE=main.c

all: $(BIN)

$(BIN): $(SOURCE)
	gcc -o $(BIN) -g -rdynamic $(SOURCE)

clean:
	rm *.o $(BIN)
