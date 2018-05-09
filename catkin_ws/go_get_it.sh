#!/bin/sh
#运行go_get_it项目
echo "gender recognizition start"
gnome-terminal -x bash -c "roslaunch navigation_test go_get_it.launch"

sleep 10

gnome-terminal -x bash -c "roslaunch speech go_get_it.launch"


sleep 1



gnome-terminal -x bash -c " pocketsphinx_continuous -inmic yes -dict ~/catkin_ws/src/speech/voice_library/go_get_it/go_get_it.dic -lm ~/catkin_ws/src/speech/voice_library/go_get_it/go_get_it.lm"

sleep 1

exit 0
