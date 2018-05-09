echo "riddle.launch start"
gnome-terminal -x bash -c "pocketsphinx_continuous -inmic yes -dict /home/kamerider/catkin_ws/src/speech/voice_library/inspect/1131.dic -lm /home/kamerider/catkin_ws/src/speech/voice_library/inspect/1131.lm;"

sleep 1
