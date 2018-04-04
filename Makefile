all:
	gcc `pkg-config --cflags gtk+-3.0` -o ex ex.c `pkg-config --libs gtk+-3.0` `pkg-config --libs --cflags cairo` -lX11 -lXtst
round:
	gcc `pkg-config --cflags gtk+-3.0` -o round round.c `pkg-config --libs gtk+-3.0` `pkg-config --libs --cflags cairo` -lX11 -lXtst

