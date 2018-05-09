#!/usr/bin/env python
# -*- coding:UTF-8 -*-

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
		self.question_start_signal = rospy.get_param("~question_start_signal", "")
		self.state="true"
		self.soundhandle=SoundClient()
		rospy.sleep(1)
		self.soundhandle.stopAll()
		rospy.sleep(1)
		self.pub = rospy.Publisher('/ifFollowme', String, queue_size=15)
		self.loc_pub = rospy.Publisher('/voice2bring', String, queue_size=15)
		self.img_pub = rospy.Publisher('/voice2img', String, queue_size=15)


		#rospy.Subscriber('found_person',String,self.askhelp)
		rospy.Subscriber('nav2speech',String,self.reachdst)
		#rospy.Subscriber('/prediction_end',String,self.just_say)
		#print "1"
		#rospy.Subscriber('emergency2speech',String,self.emergency_callback)
		#print "1"
                rospy.Subscriber('/follow2voice',String,self.follow_callback)
		#学习地点	
		self.if_followme=0
		self.if_stop=0
		self.count_point=1
		self.if_locpub=0
		self.if_confirm_placename=0
		self.if_confirm_placename_list=0
		self.ready_back=0
		self.location_num_first=1

		self.location_dict={}
		#/学习地点


		#gpsr
		self.if_locpub_right=0

		self.candidate_loc=""
		self.candidate_target=""
		self.candidate_action=""
		self.target_place = ""
		self.target_action = ""
		self.target_target = ""


		self.is_listen_thing=0
		self.find_thing_num=0
		self.thing_in_sentence=[]
		self.confirm_thing=0

		self.location=['living-table','side-shelf','chair','living-table','book-shelf']

		self.allthing=['curry','soup','jam','soy-milk','energy-drink','tea','kiwi','dekopon','choco-snack'
				,'chewing-gum','samntha','kim','amelia','chole','lily','avery','harper','emma','olivia']
		self.key_sentence=""

		self.location_num_second=0
		#/gpsr





		
		
		self.allplace=['living-table','side-shelf','chair','living-table','book-shelf']
		self.place_in_sentence=[]
		self.find_place_num=0
		

		self.soundhandle.say("ready",self.voice)
		rospy.sleep(1)
		self.soundhandle.say("please say jack before each question",self.voice)
		rospy.sleep(3.5)
		#os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
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
			os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")

	def just_say(self,msg):
		msg.data=msg.data.lower()
		if msg.data.find('finish') > -1:
			self.soundhandle.say("I have find the thing",self.voice)
			rospy.sleep(2.5)
			self.soundhandle.say("can you help me put it on my box",self.voice)
			rospy.sleep(10)
			self.soundhandle.say("ok I will go back to the start point",self.voice)
			rospy.sleep(3)
			self.loc_pub.publish('start_point')
			self.soundhandle.say("wa wa wa wa wa",self.voice)

	def reachdst(self,msg):
		msg.data=msg.data.lower()
		self.soundhandle.say("shit one ",self.voice)
		rospy.sleep(4)
		if msg.data.find('arrive_startpoint') > -1:
			self.soundhandle.say("shit two",self.voice)
			rospy.sleep(3)
			os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
			self.if_locpub=0
			self.if_stop=1
			self.soundhandle.say("I have arrived start point",self.voice)
			rospy.sleep(4)
			self.soundhandle.say("please tell me next action",self.voice)
			rospy.sleep(4)
			os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
		if msg.data.find('remember') > -1:
			os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
			self.soundhandle.say("I have remember this point ",self.voice)
			rospy.sleep(4)
			os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
		if msg.data.find("findsomething") > -1:
			os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
			rospy.sleep(3.5)
			self.soundhandle.say(" i have arrived",self.voice)
			rospy.sleep(2)
			self.ready_back=1
			self.soundhandle.say(" please put the thing on me ",self.voice)
			rospy.sleep(8)
			self.soundhandle.say(" I will go back",self.voice)
			rospy.sleep(3)
			self.loc_pub.publish('start_point')
			os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
		if msg.data.find('next_turn') > -1:
			self.soundhandle.say("one two three",self.voice)
			rospy.sleep(3)
			os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
			self.if_stop=1
			self.soundhandle.say("I have finish this round",self.voice)
			rospy.sleep(4)
			self.soundhandle.say("please tell me next action",self.voice)
			rospy.sleep(4)
			os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
			self.if_followme=1
			self.if_stop=1
			self.if_locpub=0
			self.if_confirm_placename=0
			self.if_confirm_placename_list=0
			self.ready_back=0
			self.location_num_first=-1
			self.place_in_sentence=[]
			self.find_place_num=0
	def follow(self,msg):
		msg.data=msg.data.lower()
		print msg.data
