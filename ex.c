#include <cairo.h>
#include <unistd.h>
#include <X11/extensions/XTest.h>
#include <gtk/gtk.h>
#include <math.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <stdio.h>
#include <cairo-xlib.h>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

GtkWidget *window;
Window root;
int hsquare = 0;
int vsquare = 0;
int click_flag = 0;
int click_scroll_flag = 0;

GtkWidget *darea;
int screen_width;
int screen_height;
int hstep;
int vstep;

int x_position;
int y_position;

int x_cursor_pos;
int y_cursor_pos;
int cursor_step = 10;

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

void click_left(){
  click(1);
}

void unclick_left(){
  unclick(1);
}

void click_scroll(){
  click(2);
}

void unclick_scroll(){
  unclick(2);
}

void move_pointer(int dest_x,int dest_y){
  Display* display = XOpenDisplay(0);
  XWarpPointer(display, None, root, 0, 0, 0, 0, dest_x, dest_y);
  x_cursor_pos = dest_x;
  y_cursor_pos = dest_y;
  XFlush(display);
  XCloseDisplay(display);
}

gboolean on_key_press (GtkWidget *widget, GdkEventKey *event, gpointer data) {

  int hoffset = hstep/2;
  int voffset = vstep/2;

  int hrelative = hstep/10;
  int vrelative = vstep/4;
  int hrel_offset = hrelative/2;
  int vrel_offset = vrelative/2;

  if (event->keyval == GDK_KEY_Escape){
    gtk_main_quit();
  }
  g_printerr("%s\n", gdk_keyval_name (event->keyval));

  if (event->keyval == GDK_KEY_Return){
    click_scroll_flag = 1;
    gtk_widget_destroy(window);
    gtk_main_quit();
  }

  if (event->keyval == GDK_KEY_space){
    click_flag = 1;
    gtk_widget_destroy(window);
    gtk_main_quit();
  }

  // left hand
  if (event->keyval == GDK_KEY_1){
    if (event->state & GDK_CONTROL_MASK) {
      move_pointer(hsquare - (5 * hrelative - hrel_offset), vsquare - (1 * vrelative + vrel_offset));
    }else{
      hsquare = hoffset+0 * hstep;
      vsquare = voffset+0 * vstep;
      move_pointer(hsquare, vsquare);
      x_position = 0;
      y_position = 0;
    }
  }
  if (event->keyval == GDK_KEY_2){
    if (event->state & GDK_CONTROL_MASK) {
      move_pointer(hsquare - (4 * hrelative - hrel_offset), vsquare - (1 * vrelative + vrel_offset));
    }else{
      hsquare = hoffset+1 * hstep;
      vsquare = voffset+0 * vstep;
      move_pointer(hsquare, vsquare);
      x_position = 1;
      y_position = 0;
    }
  }
  if (event->keyval == GDK_KEY_3){
    if (event->state & GDK_CONTROL_MASK) {
      move_pointer(hsquare - (3 * hrelative - hrel_offset), vsquare - (1 * vrelative + vrel_offset));
    }else{
      hsquare = hoffset+2 * hstep;
      vsquare = voffset+0 * vstep;
      move_pointer(hsquare, vsquare);
      x_position = 2;
      y_position = 0;
    }
  }
  if (event->keyval == GDK_KEY_4){
    if (event->state & GDK_CONTROL_MASK) {
      move_pointer(hsquare - (2 * hrelative - hrel_offset), vsquare - (1 * vrelative + vrel_offset));
    }else{
      hsquare = hoffset+3 * hstep;
      vsquare = voffset+0 * vstep;
      move_pointer(hsquare, vsquare);
      x_position = 3;
      y_position = 0;
    }
  }
  if (event->keyval == GDK_KEY_5){
    if (event->state & GDK_CONTROL_MASK) {
      move_pointer(hsquare - (1 * hrelative - hrel_offset), vsquare - (1 * vrelative + vrel_offset));
    }else{
      hsquare = hoffset+4 * hstep;
      vsquare = voffset+0 * vstep;
      move_pointer(hsquare, vsquare);
      x_position = 4;
      y_position = 0;
    }
  }

  if (event->keyval == GDK_KEY_q){
    if (event->state & GDK_CONTROL_MASK) {
      move_pointer(hsquare - (5 * hrelative - hrel_offset), vsquare - (0 * vrelative + vrel_offset));
    }else{
      hsquare = hoffset+0 * hstep;
      vsquare = voffset+1 * vstep;
      move_pointer(hsquare, vsquare);
      x_position = 0;
      y_position = 1;
    }
  }
  if (event->keyval == GDK_KEY_w){
    if (event->state & GDK_CONTROL_MASK) {
      move_pointer(hsquare - (4 * hrelative - hrel_offset), vsquare - (0 * vrelative + vrel_offset));
    }else{
      hsquare = hoffset+1 * hstep;
      vsquare = voffset+1 * vstep;
      move_pointer(hsquare, vsquare);
      x_position = 1;
      y_position = 1;
    }
  }
  if (event->keyval == GDK_KEY_e){
    if (event->state & GDK_CONTROL_MASK) {
      move_pointer(hsquare - (3 * hrelative - hrel_offset), vsquare - (0 * vrelative + vrel_offset));
    }else{
      hsquare = hoffset+2 * hstep;
      vsquare = voffset+1 * vstep;
      move_pointer(hsquare, vsquare);
      x_position = 2;
      y_position = 1;
    }
  }
  if (event->keyval == GDK_KEY_r){
    if (event->state & GDK_CONTROL_MASK) {
      move_pointer(hsquare - (2 * hrelative - hrel_offset), vsquare - (0 * vrelative + vrel_offset));
    }else{
      hsquare = hoffset+3 * hstep;
      vsquare = voffset+1 * vstep;
      move_pointer(hsquare, vsquare);
      x_position = 3;
      y_position = 1;
    }
  }
  if (event->keyval == GDK_KEY_t){
    if (event->state & GDK_CONTROL_MASK) {
      move_pointer(hsquare - (1 * hrelative - hrel_offset), vsquare - (0 * vrelative + vrel_offset));
    }else{
      hsquare = hoffset+4 * hstep;
      vsquare = voffset+1 * vstep;
      move_pointer(hsquare, vsquare);
      x_position = 4;
      y_position = 1;
    }
  }

  if (event->keyval == GDK_KEY_a){
    if (event->state & GDK_CONTROL_MASK) {
      move_pointer(hsquare - (5 * hrelative - hrel_offset), vsquare + (0 * vrelative + vrel_offset));
    }else{
      hsquare = hoffset+0 * hstep;
      vsquare = voffset+2 * vstep;
      move_pointer(hsquare, vsquare);
      x_position = 0;
      y_position = 2;
    }
  }
  if (event->keyval == GDK_KEY_s){
    if (event->state & GDK_CONTROL_MASK) {
      move_pointer(hsquare - (4 * hrelative - hrel_offset), vsquare + (0 * vrelative + vrel_offset));
    }else{
      hsquare = hoffset+1 * hstep;
      vsquare = voffset+2 * vstep;
      move_pointer(hsquare, vsquare);
      x_position = 1;
      y_position = 2;
    }
  }
  if (event->keyval == GDK_KEY_d){
    if (event->state & GDK_CONTROL_MASK) {
      move_pointer(hsquare - (3 * hrelative - hrel_offset), vsquare + (0 * vrelative + vrel_offset));
    }else{
      hsquare = hoffset+2 * hstep;
      vsquare = voffset+2 * vstep;
      move_pointer(hsquare, vsquare);
      x_position = 2;
      y_position = 2;
    }
  }
  if (event->keyval == GDK_KEY_f){
    if (event->state & GDK_CONTROL_MASK) {
      move_pointer(hsquare - (2 * hrelative - hrel_offset), vsquare + (0 * vrelative + vrel_offset));
    }else{
      hsquare = hoffset+3 * hstep;
      vsquare = voffset+2 * vstep;
      move_pointer(hsquare, vsquare);
      x_position = 3;
      y_position = 2;
    }
  }
  if (event->keyval == GDK_KEY_g){
    if (event->state & GDK_CONTROL_MASK) {
      move_pointer(hsquare - (1 * hrelative - hrel_offset), vsquare + (0 * vrelative + vrel_offset));
    }else{
      hsquare = hoffset+4 * hstep;
      vsquare = voffset+2 * vstep;
      move_pointer(hsquare, vsquare);
      x_position = 4;
      y_position = 2;
    }
  }

  if (event->keyval == GDK_KEY_z){
    if (event->state & GDK_CONTROL_MASK) {
      move_pointer(hsquare - (5 * hrelative - hrel_offset), vsquare + (1 * vrelative + vrel_offset));
    }else{
      hsquare = hoffset+0 * hstep;
      vsquare = voffset+3 * vstep;
      move_pointer(hsquare, vsquare);
      x_position = 0;
      y_position = 3;
    }
  }
  if (event->keyval == GDK_KEY_x){
    if (event->state & GDK_CONTROL_MASK) {
      move_pointer(hsquare - (4 * hrelative - hrel_offset), vsquare + (1 * vrelative + vrel_offset));
    }else{
      hsquare = hoffset+1 * hstep;
      vsquare = voffset+3 * vstep;
      move_pointer(hsquare, vsquare);
      x_position = 1;
      y_position = 3;
    }
  }
  if (event->keyval == GDK_KEY_c){
    if (event->state & GDK_CONTROL_MASK) {
      move_pointer(hsquare - (3 * hrelative - hrel_offset), vsquare + (1 * vrelative + vrel_offset));
    }else{
      hsquare = hoffset+2 * hstep;
      vsquare = voffset+3 * vstep;
      move_pointer(hsquare, vsquare);
      x_position = 2;
      y_position = 3;
    }
  }
  if (event->keyval == GDK_KEY_v){
    if (event->state & GDK_CONTROL_MASK) {
      move_pointer(hsquare - (2 * hrelative - hrel_offset), vsquare + (1 * vrelative + vrel_offset));
    }else{
      hsquare = hoffset+3 * hstep;
      vsquare = voffset+3 * vstep;
      move_pointer(hsquare, vsquare);
      x_position = 3;
      y_position = 3;
    }
  }
  if (event->keyval == GDK_KEY_b){
    if (event->state & GDK_CONTROL_MASK) {
      move_pointer(hsquare - (1 * hrelative - hrel_offset), vsquare + (1 * vrelative + vrel_offset));
    }else{
      hsquare = hoffset+4 * hstep;
      vsquare = voffset+3 * vstep;
      move_pointer(hsquare, vsquare);
      x_position = 4;
      y_position = 3;
    }
  }

  // right hand
  if (event->keyval == GDK_KEY_6){
    if (event->state & GDK_CONTROL_MASK) {
      move_pointer(hsquare + (1 * hrelative + hrel_offset), vsquare - (1 * vrelative + vrel_offset));
    }else{
      hsquare = hoffset+5 * hstep;
      vsquare = voffset+0 * vstep;
      move_pointer(hsquare, vsquare);
      x_position = 5;
      y_position = 0;
    }
  }
  if (event->keyval == GDK_KEY_7){
    if (event->state & GDK_CONTROL_MASK) {
      move_pointer(hsquare + (2 * hrelative - hrel_offset), vsquare - (1 * vrelative + vrel_offset));
    }else{
      hsquare = hoffset+6 * hstep;
      vsquare = voffset+0 * vstep;
      move_pointer(hsquare, vsquare);
      x_position = 6;
      y_position = 0;
    }
  }
  if (event->keyval == GDK_KEY_8){
    if (event->state & GDK_CONTROL_MASK) {
      move_pointer(hsquare + (3 * hrelative - hrel_offset), vsquare - (1 * vrelative + vrel_offset));
    }else{
      hsquare = hoffset+7 * hstep;
      vsquare = voffset+0 * vstep;
      move_pointer(hsquare, vsquare);
      x_position = 7;
      y_position = 0;
    }
  }
  if (event->keyval == GDK_KEY_9){
    if (event->state & GDK_CONTROL_MASK) {
      move_pointer(hsquare + (4 * hrelative - hrel_offset), vsquare - (1 * vrelative + vrel_offset));
    }else{
      hsquare = hoffset+8 * hstep;
      vsquare = voffset+0 * vstep;
      move_pointer(hsquare, vsquare);
      x_position = 8;
      y_position = 0;
    }
  }
  if (event->keyval == GDK_KEY_0){
    if (event->state & GDK_CONTROL_MASK) {
      move_pointer(hsquare + (5 * hrelative - hrel_offset), vsquare - (1 * vrelative + vrel_offset));
    }else{
      hsquare = hoffset+9 * hstep;
      vsquare = voffset+0 * vstep;
      move_pointer(hsquare, vsquare);
      x_position = 9;
      y_position = 0;
    }
  }

  if (event->keyval == GDK_KEY_y){
    if (event->state & GDK_CONTROL_MASK) {
      move_pointer(hsquare + (1 * hrelative - hrel_offset), vsquare - (0 * vrelative + vrel_offset));
    }else{
      hsquare = hoffset+5 * hstep;
      vsquare = voffset+1 * vstep;
      move_pointer(hsquare, vsquare);
      x_position = 5;
      y_position = 1;
    }
  }
  if (event->keyval == GDK_KEY_u){
    if (event->state & GDK_CONTROL_MASK) {
      move_pointer(hsquare + (2 * hrelative - hrel_offset), vsquare - (0 * vrelative + vrel_offset));
    }else{
      hsquare = hoffset+6 * hstep;
      vsquare = voffset+1 * vstep;
      move_pointer(hsquare, vsquare);
      x_position = 6;
      y_position = 1;
    }
  }
  if (event->keyval == GDK_KEY_i){
    if (event->state & GDK_CONTROL_MASK) {
      move_pointer(hsquare + (3 * hrelative - hrel_offset), vsquare - (0 * vrelative + vrel_offset));
    }else{
      hsquare = hoffset+7 * hstep;
      vsquare = voffset+1 * vstep;
      move_pointer(hsquare, vsquare);
      x_position = 7;
      y_position = 1;
    }
  }
  if (event->keyval == GDK_KEY_o){
    if (event->state & GDK_CONTROL_MASK) {
      move_pointer(hsquare + (4 * hrelative - hrel_offset), vsquare - (0 * vrelative + vrel_offset));
    }else{
      hsquare = hoffset+8 * hstep;
      vsquare = voffset+1 * vstep;
      move_pointer(hsquare, vsquare);
      x_position = 8;
      y_position = 1;
    }
  }
  if (event->keyval == GDK_KEY_p){
    if (event->state & GDK_CONTROL_MASK) {
      move_pointer(hsquare + (5 * hrelative - hrel_offset), vsquare - (0 * vrelative + vrel_offset));
    }else{
      hsquare = hoffset+9 * hstep;
      vsquare = voffset+1 * vstep;
      move_pointer(hsquare, vsquare);
      x_position = 9;
      y_position = 1;
    }
  }

  if (event->keyval == GDK_KEY_h){
    if (event->state & GDK_CONTROL_MASK) {
      move_pointer(hsquare + (1 * hrelative - hrel_offset), vsquare + (0 * vrelative + vrel_offset));
    }else{
      hsquare = hoffset+5 * hstep;
      vsquare = voffset+2 * vstep;
      move_pointer(hsquare, vsquare);
      x_position = 5;
      y_position = 2;
    }
  }
  if (event->keyval == GDK_KEY_j){
    if (event->state & GDK_CONTROL_MASK) {
      move_pointer(hsquare + (2 * hrelative - hrel_offset), vsquare + (0 * vrelative + vrel_offset));
    }else{
      hsquare = hoffset+6 * hstep;
      vsquare = voffset+2 * vstep;
      move_pointer(hsquare, vsquare);
      x_position = 6;
      y_position = 2;
    }
  }
  if (event->keyval == GDK_KEY_k){
    if (event->state & GDK_CONTROL_MASK) {
      move_pointer(hsquare + (3 * hrelative - hrel_offset), vsquare + (0 * vrelative + vrel_offset));
    }else{
      hsquare = hoffset+7 * hstep;
      vsquare = voffset+2 * vstep;
      move_pointer(hsquare, vsquare);
      x_position = 7;
      y_position = 2;
    }
  }
  if (event->keyval == GDK_KEY_l){
    if (event->state & GDK_CONTROL_MASK) {
      move_pointer(hsquare + (4 * hrelative - hrel_offset), vsquare + (0 * vrelative + vrel_offset));
    }else{
      hsquare = hoffset+8 * hstep;
      vsquare = voffset+2 * vstep;
      move_pointer(hsquare, vsquare);
      x_position = 8;
      y_position = 2;
    }
  }
  if (event->keyval == GDK_KEY_ccedilla){
    if (event->state & GDK_CONTROL_MASK) {
      move_pointer(hsquare + (5 * hrelative - hrel_offset), vsquare + (0 * vrelative + vrel_offset));
    }else{
      hsquare = hoffset+9 * hstep;
      vsquare = voffset+2 * vstep;
      move_pointer(hsquare, vsquare);
      x_position = 9;
      y_position = 2;
    }
  }

  if (event->keyval == GDK_KEY_n){
    if (event->state & GDK_CONTROL_MASK) {
      move_pointer(hsquare + (1 * hrelative - hrel_offset), vsquare + (1 * vrelative + vrel_offset));
    }else{
      hsquare = hoffset+5 * hstep;
      vsquare = voffset+3 * vstep;
      move_pointer(hsquare, vsquare);
      x_position = 5;
      y_position = 3;
    }
  }
  if (event->keyval == GDK_KEY_m){
    if (event->state & GDK_CONTROL_MASK) {
      move_pointer(hsquare + (2 * hrelative - hrel_offset), vsquare + (1 * vrelative + vrel_offset));
    }else{
      hsquare = hoffset+6 * hstep;
      vsquare = voffset+3 * vstep;
      move_pointer(hsquare, vsquare);
      x_position = 6;
      y_position = 3;
    }
  }
  if (event->keyval == GDK_KEY_comma){
    if (event->state & GDK_CONTROL_MASK) {
      move_pointer(hsquare + (3 * hrelative - hrel_offset), vsquare + (1 * vrelative + vrel_offset));
    }else{
      hsquare = hoffset+7 * hstep;
      vsquare = voffset+3 * vstep;
      move_pointer(hsquare, vsquare);
      x_position = 7;
      y_position = 3;
    }
  }
  if (event->keyval == GDK_KEY_period){
    if (event->state & GDK_CONTROL_MASK) {
      move_pointer(hsquare + (4 * hrelative - hrel_offset), vsquare + (1 * vrelative + vrel_offset));
    }else{
      hsquare = hoffset+8 * hstep;
      vsquare = voffset+3 * vstep;
      move_pointer(hsquare, vsquare);
      x_position = 8;
      y_position = 3;
    }
  }
  if (event->keyval == GDK_KEY_semicolon){
    if (event->state & GDK_CONTROL_MASK) {
      move_pointer(hsquare + (5 * hrelative - hrel_offset), vsquare + (1 * vrelative + vrel_offset));
    }else{
      hsquare = hoffset+9 * hstep;
      vsquare = voffset+3 * vstep;
      move_pointer(hsquare, vsquare);
      x_position = 9;
      y_position = 3;
    }
  }
  if (event->keyval == GDK_KEY_Left){
    move_pointer(x_cursor_pos - cursor_step, y_cursor_pos);
  }
  if (event->keyval == GDK_KEY_Right){
    move_pointer(x_cursor_pos + cursor_step, y_cursor_pos);
  }
  if (event->keyval == GDK_KEY_Up){
    move_pointer(x_cursor_pos, y_cursor_pos - cursor_step);
  }
  if (event->keyval == GDK_KEY_Down){
    move_pointer(x_cursor_pos, y_cursor_pos + cursor_step);
  }

  // redraw
  gtk_widget_queue_draw(window);
}

