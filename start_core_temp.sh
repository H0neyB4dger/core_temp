#!/bin/bash
PID=$(pidof core_temp)
if [ $PID ]; then
  echo core_temp is already launched
else
  cd /home/madara/core_temp && ./core_temp
fi
