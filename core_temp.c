#include <gtk/gtk.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#define TEMP_SIZE 128
#define SCREEN_WIDTH 1895 //хз почему так, впрочем это относится ко всей программе
#define RIGHT_MOVE_CAP 25
#define TEMP_FORMAT "%.1lf\u00b0C"
#define TEMP_FILE "./temperature.txt"
#define TEMP_SCRIPT "./temp.sh"
#define MOVE_SCRIPT "./move.sh"


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

gboolean tick_callback(GtkWidget *label, GdkFrameClock *frame_clock, gpointer user_data)
{
  if (LAST_TIME == 0) {
    LAST_TIME = time(NULL);
  }
  else if (time(NULL) - LAST_TIME >= 1) {
    char temperature[TEMP_SIZE];
    snprintf(temperature, TEMP_SIZE, TEMP_FORMAT, get_temp());
    gtk_label_set_label(GTK_LABEL(label), temperature);
    LAST_TIME = time(NULL);
  }
  return G_SOURCE_CONTINUE;
}

void activate(GtkApplication *app, gpointer user_data)
{
  GtkWidget *window;
  GtkWidget *label;
  char temperature[TEMP_SIZE];
  char command[TEMP_SIZE];
  int x = 100, y = 100;
  int move_x = SCREEN_WIDTH - x + RIGHT_MOVE_CAP, move_y = 0;

  window = gtk_application_window_new(app);
  gtk_window_set_default_size(GTK_WINDOW(window), x, y);
  gtk_window_set_decorated(GTK_WINDOW(window), false);
  
  snprintf(temperature, TEMP_SIZE, TEMP_FORMAT, get_temp());
  label = gtk_label_new(temperature);
  gtk_widget_add_tick_callback(label, tick_callback, NULL, NULL);
  gtk_window_set_child(GTK_WINDOW(window), label);

  gtk_window_present(GTK_WINDOW(window));

  snprintf(command, TEMP_SIZE, "%s %d %d", MOVE_SCRIPT, move_x, move_y);
  system(command);
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