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
		self.pub = rospy.Publisher('/ifFollowme', String, queue_size=15)
		self.loc_pub = rospy.Publisher('/voice2bring', String, queue_size=15)
		self.srt_guide = rospy.Publisher('/voice2guide', String, queue_size=15)

		rospy.Subscriber('/found_person',String,self.askhelp)
                rospy.Subscriber('/middleArrive',String,self.toFinalPoint)
		rospy.Subscriber('/nav2speech',String,self.reachdst)
		rospy.Subscriber('/img2voice',String,self.just_say)
		rospy.Subscriber('/emergency2speech',String,self.emergency_callback)
                rospy.Subscriber('/follow2voice',String,self.follow_callback)
		self.difmsg='null'
		self.if_followme=0
		self.if_stop=0
		self.if_locpub=0
		rospy.sleep(13)
		self.soundhandle.say("ready",self.voice)
		rospy.sleep(1)
		self.soundhandle.say("please say jack before each question",self.voice)
		os.system("/home/kamerider/catkin_ws/src/arm/init.sh")
		self.soundhandle.say("say stop following me when you arrive",self.voice)
		rospy.sleep(3.5)
		self.soundhandle.say("I am waiting for your command",self.voice)
		rospy.sleep(3.5)
		os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx_help.sh")
		rospy.Subscriber('recognizer_output',String,self.follow)
	def emergency_callback(self,msg):
		msg.data=msg.data.lower()
		if msg.data=="true":
			self.state="true"
		else :
			self.state="false"

        def follow_callback(self,msg):
		msg.data=msg.data.lower()
		if msg.data=="far":
			os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
			self.soundhandle.say("please slow down and come close to me ",self.voice)
			rospy.sleep(2.5)
			os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx_help.sh")

	def just_say(self,msg):
		msg.data=msg.data.lower()
		self.soundhandle.say( msg.data,self.voice)
		rospy.sleep(4)
	def askhelp(self,msg):
		msg.data=msg.data.lower()
		if msg.data=="found_person":
			self.soundhandle.say(" new operator ",self.voice)
			rospy.sleep(1.5)
			self.soundhandle.say(" i have reached the person ",self.voice)
			rospy.sleep(3)
			self.soundhandle.say("please help me carry the groceries into the house",self.voice)
			rospy.sleep(4)
			self.soundhandle.say(" now please follow me to the car",self.voice)
			rospy.sleep(4)
			self.soundhandle.say(" I am ready to start guiding ",self.voice)
			rospy.sleep(3)
			self.srt_guide.publish("instruction_over")
	def reachdst(self,msg):
		msg.data=msg.data.lower()
		if msg.data.find('grasp') > -1:
			self.soundhandle.say("Please put the bag ",self.voice)
			rospy.sleep(4)
			self.soundhandle.say("on my arm",self.voice)
			rospy.sleep(4)
			os.system("/home/kamerider/catkin_ws/src/arm/raise_hand.sh")
		if msg.data.find('door') > -1:
			self.soundhandle.say("Please wait for fifteen seconds ",self.voice)
			rospy.sleep(4)
			if self.state=="true":
				self.soundhandle.say('the door is closed ',self.voice)
				rospy.sleep(2.5)
				self.soundhandle.say('please help me open the door',self.voice)
				rospy.sleep(3)
		if msg.data.find("release") > -1:
			os.system("/home/kamerider/catkin_ws/src/arm/release.sh")
			rospy.sleep(3.5)
			self.soundhandle.say(" i have arrived",self.voice)
			rospy.sleep(2)

			self.soundhandle.say(" i begin to find person ",self.voice)
			rospy.sleep(3)
			os.system("/home/kamerider/catkin_ws/src/arm/init.sh")
			rospy.sleep(3.5)
		if msg.data.find("arrived") > -1:
			self.soundhandle.say(" i have arrived at the car location",self.voice)
			rospy.sleep(3)
			self.soundhandle.say(" i have finished the mission",self.voice)
			rospy.sleep(3)
	def follow(self,msg):
		msg.data=msg.data.lower()
		print msg.data
		if msg.data.find('jack') > -1 and msg.data.find('follow-me') > -1 and self.if_followme ==0 :
			self.pub.publish('follow_start')
			self.soundhandle.say('okay i will follw you',self.voice)
			rospy.sleep(3)
			self.if_followme=1
			msg.data=' '
		elif msg.data.find('jack')>-1 and self.if_followme ==1 and self.if_stop==0:
			#if msg.data.find('stop-following-me') > -1 or msg.data.find('stop-following') > -1 or msg.data.find('stop') > -1 or msg.data.find('follow-me') > -1:
                        if msg.data.find('stop-follow-me') > -1 or msg.data.find('stop-following') > -1 or msg.data.find('stop') > -1:
				self.pub.publish('follow_stop')
				self.soundhandle.say('okay i will stop and remember this car location',self.voice)
				rospy.sleep(4)
				self.soundhandle.say('please put the bag onto my hand',self.voice)
				rospy.sleep(3)
				os.system("/home/kamerider/catkin_ws/src/arm/raise_hand.sh")
				self.if_stop=1
				msg.data=' '
		elif msg.data.find('jack')>-1 and self.if_stop==1 and self.if_locpub==0:
			if (msg.data.find('the-living-room') > -1 or msg.data.find('living-room') > -1 or msg.data.find('to-living-room') > -1 or msg.data.find('to-the-living-room') > -1 ) and self.if_locpub==0:			
				os.system("/home/kamerider/catkin_ws/src/arm/grasp.sh")
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.loc_pub.publish('livingroom')
				self.soundhandle.say('i will take to the living room ',self.voice)
				rospy.sleep(3.5)
				msg.data=' '
				print "living room"
				self.if_locpub=1
			if (msg.data.find('kitchen') > -1 or msg.data.find('the-kitchen') > -1 or msg.data.find('to-kitchen') > -1 or msg.data.find('to-the-kitchen') > -1) and self.if_locpub==0:			
				os.system("/home/kamerider/catkin_ws/src/arm/grasp.sh")
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.loc_pub.publish('kitchen')
				self.soundhandle.say('i will take to the kitchen ',self.voice)
				rospy.sleep(3.5)
				msg.data=' '
				print "kitchen"
				self.if_locpub=1
			if (msg.data.find('kitchen-table') > -1 or msg.data.find('the-kitchen-table') > -1 or msg.data.find('to-kitchen-table') > -1 or msg.data.find('to-the-kitchen-table') > -1) and self.if_locpub==0:			
				os.system("/home/kamerider/catkin_ws/src/arm/grasp.sh")
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.loc_pub.publish('kitchentable')
				self.soundhandle.say('i will take to the kitchen table ',self.voice)
				rospy.sleep(3.5)
				msg.data=' '
				print "kitchen table"
				self.if_locpub=1
			if (msg.data.find('hallway') > -1 or msg.data.find('the-hallway') > -1 or msg.data.find('to-hallway') > -1 or msg.data.find('to-the-hallway') > -1) and self.if_locpub==0:			
				os.system("/home/kamerider/catkin_ws/src/arm/grasp.sh")
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.loc_pub.publish('hallway')
				self.soundhandle.say('i will take to the hallway ',self.voice)
				rospy.sleep(3.5)
				msg.data=' '
				print "hallway"
				self.if_locpub=1
			if (msg.data.find('little-table') > -1 or msg.data.find('the-little-table') > -1 or msg.data.find('to-little-table') > -1 or msg.data.find('to-the-little-table') > -1) and self.if_locpub==0:			
				os.system("/home/kamerider/catkin_ws/src/arm/grasp.sh")
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.loc_pub.publish('littletable')
				self.soundhandle.say('i will take to the little table ',self.voice)
				rospy.sleep(3.5)
				msg.data=' '
				print "little-table"
				self.if_locpub=1
			if (msg.data.find('dining-table-a') > -1 or msg.data.find('the-dining-table-a') > -1 or msg.data.find('to-dining-table-a') > -1 or msg.data.find('to-the-dining-table-a') > -1) and self.if_locpub==0:			
				os.system("/home/kamerider/catkin_ws/src/arm/grasp.sh")
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.loc_pub.publish('littletable')
				self.soundhandle.say('i will take to the dining table a ',self.voice)
				rospy.sleep(3.5)
				msg.data=' '
				print "dining-table-a"
				self.if_locpub=1
			if (msg.data.find('dining-room') > -1 or msg.data.find('the-dining-room') > -1 or msg.data.find('to-dining-room') > -1 or msg.data.find('to-the-dining-room') > -1) and self.if_locpub==0:			
				os.system("/home/kamerider/catkin_ws/src/arm/grasp.sh")
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.loc_pub.publish('diningroom')
				self.soundhandle.say('i will take to the dining room ',self.voice)
				rospy.sleep(3.5)
				msg.data=' '
				print "dining room"
				self.if_locpub=1
			if (msg.data.find('to-bar-table') > -1 or msg.data.find('bar-table') > -1 or msg.data.find('bar') > -1 or msg.data.find('to-the-bar-table') > -1 ) and self.if_locpub==0:			
				os.system("/home/kamerider/catkin_ws/src/arm/grasp.sh")
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.loc_pub.publish('diningroom')
				self.soundhandle.say('i will take to the bar table ',self.voice)
				rospy.sleep(3.5)
				msg.data=' '
				print "bar table"
				self.if_locpub=1
			if (msg.data.find('dining-table-b') > -1 or msg.data.find('to-dining-table-b') > -1 or msg.data.find('to-the-dining-table-b') > -1 or msg.data.find('the-dining-table-b') > -1) and self.if_locpub==0:			
				os.system("/home/kamerider/catkin_ws/src/arm/grasp.sh")
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.loc_pub.publish('littletable')
				self.soundhandle.say('i will take to the dining table b ',self.voice)
				rospy.sleep(3.5)
				msg.data=' '
				print "dining table b"
				self.if_locpub=1
			if (msg.data.find('living-room') > -1 or msg.data.find('to-living-room') > -1 or msg.data.find('to-the-living-room') > -1 or msg.data.find('the-living-room') > -1) and self.if_locpub==0:			
				os.system("/home/kamerider/catkin_ws/src/arm/grasp.sh")
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.loc_pub.publish('livingroom')
				self.soundhandle.say('i will take to the living room ',self.voice)
				rospy.sleep(3.5)
				msg.data=' '
				print "living-room"
				self.if_locpub=1
                        if (msg.data.find('bedroom') > -1 or msg.data.find('to-bedroom') > -1 or msg.data.find('to-the-bedroom') > -1 or msg.data.find('the-bedroom') > -1) and self.if_locpub==0:			
				os.system("/home/kamerider/catkin_ws/src/arm/grasp.sh")
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.loc_pub.publish('bedroom')
				self.soundhandle.say('i will take to the bedroom ',self.voice)
				rospy.sleep(3.5)
				msg.data=' '
				print "bed-room"
				self.if_locpub=1
			if (msg.data.find('sofa') > -1 or msg.data.find('to-sofa') > -1 or msg.data.find('to-the-sofa') > -1 or msg.data.find('the-sofa') > -1) and self.if_locpub==0:			
				os.system("/home/kamerider/catkin_ws/src/arm/grasp.sh")
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.loc_pub.publish('livingroom')
				self.soundhandle.say('i will take to the sofa ',self.voice)
				rospy.sleep(3.5)
				msg.data=' '
				print "sofa"
				self.if_locpub=1
			if (msg.data.find('arm-chair') > -1 or msg.data.find('to-arm-chair') > -1 or msg.data.find('to-the-arm-chair') > -1 or msg.data.find('the-arm-chair') > -1) and self.if_locpub==0:			
				os.system("/home/kamerider/catkin_ws/src/arm/grasp.sh")
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.loc_pub.publish('livingroom')
				self.soundhandle.say('i will take to the arm chair ',self.voice)
				rospy.sleep(3.5)
				msg.data=' '
				print "arm-chair"
				self.if_locpub=1
			if (msg.data.find('coffee-table') > -1 or msg.data.find('to-coffee-table') > -1 or msg.data.find('to-the-coffee-table') > -1 or msg.data.find('the-coffee-table') > -1) and self.if_locpub==0:			
				os.system("/home/kamerider/catkin_ws/src/arm/grasp.sh")
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.loc_pub.publish('coffeetable')
				self.soundhandle.say('i will take to the coffee table ',self.voice)
				rospy.sleep(3.5)
				msg.data=' '
				print "coffee-table"
				self.if_locpub=1
		elif msg.data.find("jack")>-1 or msg.data.find("follow")>-1 or msg.data.find("follow-me")>-1 or msg.data.find("kamerider")>-1 or msg.data.find('to-kitchen')>-1 or msg.data.find("stop-following-me")>-1 or msg.data.find("stop-following")>-1 or msg.data.find("stop")>-1 or msg.data.find('living-room')>-1 or msg.data.find('the-bedroom')>-1 or msg.data.find('the-living-room')>-1 or msg.data.find('to-the-bedroom')>-1 or msg.data.find('to-the-living-room')>-1 or msg.data.find('to-bedroom')>-1 or msg.data.find('to-living-room')>-1 or msg.data.find('take')>-1 or msg.data.find('bring')>-1:
			print "6666666666666666666666666666666"
			print msg.data
			os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")				
			self.soundhandle.say('please say jack and repeat',self.voice)
			rospy.sleep(4)
			os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx_help.sh")
		else :
			return



	
	def toFinalPoint(self,msg):
		msg.data=msg.data.lower()
		print msg.data
		if msg.data=="livingroom":			
			self.loc_pub.publish('livingroom')
			self.soundhandle.say('i will continue to the living room ',self.voice)
			rospy.sleep(3.5)
			msg.data=' '
			print "living room"

	def cleanup(self):
		rospy.loginfo("shuting down navsp node ....")
if __name__=="__main__":
	rospy.init_node('help_me_carry')
	try:
		help_me_carry()
		rospy.spin()
	except:
		pass





