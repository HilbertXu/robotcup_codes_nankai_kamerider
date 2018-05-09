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
		self.cate1='a'
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
		self.soundhandle.say("please say jack before each question",self.voice)
		rospy.sleep(3.5)
		self.if_heared=0
		self.speech2nav_pub = rospy.Publisher('/speech2nav', String, queue_size=15)
                self.table_pub = rospy.Publisher('/at_table', String, queue_size=1)
		self.qq=0
		self.arrived_time=0
		rospy.Subscriber('/barplace',String,self.bardect_callback)
		rospy.Subscriber('/img2voice',String,self.img_callback)	
		rospy.Subscriber('/nav2speech',String,self.nav_callback)		
		rospy.Subscriber('recognizer_output',String,self.follow)
		self.if_dect=0
	
	def img_callback(self,msg):
		msg.data=msg.data.lower()
		if self.arrived_time==0:
			self.qq=1
                        self.table_pub.publish("found_table")
			self.soundhandle.say('hello i have found you',self.voice)
			rospy.sleep(3)
			self.soundhandle.say('please tell me what do you want to order',self.voice)
			rospy.sleep(4)
			self.soundhandle.say('please say jack thats all when you finish  ',self.voice)
			
			rospy.sleep(3)		
			os.system("~/catkin_ws/src/speech/run_pocketsphinx.sh")
		else:
			self.soundhandle.say('please take your  away',self.voice)
			rospy.sleep(3)

	def bardect_callback(self,msg):
		msg.data=msg.data.lower()
		print msg.data
		self.soundhandle.say('the bar is on the '+ msg.data,self.voice)
		rospy.sleep(5)
		self.soundhandle.say('i start to find  customer ',self.voice)
		rospy.sleep(3)
		self.speech2nav_pub.publish("wave")
	def nav_callback(self,msg):
		msg.data=msg.data.lower()
		print msg.data
		if msg.data.find("wave")>-1:
			self.soundhandle.say('please take your orders away',self.voice)
			rospy.sleep(5)
		elif msg.data.find('arrived_bar_position')>-1:
			self.soundhandle.say('i have arrived at the bar table',self.voice)
			rospy.sleep(3)
			self.soundhandle.say('please put '+ self.cate1 +' onto the tray' ,self.voice)
			rospy.sleep(5)
			self.soundhandle.say('please say jack go back when you finished' ,self.voice)
			rospy.sleep(3.5)

	def follow(self,msg):
		msg.data=msg.data.lower()
		print msg.data
		if msg.data.find('jack') > -1 and msg.data.find('start') > -1 and self.if_dect ==0 :
			self.speech2nav_pub.publish('start')
			self.soundhandle.say('okay i start to find the bar table',self.voice)
			rospy.sleep(1.5)
			self.if_dect=1	
			os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
		if msg.data.find('jack')>-1 and msg.data.find('thats-all')>-1 :
			self.soundhandle.say('okay i will go back to the bar table',self.voice)
			rospy.sleep(1.5)
			rospy.sleep(1.5)	
			self.speech2nav_pub.publish('return')
			self.if_heared=1
		if self.if_heared==0 and self.qq==1:
			if msg.data.find('mixed-nuts')>-1:
				if self.cate1!='a':
					self.cate2='mixed-nuts'
				else:
					self.cate1='mixed-nuts'
				self.soundhandle.say('okay i will take you the mixed-nuts',self.voice)
				rospy.sleep(1.5)
				 
				rospy.sleep(1.5)	
				  
				self.if_heared=1
			elif msg.data.find('canned-fish')>-1:
				if self.cate1!='a':
					self.cate2='canned-fish'
				else:
					self.cate1='canned-fish'
				self.soundhandle.say('okay i will take you the canned-fish',self.voice)
				rospy.sleep(1.5)
				 
				rospy.sleep(1.5)	
				  
				self.if_heared=1

			elif msg.data.find('pringles')>-1:
				if self.cate1!='a':
					self.cate2='pringles'
				else:
					self.cate1='pringles'
				self.soundhandle.say('okay i will take you the pringles',self.voice)
				rospy.sleep(1.5)
				 
				rospy.sleep(1.5)	
				  
				self.if_heared=1
			elif msg.data.find('cereal')>-1:
				if self.cate1!='a':
					self.cate2='cereal'
				else:
					self.cate1='cereal'
				self.soundhandle.say('okay i will take you the cereal',self.voice)
				rospy.sleep(1.5)
				 
				rospy.sleep(1.5)	
				  
				self.if_heared=1
			elif msg.data.find('apple-juice')>-1:
				if self.cate1!='a':
					self.cate2='apple-juice'
				else:
					self.cate1='apple-juice'
				self.soundhandle.say('okay i will take you the apple-juice',self.voice)
				rospy.sleep(1.5)
				 
				rospy.sleep(1.5)	
				  
				self.if_heared=1
			elif msg.data.find('milk-tea')>-1:
				if self.cate1!='a':
					self.cate2='milk-tea'
				else:
					self.cate1='milk-tea'
				self.soundhandle.say('okay i will take you the milk-tea',self.voice)
				rospy.sleep(1.5)
				 
				rospy.sleep(1.5)	
				  
				self.if_heared=1
			elif msg.data.find('jelly')>-1:
				if self.cate1!='a':
					self.cate2='jelly'
				else:
					self.cate1='jelly'
				self.soundhandle.say('okay i will take you the jelly',self.voice)
				rospy.sleep(1.5)
				 
				rospy.sleep(1.5)	
				  
				self.if_heared=1
			elif msg.data.find('milk-biscuit')>-1:
				if self.cate1!='a':
					self.cate2='milk-biscuit'
				else:
					self.cate1='milk-biscuit'
				self.soundhandle.say('okay i will take you the milk-biscuit',self.voice)
				rospy.sleep(1.5)
				 
				rospy.sleep(1.5)	
				  
				self.if_heared=1
			elif msg.data.find('cereal-bowl')>-1:
				if self.cate1!='a':
					self.cate2='cereal-bowl'
				else:
					self.cate1='cereal-bowl'
				self.soundhandle.say('okay i will take you the cereal-bowl',self.voice)
				rospy.sleep(1.5)
				 
				rospy.sleep(1.5)	
				  
				self.if_heared=1
			elif msg.data.find('root-beer')>-1:
				if self.cate1!='a':
					self.cate2='root-beer'
				else:
					self.cate1='root-beer'
				self.soundhandle.say('okay i will take you the root-beer',self.voice)
				rospy.sleep(1.5)
				 
				rospy.sleep(1.5)	
				  
				self.if_heared=1
			elif msg.data.find('potato-chip')>-1:
				if self.cate1!='a':
					self.cate2='potato-chip'
				else:
					self.cate1='potato-chip'
				self.soundhandle.say('okay i will take you the potato-chip',self.voice)
				rospy.sleep(1.5)
				 
				rospy.sleep(1.5)	
				  
				self.if_heared=1
			elif msg.data.find('instant-noodle')>-1:
				if self.cate1!='a':
					self.cate2='instant-noodle'
				else:
					self.cate1='instant-noodle'
				self.soundhandle.say('okay i will take you the instant-noodle',self.voice)
				rospy.sleep(1.5)
				 
				rospy.sleep(1.5)	
				  
				self.if_heared=1
			elif msg.data.find('green-tea')>-1:
				if self.cate1!='a':
					self.cate2='green-tea'
				else:
					self.cate1='green-tea'
				self.soundhandle.say('okay i will take you the green-tea',self.voice)
				rospy.sleep(1.5)
				 
				rospy.sleep(1.5)	
				  
				self.if_heared=1
		else:
			if msg.data.find('jack') > -1 and  msg.data.find('go-back') > -1:
				self.speech2nav_pub.publish('go-back')
				self.soundhandle.say('okay i will deliver these to the customers',self.voice)
				rospy.sleep(3.5)
				self.if_heared=0
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")

			

			

	def cleanup(self):
		rospy.loginfo("shuting down navsp node ....")
if __name__=="__main__":
	rospy.init_node('help_me_carry')
	try:
		help_me_carry()
		rospy.spin()
	except:
		pass





