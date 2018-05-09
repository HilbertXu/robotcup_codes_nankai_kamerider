#!/bin/sh
#用于最开始的检查急停开关
echo "inspect launch"
gnome-terminal -x bash -c "roslaunch navigation_test SG.launch"

sleep 5


gnome-terminal -x bash -c "rosrun face_detection_with_aip groceries_prediction.py"

sleep 1

gnome-terminal -x bash -c "rosrun face_detection_with_aip take_photo_store"

sleep 1

gnome-terminal -x bash -c "roslaunch speech SC.launch"

sleep 1

exit 0
