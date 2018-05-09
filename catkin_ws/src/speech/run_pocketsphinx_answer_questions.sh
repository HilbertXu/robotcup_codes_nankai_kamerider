echo "riddle.launch start"
gnome-terminal -x bash -c "pocketsphinx_continuous -inmic yes -dict /home/kamerider/catkin_ws/src/speech/voice_library/riddle/riddle.dic -lm /home/kamerider/catkin_ws/src/speech/voice_library/riddle/riddle.lm;"


sleep 1