#-----------------------------------------------开始follow me----------------------------------------------------
		if msg.data.find('jack') > -1 and msg.data.find('follow-me') > -1 and self.if_followme ==0 :
			os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
			
			self.pub.publish('follow_start')
			self.soundhandle.say('okay i will follw you',self.voice)
			rospy.sleep(3)
			self.if_followme=1
			msg.data=' '
			
			os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
#-----------------------------------------------学习第self.location_num_first个点的位置并确认地点的名字----------------------------------------------------
		elif msg.data.find('jack')>-1 and self.if_followme ==1 and self.if_stop==0 and self.if_confirm_placename==0 and self.if_confirm_placename_list==0 and self.count_point==self.location_num_first:
			#结束的话
			if msg.data.find('now-we-get-all-point') > -1:
				self.location_num_first=-1
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say('okay i will follow you to the start point',self.voice)
				rospy.sleep(6)
				os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
			#第一个点
			if msg.data.find('the-point-one-is') > -1 and self.location_num_first==1:
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say('okay let me confirm the name',self.voice)
				rospy.sleep(3)
				for place in self.allplace:
					print place
					if msg.data.find(place)>-1:
						self.place_in_sentence.append(place)
				if len(self.place_in_sentence)>0:
					self.soundhandle.say("is the name you want me to learn in the following list",self.voice)
					rospy.sleep(6)
					for x in self.place_in_sentence:
						self.soundhandle.say(x,self.voice)
						print x
						rospy.sleep(2)			
				self.if_confirm_placename_list=1
				self.count_point=self.count_point+1
				msg.data=' '
				os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
			#第二个点
			if msg.data.find('the-point-two-is') > -1 and self.location_num_first==2:
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say('okay let me confirm the name',self.voice)
				rospy.sleep(3)
				for place in self.allplace:
					print place
					if msg.data.find(place)>-1:
						self.place_in_sentence.append(place)
				if len(self.place_in_sentence)>0:
					self.soundhandle.say("is the name you want me to learn in the following list",self.voice)
					rospy.sleep(6)
					for x in self.place_in_sentence:
						self.soundhandle.say(x,self.voice)
						print x
						rospy.sleep(2)	
				self.if_confirm_placename_list=1
				self.count_point=self.count_point+1
				msg.data=' '
				os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
			#第三个点
			if msg.data.find('the-point-three-is') > -1 and self.location_num_first==3:
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say('okay let me confirm the name',self.voice)
				rospy.sleep(3)
				for place in self.allplace:
					print place
					if msg.data.find(place)>-1:
						self.place_in_sentence.append(place)
				if len(self.place_in_sentence)>0:
					self.soundhandle.say("is the name you want me to learn in the following list",self.voice)
					rospy.sleep(6)
					for x in self.place_in_sentence:
						self.soundhandle.say(x,self.voice)
						print x
						rospy.sleep(2)	
				self.if_confirm_placename_list=1
				self.count_point=self.count_point+1
				msg.data=' '
				os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
			#第四个点
			if msg.data.find('the-point-four-is') > -1 and self.location_num_first==4:
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say('okay let me confirm the name',self.voice)
				rospy.sleep(3)
				for place in self.allplace:
					print place
					if msg.data.find(place)>-1:
						self.place_in_sentence.append(place)
				if len(self.place_in_sentence)>0:
					self.soundhandle.say("is the name you want me to learn in the following list",self.voice)
					rospy.sleep(6)
					for x in self.place_in_sentence:
						self.soundhandle.say(x,self.voice)
						print x
						rospy.sleep(2)	
				self.if_confirm_placename_list=1
				self.count_point=self.count_point+1
				msg.data=' '
				os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
			#第五个点
			if msg.data.find('the-point-five-is') > -1 and self.location_num_first==5:
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say('okay let me confirm the name',self.voice)
				rospy.sleep(3)
				for place in self.allplace:
					print place
					if msg.data.find(place)>-1:
						self.place_in_sentence.append(place)
				if len(self.place_in_sentence)>0:
					self.soundhandle.say("is the name you want me to learn in the following list",self.voice)
					rospy.sleep(6)
					for x in self.place_in_sentence:
						self.soundhandle.say(x,self.voice)
						print x
						rospy.sleep(2)		
				self.if_confirm_placename_list=1
				self.count_point=self.count_point+1
				msg.data=' '
				os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
