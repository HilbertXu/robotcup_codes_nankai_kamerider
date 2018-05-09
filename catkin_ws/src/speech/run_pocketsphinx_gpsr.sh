echo "riddle.launch start"
gnome-terminal -x bash -c "pocketsphinx_continuous -inmic yes -dict /home/kamerider/catkin_ws/src/speech/voice_library/gpsr/gpsr.dic -lm /home/kamerider/catkin_ws/src/speech/voice_library/gpsr/gpsr.lm;"

sleep 1
