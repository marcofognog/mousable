all:
	gcc -o build/mousable mousable.c `pkg-config --cflags --libs gtk+-3.0` `pkg-config --libs --cflags cairo` -lX11 -lXtst
