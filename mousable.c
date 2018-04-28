#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <cairo.h>
#include <cairo-xlib.h>

#include "mousable.h"
#include "pointer.c"

int display_alpha_layer = 0;
int display_grid = 0;
int display_letters = 1;

void define_key(int item, int gdk_key, int x_pos, int y_pos, int mod_x_pos, int mod_y_pos, const char *key_char){
  keys[item].gdk_key = gdk_key;
  keys[item].x_pos = x_pos;
  keys[item].y_pos = y_pos;
  keys[item].mod_x_pos = mod_x_pos;
  keys[item].mod_y_pos = mod_y_pos;
  keys[item].key_char = key_char;
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

  int k;
  for(k=0; k<40; k++){
    if (event->keyval == keys[k].gdk_key){
      if (event->state & GDK_CONTROL_MASK) {
        move_pointer(hsquare - (keys[k].mod_x_pos * hrelative - hrel_offset), vsquare - (keys[k].mod_y_pos * vrelative + vrel_offset));
      }else{
        hsquare = hoffset + keys[k].x_pos * hstep;
        vsquare = voffset + keys[k].y_pos * vstep;
        move_pointer(hsquare, vsquare);
        x_position = keys[k].x_pos;
        y_position = keys[k].y_pos;
      }
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

void draw_selection(cairo_t *cr, int x_position, int y_position){
  double x = x_position * hstep;
  double y = y_position * vstep;
  cairo_set_source_surface(cr, surface, 0, 0);
  cairo_rectangle (cr, x, y, hstep, vstep);
  cairo_fill(cr);
}

void draw_one_letter(cairo_t * cr, int x_position, int y_position, const char * one_letter){
  // Display letters
  cairo_select_font_face(cr, "monospace", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
  cairo_set_font_size(cr, 60);
  cairo_move_to(cr, x_position * hstep + (hstep/2), y_position * vstep + (vstep/2));
  cairo_text_path(cr, one_letter);
  cairo_set_source_surface(cr, surface, 0, 0);
  cairo_fill_preserve(cr);
  cairo_set_source_rgba(cr, 1, 0, 0, 0.5);
  cairo_set_line_width(cr, 2);
  cairo_stroke(cr);
}

void draw_letters(cairo_t * cr) {
  int j;
  for (j=0;j<40;j++){
    draw_one_letter(cr, keys[j].x_pos, keys[j].y_pos, keys[j].key_char);
  }
}

void draw_grid(cairo_t * cr){
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

void draw_alpha_layer(cairo_t *cr){
  cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
  cairo_paint_with_alpha (cr, 0.3);
}

static void do_drawing(cairo_t *cr, GtkWidget *widget) {
  cairo_set_source_surface(cr, surface, 0, 0);
  cairo_paint(cr);

  if(display_alpha_layer){
    float found_x = (current_x_pos / hstep);
    float found_y = (current_y_pos / vstep);
    draw_alpha_layer;
    draw_selection (cr, (int)found_x, (int)found_y);
  }

  if (display_grid)
    draw_grid(cr);


  if (display_letters)
    draw_letters(cr);
}

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
  do_drawing(cr, widget);

  return FALSE;
}

static gboolean get_pointer_pos (GtkWidget *widget, GdkEventCrossing *event, gpointer   user_data){
  current_x_pos = (int) event->x;
  current_y_pos = (int) event->y;
}

void map_keys(){
  define_key(0, GDK_KEY_1, 0, 0, 5, 1, "1");
  define_key(1, GDK_KEY_2, 1, 0, 4, 1, "2");
  define_key(2, GDK_KEY_3, 2, 0, 3, 1, "3");
  define_key(3, GDK_KEY_4, 3, 0, 2, 1, "4");
  define_key(4, GDK_KEY_5, 4, 0, 1, 1, "5");
  define_key(5, GDK_KEY_q, 0, 1, 5, 0, "q");
  define_key(6, GDK_KEY_w, 1, 1, 4, 0, "w");
  define_key(7, GDK_KEY_e, 2, 1, 3, 0, "e");
  define_key(8, GDK_KEY_r, 3, 1, 2, 0, "r");
  define_key(9, GDK_KEY_t, 4, 1, 1, 0, "t");
  define_key(10, GDK_KEY_a, 0, 2, 5, -1, "a");
  define_key(11, GDK_KEY_s, 1, 2, 4, -1, "s");
  define_key(12, GDK_KEY_d, 2, 2, 3, -1, "d");
  define_key(13, GDK_KEY_f, 3, 2, 2, -1, "f");
  define_key(14, GDK_KEY_g, 4, 2, 1, -1, "g");
  define_key(15, GDK_KEY_z, 0, 3, 5, -2, "z");
  define_key(16, GDK_KEY_x, 1, 3, 4, -2, "x");
  define_key(17, GDK_KEY_c, 2, 3, 3, -2, "c");
  define_key(18, GDK_KEY_v, 3, 3, 2, -2, "v");
  define_key(19, GDK_KEY_b, 4, 3, 1, -2, "b");

  define_key(20, GDK_KEY_6, 5, 0, 0, 1, "6");
  define_key(21, GDK_KEY_7, 6, 0, -1, 1, "7");
  define_key(22, GDK_KEY_8, 7, 0, -2, 1, "8");
  define_key(23, GDK_KEY_9, 8, 0, -3, 1, "9");
  define_key(24, GDK_KEY_0, 9, 0, -4, 1, "0");
  define_key(25, GDK_KEY_y, 5, 1, 0, 0, "y");
  define_key(26, GDK_KEY_u, 6, 1, -1, 0, "u");
  define_key(27, GDK_KEY_i, 7, 1, -2, 0, "i");
  define_key(28, GDK_KEY_o, 8, 1, -3, 0, "o");
  define_key(29, GDK_KEY_p, 9, 1, -4, 0, "p");
  define_key(30, GDK_KEY_h, 5, 2, -0, -1, "h");
  define_key(31, GDK_KEY_j, 6, 2, -1, -1, "j");
  define_key(32, GDK_KEY_k, 7, 2, -2, -1, "k");
  define_key(33, GDK_KEY_l, 8, 2, -3, -1, "l");
  define_key(34, GDK_KEY_ccedilla, 9, 2, -4, -1, "ç");
  define_key(35, GDK_KEY_n, 5, 3, 0, -2, "n");
  define_key(36, GDK_KEY_m, 6, 3, -1, -2, "m");
  define_key(37, GDK_KEY_comma, 7, 3, -2, -2, ",");
  define_key(38, GDK_KEY_period, 8, 3, -3, -2, ".");
  define_key(39, GDK_KEY_semicolon, 9, 3, -4, -2, ";");
}

int main(int argc, char *argv[]) {
  Display *disp;
  int scr;

  map_keys();

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

  // Why do we need to save to a file for the surface to have the right image?
  cairo_surface_write_to_png( surface, "/dev/null");

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
  gtk_widget_add_events(window, GDK_POINTER_MOTION_MASK);
  g_signal_connect (G_OBJECT (window), "key-press-event", G_CALLBACK (on_key_press), NULL);
  g_signal_connect (G_OBJECT (window), "enter-notify-event", G_CALLBACK (get_pointer_pos), NULL);

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

  cairo_surface_destroy(surface);

  return 0;
}
