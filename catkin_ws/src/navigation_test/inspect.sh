#!/bin/sh

echo "inspect launch"
gnome-terminal -x bash -c "roslaunch navigation_test inspect.launch"

sleep 5

gnome-terminal -x bash -c "roslaunch speech inspect.launch"

sleep 1

exit 0
