#include <cairo.h>
#include <gtk/gtk.h>
#include <math.h>
#include <stdlib.h>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

static void do_drawing(cairo_t *, GtkWidget *);

struct {
  cairo_surface_t *image;
} glob;

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
  do_drawing(cr, widget);

  return FALSE;
}

static void do_drawing(cairo_t *cr, GtkWidget *widget) {
  GtkWidget *win = gtk_widget_get_toplevel(widget);

  gint width, height;
  gtk_window_get_size(GTK_WINDOW(win), &width, &height);
  cairo_set_source_surface(cr, glob.image, 1, 1);
  cairo_arc(cr, /*x*/ 128, /* y */ 128, /* radius */ 40, 0, 2*M_PI);
  cairo_clip(cr);
  cairo_paint(cr);
}

int main(int argc, char *argv[]) {
  GtkWidget *window;
  GtkWidget *darea;
  gint width, height;

  glob.image = cairo_image_surface_create_from_png("image.png");
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

  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), width+2, height+2);
  gtk_window_set_title(GTK_WINDOW(window), "Round image");

  gtk_widget_show_all(window);

  gtk_main();

  cairo_surface_destroy(glob.image);

  return 0;
}
