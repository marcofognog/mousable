void define_key(int item, int gdk_key, int x_pos, int y_pos, int mod_x_pos, int mod_y_pos, const char *key_char){
  keys[item].gdk_key = gdk_key;
  keys[item].x_pos = x_pos;
  keys[item].y_pos = y_pos;
  keys[item].mod_x_pos = mod_x_pos;
  keys[item].mod_y_pos = mod_y_pos;
  keys[item].key_char = key_char;
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