#----------------------------------------------确认出正确地点的名字记录下来-------------------------------------------------------------
		elif msg.data.find('jack')>-1 and self.if_followme ==1 and self.if_stop==0 and self.if_confirm_placename_list==1:
				if msg.data.find('ok-very-good') > -1:					
				#如果语句中有地点名字出现
					msg.data=' '
					print msg.data
					os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
					self.candidate_place=self.place_in_sentence[self.find_place_num]
					self.soundhandle.say("so is the list",self.voice)
					rospy.sleep(2)
					self.soundhandle.say(self.place_in_sentence[self.find_place_num],self.voice)
					rospy.sleep(1)
					self.soundhandle.playWave(self.question_start_signal+"/question_start_signal.wav")
					rospy.sleep(1.3)
					os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
					self.find_place_num=self.find_place_num+1
					self.if_confirm_placename=1
					self.if_confirm_placename_list=0
				if msg.data.find('no-good-answer') > -1:
					#否则恢复相应flag再听一遍名字
					msg.data=' '
					os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
					self.if_confirm_placename_list=0
					self.count_point=self.count_point-1
					self.place_in_sentence=[]
					self.find_place_num=0
					os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")


#-------------------------------------------------------看看地点名字识别的对不对----------------------------------------------------------------
		elif msg.data.find('jack')>-1 and self.if_followme ==1 and self.if_stop==0 and self.if_confirm_placename==1:
			#---------------------------------------正确的话发消息--------------------------------------			
			if msg.data.find('ok-very-good') > -1:
				msg.data=' '
				self.target_place=self.candidate_place
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say("ok I know the name  is",self.voice)
                                rospy.sleep(3)
				self.soundhandle.say(self.target_place,self.voice)
				rospy.sleep(2)
				#给学习到的第self.location_num_first个点和其名字添加到字典里
				self.location_dict[self.target_place]=str(self.location_num_first)
				print self.target_place
				#这里给navigation发topic
				self.pub.publish(self.target_place)
				os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
				self.location_num_first=self.location_num_first+1
				self.if_confirm_placename=0
				self.place_in_sentence=[]
				self.find_place_num=0
			#不是的话问下一个候选
			if msg.data.find('no-good-answer') > -1:
				msg.data=' '
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.candidate_place=self.place_in_sentence[self.find_place_num]
				self.soundhandle.say("so is the name of this place",self.voice)
				rospy.sleep(5)
				self.soundhandle.say(self.place_in_sentence[self.find_place_num],self.voice)
				rospy.sleep(2)
				self.soundhandle.playWave(self.question_start_signal+"/question_start_signal.wav")
				rospy.sleep(1.3)
				os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
				self.find_place_num=self.find_place_num+1
				self.if_confirm_placename=1
					


#------------------------------------------------------到达终点完成学习地点的任务------------------------------------------------------------
		elif msg.data.find('jack')>-1 and self.if_followme ==1 and self.if_stop==0:
			if msg.data.find('stop-following-me') > -1 or msg.data.find('stop-following') > -1 or msg.data.find('stop-follow-me') > -1 or msg.data.find('stop')  > -1 or msg.data.find('follow-me')  > -1:
				self.pub.publish('follow_stop')
				self.soundhandle.say('okay i will stop and remember this start location',self.voice)
				rospy.sleep(4)
				
				#self.if_stop=1
				msg.data=' '

				self.if_followme=1
				self.if_stop=1
				self.if_locpub=0
				self.if_confirm_placename=0
				self.if_confirm_placename_list=0
				self.ready_back=0
				self.location_num_first=-1
				self.place_in_sentence=[]
				self.find_place_num=0




