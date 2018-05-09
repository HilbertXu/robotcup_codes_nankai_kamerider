#!/bin/sh
#运行help_me_carry项目
echo "gender recognizition start"
gnome-terminal -x bash -c "roslaunch navigation_test navi_help.launch"

sleep 10

gnome-terminal -x bash -c "roslaunch speech help_me_carry.launch"


sleep 1

gnome-terminal -x bash -c " pocketsphinx_continuous -inmic yes -dict ~/catkin_ws/src/speech/voice_library/help_me_carry/help_me_carry.dic -lm ~/catkin_ws/src/speech/voice_library/help_me_carry/help_me_carry.lm"

sleep 1

exit 0
