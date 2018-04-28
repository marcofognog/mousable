void click(int num){
  Display* display = XOpenDisplay(0);
  XTestFakeButtonEvent(display, num, 1, 0);
  XFlush(display);
  XCloseDisplay(display);
}

void unclick(int num){
  Display* display = XOpenDisplay(0);
  XTestFakeButtonEvent(display, num, 0, 0);
  XFlush(display);
  XCloseDisplay(display);
}

void click_left() { click(1); }

void unclick_left() { unclick(1); }

void click_scroll() { click(2); }

void unclick_scroll() { unclick(2); }

void move_pointer(int dest_x,int dest_y){
  Display* display = XOpenDisplay(0);
  XWarpPointer(display, None, root, 0, 0, 0, 0, dest_x, dest_y);
  x_cursor_pos = dest_x;
  y_cursor_pos = dest_y;
  XFlush(display);
  XCloseDisplay(display);
  current_x_pos = dest_x;
  current_y_pos = dest_y;
}

