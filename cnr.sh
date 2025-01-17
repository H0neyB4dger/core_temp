gcc $(pkg-config --cflags gtk4) -o core_temp core_temp.c -lgtk4-layer-shell $(pkg-config --libs gtk4) \
&& ./core_temp