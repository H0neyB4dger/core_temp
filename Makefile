core_temp: core_temp.c
					 gcc `pkg-config --cflags gtk+-3.0` -o core_temp core_temp.c `pkg-config --libs gtk+-3.0` -lm