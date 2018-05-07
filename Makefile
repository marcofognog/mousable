CC=gcc
CFLAGS=`pkg-config --cflags --libs gtk+-3.0` `pkg-config --libs --cflags cairo` -lX11 -lXtst

xmousable:
	$(CC) -o build/xmousable src/xmousable.c $(CFLAGS)
