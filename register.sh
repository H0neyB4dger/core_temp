#!/bin/bash
echo '#!/bin/bash
'"cd $PWD && ./core_temp" > ./start_core_temp.sh &&
chmod 700 ./start_core_temp.sh &&
echo "[Desktop Entry]
Encoding=UTF-8
Version=1.0
Type=Application
Terminal=false
Exec=$PWD/start_core_temp.sh
Name=core_temp
Icon=$PWD/temp.png" > ./core_temp.desktop &&
sudo cp core_temp.desktop /usr/share/applications/core_temp.desktop &&
sudo cp core_temp.desktop /home/$USER/Desktop/core_temp.desktop
