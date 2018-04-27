all:
	gcc -o build/ex ex.c `pkg-config --cflags --libs gtk+-3.0` `pkg-config --libs --cflags cairo` -lX11 -lXtst
