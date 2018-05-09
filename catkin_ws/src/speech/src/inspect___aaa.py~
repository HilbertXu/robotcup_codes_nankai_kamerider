#!/usr/bin/env python


"""
    navigation.py - Say back what is heard by the pocketsphinx recognizer.
"""

import roslib; roslib.load_manifest('speech')
import rospy
from std_msgs.msg import String
from std_msgs.msg import Int8
import os

from sound_play.libsoundplay import SoundClient

class help_me_carry:

	def __init__(self):

		rospy.on_shutdown(self.cleanup)
		self.voice = rospy.get_param("~voice", "voice_cmu_us_clb_arctic_clunits")
		self.wavepath = rospy.get_param("~wavepath", "")
		self.state="true"
		self.soundhandle=SoundClient()
		rospy.sleep(1)
		self.soundhandle.stopAll()
		rospy.sleep(1)
		self.soundhandle.say("ready",self.voice)
		rospy.sleep(1.1)
		self.pub = rospy.Publisher('/ifFollowme', String, queue_size=15)
		#发布器这里加
		self.loc_pub = rospy.Publisher('/voice2bring', String, queue_size=15)
		self.srt_guide = rospy.Publisher('/voice2guide', String, queue_size=15)
		self.inspect = rospy.Publisher('go_out', String, queue_size=15)


		rospy.Subscriber('/inspect2speech',String,self.inspect_callback)
		rospy.Subscriber('/emergency2speech',String,self.emergency_callback)		

		self.difmsg='null'
		self.if_followme=0
		self.if_stop=0
		self.if_locpub=0
		self.say_time=0

	def emergency_callback(self,msg):
		msg.data=msg.data.lower()
		if msg.data=="true":
			self.state="true"
		else :
			self.state="false"
			self.inspect.publish("false")
			print "2222222222222222222222"


	def just_say(self,msg):
		msg.data=msg.data.lower()
		self.soundhandle.say( msg.data,self.voice)
		rospy.sleep(4)
	def inspect_callback(self,msg):
		msg.data=msg.data.lower()
		if msg.data=="get_pose":
			#发布一个那啥什么的消息
			###############################

	def cleanup(self):
		rospy.loginfo("shuting down navsp node ....")
if __name__=="__main__":
	rospy.init_node('help_me_carry')
	try:
		help_me_carry()
		rospy.spin()
	except:
		pass





