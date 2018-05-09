#!/bin/sh

echo "turtlebot connected"
gnome-terminal -x bash -c "roslaunch navigation_test gpsr_yao.launch"

sleep 5


echo "speech gpsr_yao.launch start"
gnome-terminal -x bash -c "roslaunch speech gpsr.launch"

sleep 1

echo "dictionary start"
gnome-terminal -x bash -c "pocketsphinx_continuous -inmic yes -dict ~/catkin_ws/src/speech/voice_library/gpsr/gpsr.dic -lm ~/catkin_ws/src/speech/voice_library/gpsr/gpsr.lm"

exit 0 
