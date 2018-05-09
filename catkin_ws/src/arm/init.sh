echo "riddle.launch start"
gnome-terminal -x bash -c "rostopic pub /one_controller/command std_msgs/Float64 -- 0"
sleep 0.7
echo "riddle.launch start"
gnome-terminal -x bash -c "rostopic pub /two_controller/command std_msgs/Float64 -- -0.9 "
sleep 0.7
echo "riddle.launch start"
gnome-terminal -x bash -c "rostopic pub /three_controller/command std_msgs/Float64 -- 3"
sleep 0.7
echo "riddle.launch start"
gnome-terminal -x bash -c "rostopic pub /four_controller/command std_msgs/Float64 -- 0"
sleep 0.7
echo "riddle.launch start"
gnome-terminal -x bash -c "rostopic pub /five_controller/command std_msgs/Float64 -- 0.3"
sleep 0.7

