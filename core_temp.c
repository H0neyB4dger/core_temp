#include <gtk/gtk.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#define TEMP_SIZE       128
#define WINDOW_X        140
#define WINDOW_Y         40
#define SCREEN_WIDTH   1895 //хз почему так, впрочем это относится ко всей прогр     амме
#define SCREEN_HEIGHT  1040
#define WIN_MOVE_X SCREEN_WIDTH
#define WIN_MOVE_Y SCREEN_HEIGHT
#define TEMP_FORMAT "%.1lf\u00b0C"
#define PATH "./"
#define STYLE_FILE "style.css"
#define ICON_FILE "temp.ico"


time_t LAST_TIME = 0;


double get_temp(void)
{
  FILE *file = popen("sensors", "r");
  double temp_whole, temp_frac;
  int buf_len = 1024;
  char buf[buf_len], *ptr_start, *ptr_frac, *ptr_end;
  char needle[] = "Tctl:";
  size_t needle_len = strlen(needle);
  fread(buf, sizeof(char), buf_len, file);
  pclose(file);
  ptr_start = strstr(buf, needle);
  ptr_start = strchr(ptr_start + needle_len, '+') + 1;
  ptr_frac = strchr(ptr_start, '.') + 1;
  ptr_end = strstr(ptr_frac, "°");
  temp_whole = (double) atoi(ptr_start);
  temp_frac = (double) atoi(ptr_frac) / pow(10, ptr_end - ptr_frac);
  return temp_whole + temp_frac;
}

void replace_comma_with_point(char *str) {
  while (*str) {
    if (*str == ',')
      *str = '.';
    str++;
  }
}

gboolean tick_callback(GtkWidget *label, GdkFrameClock *frame_clock, gpointer user_data)
{
  if (LAST_TIME == 0) {
    LAST_TIME = time(NULL);
  }
  else if (time(NULL) - LAST_TIME >= 1) {
    char temperature[TEMP_SIZE];
    snprintf(temperature, TEMP_SIZE, TEMP_FORMAT, get_temp());
    replace_comma_with_point(temperature);
    gtk_label_set_label(GTK_LABEL(label), temperature);
    LAST_TIME = time(NULL);
  }
  return G_SOURCE_CONTINUE;
}

void activate(GtkApplication *app, gpointer user_data)
{
  GtkWidget           *window;
  GtkWidget            *label;  
  GtkCssProvider    *provider;
  GdkScreen           *screen;
  GdkVisual           *visual;
  GdkPixbuf           *pixbuf;
  char temperature[TEMP_SIZE];

  window = gtk_application_window_new(app);
  gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_X, WINDOW_Y);
  gtk_window_set_decorated(GTK_WINDOW(window), false);
  pixbuf = gdk_pixbuf_new_from_file(PATH ICON_FILE, NULL);
  gtk_window_set_icon(GTK_WINDOW(window), pixbuf);

  screen = gdk_screen_get_default();
  visual = gdk_screen_get_rgba_visual(screen);
  gtk_widget_set_visual(window, visual);
  gtk_window_set_keep_above(GTK_WINDOW(window), true);
  gtk_window_move(GTK_WINDOW(window), WIN_MOVE_X, WIN_MOVE_Y);

  provider = gtk_css_provider_new();
  gtk_css_provider_load_from_path(provider, PATH STYLE_FILE, NULL);
  gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

  snprintf(temperature, TEMP_SIZE, TEMP_FORMAT, get_temp());
  replace_comma_with_point(temperature);

  label = gtk_label_new(temperature);
  gtk_widget_add_tick_callback(label, tick_callback, window, NULL);
  gtk_container_add(GTK_CONTAINER(window), label);

  gtk_widget_show_all(window);

  cairo_region_t *region = cairo_region_create();
  gdk_window_input_shape_combine_region(gtk_widget_get_window(window), region, 0, 0);

  cairo_region_destroy(region);
  g_object_unref(provider);
}

int main(int argc, char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new("org.gtk.core_temp", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  
  g_object_unref(app);

  return status;
}

// TODO:
// узнать размер экрана и определить move_x, move_y
// таймер уже встроенный в callback вроде есть
// почистить include
