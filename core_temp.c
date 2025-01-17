#include <gtk4-layer-shell/gtk4-layer-shell.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#define TEMP_SIZE 128
#define WINDOW_X  140
#define WINDOW_Y   60
#define SCREEN_WIDTH 1895 //хз почему так, впрочем это относится ко всей программе
#define RIGHT_MOVE_CAP 25
#define WIN_MOVE_X (SCREEN_WIDTH - WINDOW_X - 5 + RIGHT_MOVE_CAP)
#define WIN_MOVE_Y 80
#define TEMP_FORMAT "%.1lf\u00b0C"
#define TEMP_FILE "./temperature.txt"
#define TEMP_SCRIPT "./temp.sh"
#define MOVE_SCRIPT "./move.sh"
#define STYLE_FILE "./style.css"


time_t LAST_TIME = 0;


double get_temp(void) 
{
  FILE *temperature_file;
  double temperature;
  double dec_part;

  system(TEMP_SCRIPT " > " TEMP_FILE);
  temperature_file = fopen(TEMP_FILE, "r");
  fscanf(temperature_file, "%lf.%lf", &temperature, &dec_part);
  temperature += dec_part / 10;
  fclose(temperature_file);
  return temperature;
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
    char command[TEMP_SIZE];

    LAST_TIME = time(NULL);
    snprintf(command, TEMP_SIZE, "%s %d %d", MOVE_SCRIPT, WIN_MOVE_X, WIN_MOVE_Y);
    system(command);
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
  GtkWindow *window;
  GtkWidget *label;  
  GtkCssProvider *provider;
  char temperature[TEMP_SIZE];

  window = GTK_WINDOW(gtk_application_window_new(app));
  gtk_layer_init_for_window(window);
  gtk_layer_set_layer(window, GTK_LAYER_SHELL_LAYER_TOP);
  gtk_layer_auto_exclusive_zone_enable(window);
  
  gtk_window_set_default_size(window, WINDOW_X, WINDOW_Y);
  gtk_window_set_decorated(window, false);

  provider = gtk_css_provider_new();
  gtk_css_provider_load_from_path(provider, STYLE_FILE);
  gtk_style_context_add_provider_for_display(gdk_display_get_default(), GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

  snprintf(temperature, TEMP_SIZE, TEMP_FORMAT, get_temp());
  replace_comma_with_point(temperature);
  label = gtk_label_new(temperature);
  gtk_widget_add_css_class(label, "label");
  gtk_widget_add_tick_callback(label, tick_callback, NULL, NULL);
  gtk_window_set_child(window, label);

  gtk_window_present(window);

  g_object_unref(provider);
}

int main(int argc, char **argv)
{
  GtkApplication *app;
  double temperature;
  int status;

  app = gtk_application_new("org.gtk.core_temp", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}