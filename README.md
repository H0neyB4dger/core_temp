lang=ru-RU
Приложение сделано для Linux Ubuntu 24.04.1 LTS, оконная система X11, рабочий стол GNOME. 
Приложение сделано с помощью библиотеки gtk-3, она, как правило, уже установлена на Linux. Для получения температуры используется готовая программа sensors, которую нужно установить с помощью команды:
  * sudo apt install lm-sensors
Перенесите папку core_temp в удобную для вас директорию, перейдите туда и запустите скрипт register.sh. Он создаст файлы, необходимые для работы ярлыка на рабочем столе и сам ярлык. Если рабочий стол называется не Desktop, то отредактируйте соответствующую строку в register.sh.

lang=en-US
App is build (not yet) with gtk-3, uses sensors to get temperature
commands (not finished):
  * sudo apt install lm-sensors
