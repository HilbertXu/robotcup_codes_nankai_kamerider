#!/bin/sh

echo "gender recognizition start"
gnome-terminal -x bash -c "roslaunch navigation_test restaurant.launch"

sleep 5

gnome-terminal -x bash -c "roslaunch speech restaurant.launch"


sleep 1
echo "gender recognizition start"
gnome-terminal -x bash -c "rosrun imgpcl restaurant_wave "

sleep 1
echo "gender recognizition start"
gnome-terminal -x bash -c "rosrun imgpcl restaurant_bardetect  "

sleep 1
echo "gender recognizition start"
gnome-terminal -x bash -c "pocketsphinx_continuous -inmic yes -dict /home/kamerider/catkin_ws/src/speech/voice_library/restaurant/restaurant.dic  -lm /home/kamerider/catkin_ws/src/speech/voice_library/restaurant/restaurant.lm "
sleep 1

exit 0
