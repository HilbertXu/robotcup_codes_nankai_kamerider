#!/bin/sh

echo "turtlebot connected"
gnome-terminal -x bash -c "roslaunch navigation_test navi_help.launch"

sleep 3

echo "kinect connected"
gnome-terminal -x bash -c "rosrun socket socket2topic_nd"
sleep 1

echo "gender recognizition start"
gnome-terminal -x bash -c "roslaunch speech img.launch"

sleep 1

echo "riddle.launch start"
gnome-terminal -x bash -c "rosrun imgpcl final_robot_move"

sleep 1

exit 0 