#--------------------------------------------------------执行阶段----------------------------------------------------------------
#----------------------------------------------------首先还是抓地点词汇--------------------------------------------------------
		elif msg.data.find('jack')>-1 and self.if_stop==1 and self.if_locpub==0:
			rospy.sleep(2.5)
			self.key_sentence=msg.data
			if (msg.data.find('the-side-shelf') > -1 or msg.data.find('side-shelf') > -1 or msg.data.find('to-side-shelf') > -1 or msg.data.find('to-the-side-shelf') > -1 ) and self.if_locpub==0:	
				self.candidate_loc="side-shelf"
				msg.data=""
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say("should I go to the side shelf",self.voice)
                                rospy.sleep(2.5)
				self.soundhandle.playWave(self.question_start_signal+"/question_start_signal.wav")
				rospy.sleep(1.3)
				os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
				self.if_locpub=1
			if (msg.data.find('the-bed') > -1 or msg.data.find('bed') > -1 or msg.data.find('to-bed') > -1 or msg.data.find('to-the-bed') > -1 ) and self.if_locpub==0:	
				self.candidate_loc="bedroom"
				msg.data=""
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say("should I go to the bedroom",self.voice)
                                rospy.sleep(2.5)
				self.soundhandle.playWave(self.question_start_signal+"/question_start_signal.wav")
				rospy.sleep(1.3)
				os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
				self.if_locpub=1
			if (msg.data.find('the-chair') > -1 or msg.data.find('chair') > -1 or msg.data.find('to-chair') > -1 or msg.data.find('to-the-chair') > -1 ) and self.if_locpub==0:	
				self.candidate_loc="chair"
				msg.data=""
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say("should I go to the chair",self.voice)
                                rospy.sleep(2.5)
				self.soundhandle.playWave(self.question_start_signal+"/question_start_signal.wav")
				rospy.sleep(1.3)
				os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
				self.if_locpub=1
			if (msg.data.find('the-living-table') > -1 or msg.data.find('living-table') > -1 or msg.data.find('to-living-table') > -1 or msg.data.find('to-the-living-table') > -1 ) and self.if_locpub==0:	
				self.candidate_loc="living-table"
				msg.data=""
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say("should I go to the living-table",self.voice)
                                rospy.sleep(2.5)
				self.soundhandle.playWave(self.question_start_signal+"/question_start_signal.wav")
				rospy.sleep(1.3)
				os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
				self.if_locpub=1
			if (msg.data.find('the-book-shelf') > -1 or msg.data.find('book-shelf') > -1 or msg.data.find('to-book-shelf') > -1 or msg.data.find('to-the-book-shelf') > -1 ) and self.if_locpub==0:	
				self.candidate_loc="book-shelf"
				msg.data=""
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say("should I go to the book-shelf",self.voice)
                                rospy.sleep(2.5)
				self.soundhandle.playWave(self.question_start_signal+"/question_start_signal.wav")
				rospy.sleep(1.3)
				os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
				self.if_locpub=1
#---------------------------------------看看识别出的地点名词对不对-----------------------------------------------------------------------------------	
		elif msg.data.find('jack')>-1 and self.if_locpub==1 and self.if_locpub_right==0 and self.if_stop==1:
			rospy.sleep(2.5)
			#-----------------------------------如果错误只能几个地点词汇一个个猜---------------------------------------------------
			if msg.data.find('no-good-answer') > -1:	
				msg.data=""
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say("so should I go to the",self.voice)
				rospy.sleep(2)
				self.soundhandle.say(self.location[self.location_num_second%4],self.voice)
				rospy.sleep(2)				
				self.candidate_loc=self.location[self.location_num_second%4]
				self.location_num_second=self.location_num_second+1
				rospy.sleep(0.5)
				self.soundhandle.playWave(self.question_start_signal+"/question_start_signal.wav")
				rospy.sleep(1.3)
				os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
			#-----------------------------------地点词汇如果正确看看识别出的话有什么物体名---------------------------------------			
			if msg.data.find('ok-very-good') > -1:	
				msg.data=""
                          	self.target_place = self.candidate_loc
				self.if_locpub_right=1	
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say("ok I will go to the",self.voice)
				rospy.sleep(2)
				self.soundhandle.say(self.target_place,self.voice)
				rospy.sleep(2)
				for thing in self.allthing:
					if self.key_sentence.find(thing)>-1:
						self.thing_in_sentence.append(thing)
				if len(self.thing_in_sentence)>0:
					self.soundhandle.say("is the thing you want in the following list",self.voice)
					rospy.sleep(4)
					self.is_listen_thing=1
					for x in self.thing_in_sentence:
						self.soundhandle.say(x,self.voice)
						print x
						rospy.sleep(2)
					os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