static void do_drawing(cairo_t *, GtkWidget *);

struct {
  cairo_surface_t *image;
} glob;

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
  do_drawing(cr, widget);

  return FALSE;
}

void draw_selection(cairo_t *cr, int x_position, int y_position){
  double x = x_position * hstep;
  double y = y_position * vstep;
  cairo_set_source_surface(cr, glob.image, 0, 0);
  cairo_rectangle (cr, x, y, hstep, vstep);
  cairo_fill(cr);

  //draw grid
  cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
  int i;
  int j;
  for(i=1; i<10; i++){
    cairo_move_to (cr, hstep * i, 0.0);
    cairo_line_to (cr, hstep * i, screen_height);
  }
  for(j=1; j<10; j++){
    cairo_move_to (cr, 0.0, vstep * j);
    cairo_line_to (cr, screen_width, vstep * j);
  }

  cairo_set_line_width (cr, 1.0);
  cairo_stroke (cr);
}

static void do_drawing(cairo_t *cr, GtkWidget *widget) {
  GtkWidget *win = gtk_widget_get_toplevel(widget);

  gint width, height;
  gtk_window_get_size(GTK_WINDOW(win), &width, &height);
  cairo_set_source_surface(cr, glob.image, 0, 0);
  cairo_paint(cr);
  cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
  cairo_paint_with_alpha (cr, 0.3);
  draw_selection (cr, x_position, y_position);
}

