CC=gcc
CFLAGS=`pkg-config --cflags --libs gtk+-3.0` `pkg-config --libs --cflags cairo` -lX11 -lXtst
OBJ= build/key_definitions.o build/options.o build/pointer.o build/xmousable.o

xmousable:  $(OBJ)
	$(CC) -o build/xmousable build/xmousable.o $(CFLAGS)

build/%.o: src/%.c
	$(CC) -o $@ $< $(CFLAGS) -c
