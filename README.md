lang=ru-RU
Приложение сделано для Linux Ubuntu 24.04.1 LTS, оконная система X11, рабочий стол GNOME. 
Приложение сделано с помощью библиотеки gtk-3, она, как правило, уже установлена на Linux. Программа xrandr, которая используется для получения размеров экрана, тоже, как правило, установлена, если у вас X11. Для получения температуры используется программа sensors, которую нужно установить с помощью команды:
  * sudo apt install lm-sensors
Перенесите директорию core_temp в удобную для вас директорию, перейдите туда и запустите скрипт register.sh. Он создаст файлы, необходимые для работы ярлыка на рабочем столе и сам ярлык. Если рабочий стол называется не Desktop, то отредактируйте соответствующую строку в register.sh. После этого на ярлыке нужно щёлкнуть правой кнопкой и нажать "Разрешить запуск". После этого ярлык должен работать (но это не точно). По желанию можно добавить в автозапуск. В общем-то, всё.

lang=en-US
The application is made for Linux Ubuntu 24.04.1 LTS, X11 window system, GNOME desktop. 
The application is made using the gtk-3 library, which is usually already installed on Linux. The xrandr program, which is used to get screen sizes, is also usually installed if you have X11. To get the temperature, the sensors program is used, which must be installed using the command:
  * sudo apt install lm-sensors
Move the core_temp directory to a directory convenient for you, cd there and run the script register.sh. It will create the files necessary for the desktop shortcut to work and the shortcut itself. If the desktop is not called Desktop, then edit the corresponding line in register.sh. After that, right-click on the shortcut and click "Allow launch". After that, the shortcut should work (I hope). Optionally, you can add it to autorun. In general, that's it.
