#!/bin/sh
#用于最开始的检查急停开关
echo "inspect launch"
gnome-terminal -x bash -c "roslaunch navigation_test inspect.launch"

sleep 5

gnome-terminal -x bash -c "roslaunch speech inspect.launch"

sleep 1

exit 0
