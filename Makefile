all:
	gcc `pkg-config --cflags gtk+-3.0` -o build/ex ex.c `pkg-config --libs gtk+-3.0` `pkg-config --libs --cflags cairo` -lX11 -lXtst
