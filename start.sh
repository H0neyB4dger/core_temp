#!/bin/bash
PID=$(pidof core_temp)
if [ $PID ]; then
  echo core_temp is already launched
else
  cd ~/core_temp && ./core_temp
fi
