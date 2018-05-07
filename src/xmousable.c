#include "pointer.c"
#include "key_definitions.c"
#include "options.c"

int hsquare = 0;
int vsquare = 0;
int click_flag = 0;
int click_scroll_flag = 0;

void match_key (GdkEventKey * event){
  int hoffset = hstep/2;
  int voffset = vstep/2;

  int hrelative = hstep/COLUMNS;
  int vrelative = vstep/ROWS;
  int hrel_offset = hrelative/2;
  int vrel_offset = vrelative/2;

  int k;
  for(k=0; k<NUMBER_OF_KEYS; k++){
    if (event->keyval == keys[k].gdk_key){
      if (event->state & GDK_CONTROL_MASK) {
        move_pointer(
                     hsquare - (keys[k].mod_x_pos * hrelative - hrel_offset),
                     vsquare - (keys[k].mod_y_pos * vrelative + vrel_offset)
                     );
      }else{
        hsquare = hoffset + keys[k].x_pos * hstep;
        vsquare = voffset + keys[k].y_pos * vstep;
        move_pointer(hsquare, vsquare);
        x_position = keys[k].x_pos;
        y_position = keys[k].y_pos;
      }
    }
  }
}

gboolean on_key_press (GtkWidget *widget, GdkEventKey *event, gpointer data) {
  if (event->keyval == GDK_KEY_Escape){
    gtk_main_quit();
  }

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

  if (event->keyval == GDK_KEY_Left){
    move_pointer(current_x_pos - cursor_step, current_y_pos);
  }
  if (event->keyval == GDK_KEY_Right){
    move_pointer(current_x_pos + cursor_step, current_y_pos);
  }
  if (event->keyval == GDK_KEY_Up){
    move_pointer(current_x_pos, current_y_pos - cursor_step);
  }
  if (event->keyval == GDK_KEY_Down){
    move_pointer(current_x_pos, current_y_pos + cursor_step);
  }

  match_key(event);

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
  cairo_select_font_face(cr, "monospace", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
  cairo_set_font_size(cr, FONT_SIZE);
  cairo_move_to(cr, x_position * hstep + (hstep/2), y_position * vstep + (vstep/2));
  cairo_text_path(cr, one_letter);
  cairo_set_source_surface(cr, surface, 0, 0);
  cairo_fill_preserve(cr);
  cairo_set_source_rgba(cr, 1, 0, 0, OUTLINE_ALPHA);
  cairo_set_line_width(cr, OUTLINE_WIDTH);
  cairo_stroke(cr);
}

void draw_letters(cairo_t * cr) {
  int j;
  for (j=0;j<NUMBER_OF_KEYS;j++){
    draw_one_letter(cr, keys[j].x_pos, keys[j].y_pos, keys[j].key_char);
  }
}

void draw_grid(cairo_t * cr){
  cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
  int i;
  int j;
  for(i=1; i<COLUMNS; i++){
    cairo_move_to (cr, hstep * i, 0.0);
    cairo_line_to (cr, hstep * i, screen_height);
  }
  for(j=1; j<ROWS; j++){
    cairo_move_to (cr, 0.0, vstep * j);
    cairo_line_to (cr, screen_width, vstep * j);
  }

  cairo_set_line_width (cr, 1.0);
  cairo_stroke (cr);
}

void draw_alpha_layer(cairo_t *cr){
  cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
  cairo_paint_with_alpha (cr, ALPHA_LAYER_INDEX);
}

static void do_drawing(cairo_t *cr, GtkWidget *widget) {
  cairo_set_source_surface(cr, surface, 0, 0);
  cairo_paint(cr);

  if(display_alpha_layer){
    float found_x = (current_x_pos / hstep);
    float found_y = (current_y_pos / vstep);
    draw_alpha_layer(cr);
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

int main(int argc, char *argv[]) {
  parse_options(argc, argv);

  Display *disp;
  int scr;

  map_keys();

  disp = XOpenDisplay(":0");
  scr = DefaultScreen(disp);

  Screen *screen = ScreenOfDisplay(disp, 0);
  screen_width = screen->width;
  screen_height = screen->height;
  hstep = screen_width/COLUMNS;
  vstep = screen_height/ROWS;

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
  gtk_widget_set_size_request (GTK_WIDGET(window), screen_width, screen_height);
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