int main(int argc, char *argv[]) {
  gint width, height;

  Display *disp;
  cairo_surface_t *surface;
  int scr;

  disp = XOpenDisplay(":0");
  scr = DefaultScreen(disp);

  Screen *screen = ScreenOfDisplay(disp, 0);
  screen_width = screen->width;
  screen_height = screen->height;
  hstep = screen_width/10;
  vstep = screen_height/4;

  root = DefaultRootWindow(disp);
  surface = cairo_xlib_surface_create(disp, root, DefaultVisual(disp, scr),
                                      DisplayWidth(disp, scr),
                                      DisplayHeight(disp, scr));
  cairo_surface_write_to_png( surface, "opa.png");

  glob.image = surface;
  width = cairo_image_surface_get_width(glob.image);
  height = cairo_image_surface_get_height(glob.image);

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  darea = gtk_drawing_area_new();
  gtk_container_add(GTK_CONTAINER (window), darea);

  g_signal_connect(G_OBJECT(darea), "draw",
                   G_CALLBACK(on_draw_event), NULL);
  g_signal_connect(G_OBJECT(window), "destroy",
                   G_CALLBACK(gtk_main_quit), NULL);

  gtk_window_set_accept_focus (GTK_WINDOW(window), TRUE);
  gtk_window_set_decorated (GTK_WINDOW(window), FALSE);
  gtk_window_set_keep_above(GTK_WINDOW(window), TRUE);
  gtk_widget_set_size_request (GTK_WIDGET(window), 1366, 768);
  gtk_window_fullscreen (GTK_WINDOW(window));

  gtk_widget_add_events(window, GDK_KEY_PRESS_MASK);
  g_signal_connect (G_OBJECT (window), "key-press-event", G_CALLBACK (on_key_press), NULL);

  gtk_widget_show_all(window);

  gtk_main();

  if (click_flag){
    click_left();
    unclick_left();
  }

  if (click_scroll_flag){
    click_scroll();
    unclick_scroll();
  }

  cairo_surface_destroy(glob.image);

  return 0;
}