#------------------------------------------------在list范围内就可以开问具体thing-----------------------------------------------------------
		elif msg.data.find('jack')>-1 and self.if_locpub==1 and self.if_locpub_right==1 and self.is_listen_thing==1 and self.if_stop==1 and self.confirm_thing==0:
			rospy.sleep(2.5)
			if msg.data.find('ok-very-good') > -1:					
				#如果语句中有物品出现
				msg.data=""
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.candidate_target=self.thing_in_sentence[self.find_thing_num]
				self.candidate_action="bring you"
				self.soundhandle.say("so should I go there",self.voice)
				rospy.sleep(2)
				self.soundhandle.say("and take a",self.voice)
			        rospy.sleep(1)
				self.soundhandle.say(self.thing_in_sentence[self.find_thing_num],self.voice)
				rospy.sleep(1)
				self.soundhandle.playWave(self.question_start_signal+"/question_start_signal.wav")
				rospy.sleep(1.3)
				os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
				self.confirm_thing=1
				self.find_thing_num=self.find_thing_num+1
#-------------------------------------------------------看看物体识别的对不对----------------------------------------------------------------
		if msg.data.find('jack')>-1 and self.if_locpub_right==1 and self.confirm_thing==1 and self.is_listen_thing==1 and self.if_stop==1:
			self.soundhandle.say('four four four four four',self.voice)
			rospy.sleep(2.5)
			#---------------------------------------物体也正确的话发消息--------------------------------------			
			if msg.data.find('ok-very-good') > -1:
				msg.data=""
				self.target_action = self.candidate_action
				self.target_target = self.candidate_target
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say("ok I will go to",self.voice)
                                rospy.sleep(2)
				self.soundhandle.say(self.target_place,self.voice)
				rospy.sleep(1)
				self.soundhandle.say(self.target_action,self.voice)
				rospy.sleep(1)
				self.soundhandle.say(self.target_target,self.voice)
				rospy.sleep(1)
				#这里给navigation发topic
				self.loc_pub.publish(self.location_dict[self.target_place])
				os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
			if msg.data.find('no-good-answer') > -1:
				msg.data=""
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				if len(self.thing_in_sentence)>self.find_thing_num:
					self.candidate_target=self.thing_in_sentence[self.find_thing_num]
					self.candidate_action="take"
					self.soundhandle.say("so should I go there",self.voice)
					rospy.sleep(3)
					self.soundhandle.say("and take a",self.voice)
				        rospy.sleep(2)
					self.soundhandle.say(self.candidate_target,self.voice)
					rospy.sleep(2)
					self.soundhandle.playWave(self.question_start_signal+"/question_start_signal.wav")
					rospy.sleep(1.3)
					os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
					self.confirm_thing=1
					self.find_thing_num=self.find_thing_num+1








		elif msg.data.find("jack")>-1 or msg.data.find("follow")>-1 or msg.data.find("follow-me")>-1 or msg.data.find("kamerider")>-1 or msg.data.find('to-kitchen')>-1 or msg.data.find("stop-following-me")>-1 or msg.data.find("stop-following")>-1 or msg.data.find("stop")>-1 or msg.data.find('living-room')>-1 or msg.data.find('the-bedroom')>-1 or msg.data.find('the-living-room')>-1 or msg.data.find('to-the-bedroom')>-1 or msg.data.find('to-the-living-room')>-1 or msg.data.find('to-bedroom')>-1 or msg.data.find('to-living-room')>-1 or msg.data.find('take')>-1 or msg.data.find('bring')>-1:
			print "6666666666666666666666666666666"
			print msg.data
			os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")				
			self.soundhandle.say('please say jack and repeat',self.voice)
			rospy.sleep(4)
			os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
		else :
			return
	def cleanup(self):
		rospy.loginfo("shuting down navsp node ....")
if __name__=="__main__":
	rospy.init_node('help_me_carry')
	try:
		help_me_carry()
		rospy.spin()
	except:
		pass





