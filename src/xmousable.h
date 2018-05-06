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
int cursor_step;

float current_x_pos;
float current_y_pos;

cairo_surface_t *surface;

typedef struct keymap {
  int gdk_key;
  int x_pos;
  int y_pos;
  int mod_x_pos;
  int mod_y_pos;
  const char *key_char;
} keyMap;

#define ROWS 4
#define COLUMNS 10
#define NUMBER_OF_KEYS 40
keyMap keys [NUMBER_OF_KEYS];

#define FONT_SIZE 60
#define OUTLINE_ALPHA 0.5
#define OUTLINE_WIDTH 2
#define ALPHA_LAYER_INDEX 0.3
