#!/bin/sh

echo "gender recognizition start"
gnome-terminal -x bash -c "roslaunch navigation_test navi_help.launch"

sleep 10

gnome-terminal -x bash -c "roslaunch speech help_me_carry.launch"


sleep 1


exit 0
