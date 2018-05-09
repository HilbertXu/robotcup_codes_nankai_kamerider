#!/bin/sh

echo "turtlebot connected"
gnome-terminal -x bash -c "roslaunch turtlebot_bringup minimal.launch"

sleep 1

echo "kinect connected"
#gnome-terminal -x bash -c "roslaunch freenect_launch doublekinect_test.launch"
gnome-terminal -x bash -c "roslaunch freenect_launch freenect.launch"
sleep 1

echo "waiting for signal"
gnome-terminal -x bash -c "rosrun face_detection_with_aip face_detection "

sleep 1

echo "gender detection start"
gnome-terminal -x bash -c "rosrun face_detection_with_aip face_aip.py"

sleep 1

echo "riddle.launch start"
gnome-terminal -x bash -c "roslaunch speech SPR.launch;"

sleep 1

echo "dictionary start"
gnome-terminal -x bash -c " pocketsphinx_continuous -inmic yes -dict ~/catkin_ws/src/speech/voice_library/riddle/riddle.dic -lm ~/catkin_ws/src/speech/voice_library/riddle/riddle.lm"

exit 0 
