all:
	gcc -o build/xmousable src/xmousable.c `pkg-config --cflags --libs gtk+-3.0` `pkg-config --libs --cflags cairo` -lX11 -lXtst
