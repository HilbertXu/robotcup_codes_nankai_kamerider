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

class gpsr:

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
                self.back2start_pub = rospy.Publisher('/back2Start', String, queue_size=15)
		self.loc_pub = rospy.Publisher('/speechGiveLocation', String, queue_size=15)
		self.find_target_thing_pub = rospy.Publisher('/imgFindTargetThing', String, queue_size=15)
		self.find_person_pub = rospy.Publisher('/nav2image', String, queue_size=15)
		rospy.Subscriber('/arriveLocation',String,self.reachdst_callback)
		rospy.Subscriber('/emergency2speech',String,self.emergency_callback)
		rospy.Subscriber('/found_person',String,self.askhelp)
		self.difmsg='null'
		self.if_backToStart=0
		
		self.step=0
		self.confirm_thing=0

		self.if_locpub=0
		self.if_locpub_right=0
		self.if_listen_action=0
                self.if_action_right=0
		self.if_listen_thing=0
                self.if_thing_right=0
                self.if_confirm=0

		self.if_now_answer=0

		self.is_it_edible=0
		self.is_it_solid=0
		self.is_it_snack=0
		self.is_it_sweet=0

		self.candidate_loc=""
		self.candidate_target=""
		self.candidate_action=""
		self.target_place = ""
		self.target_action = ""
		self.target_target = ""

		self.is_listen_target=0
		self.is_listen_thing=0
		self.is_listen_person=0
		self.find_target_num=0
		self.find_thing_num=0
		self.find_person_num=0
		self.target_in_sentence=[]
		self.thing_in_sentence=[]
		self.person_in_sentence=[]
		self.confirm_thing=0
		self.confirm_person=0
		self.is_answer_question=0
		self.location=['living-room','corridor','bedroom','kidsroom','kitchen']
		#self.location=['living-room','corridor','bedroom','kidsroom','kitchen','cupboard','kitchen-table'
		#		,'kitchen-rack','bed','teepee','desk','side-shelf'
		#		,'book-shelf','living-rack','sofa','living-table']
		self.thing1111=['candy','chewing gum','jelly']
		self.thing1110=['cup star','curry','chips']
		self.thing1101=['maize','onion','radish']
		self.thing1100=['apple','bread','orange']
		self.thing10=['water','cola','beer','green tea']
		self.thing011=['peanut','hair gel','shampoo']
		self.thing010=['emollient cream']
		self.thing001=['bowl','plate','soup bowl']
		self.thing000=['chopsticks','fork','spoon']

		self.alltarget=['candy','chewing-gum','jelly','cup-star','curry','chips','maize','onion','radish'
				,'apple','bread','orange','water','cola','beer','green-tea','peanut','hair-gel'
				,'shampoo','emollient-cream','bowl','plate','soup-bowl','chopsticks','spoon','fork'
				,'tom','jane','lucy','james','tony','ben','miller','michael','andrew','jordon','answer-some-questions']
		self.allthing=['candy','chewing-gum','jelly','cup-star','curry','chips','maize','onion','radish'
				,'apple','bread','orange','water','cola','beer','green-tea','peanut','hair-gel'
				,'shampoo','emollient-cream','bowl','plate','soup-bowl','chopsticks','spoon','fork']
		self.allperson=['tom','jane','lucy','james','tony','ben','miller','michael','andrew','jordon']
		#self.alltarget=['curry','soup','jam','soy-milk','energy-drink','tea','kiwi','dekopon',
		#		'choco-snack','chewing-gum','samantha','kim','amelia'
		#		,'chole','lily','avery','harper','emma','olivia','sophia','john','steve',
		#		'donald','jackson','lucas','oliver','noah','liam','mason','jacob','drink','food',
		#		'fruit','food']
		#self.allthing=['curry','soup','jam','soy-milk','energy-drink','tea','kiwi','dekopon',
		#		'choco-snack','chewing-gum','drink','food','fruit','food']
		#self.allperson=['samantha','kim','amelia'
		#		,'chole','lily','avery','harper','emma','olivia','sophia','john','steve',
		#		'donald','jackson','lucas','oliver','noah','liam','mason','jacob']

		self.key_sentence=""

		self.alltarget_num=0
		self.allthing_num=0
		self.allperson_num=0
		self.location_num=0
		self.thing1111_num=0
		self.thing1110_num=0

		self.soundhandle.say("ok I am ready",self.voice)
		rospy.sleep(3)
		self.soundhandle.say("please say jack before each command",self.voice)
		self.soundhandle.say("I am waiting for your command",self.voice)
		os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
		rospy.Subscriber('recognizer_output',String,self.listen_callback)
	def emergency_callback(self,msg):
		msg.data=msg.data.lower()
		if msg.data=="true":
			self.state="true"
		else :
			self.state="false"
	def listen_callback(self,msg):
		msg.data=msg.data.lower()
		print msg.data
#-------------------------------first step----------------------------------------------------------------
#-------------------------------首先还是抓地点词汇--------------------------------------------------------
		if msg.data.find('jack')>-1 and msg.data.find('you-can-just-go-out')>-1:
			msg.data=""
			self.loc_pub.publish("out")
		if msg.data.find('jack')>-1 and msg.data.find('just-go-to-the-start-point')>-1:
			msg.data=""
			self.loc_pub.publish("start")
		if msg.data.find('jack')>-1 and msg.data.find('now-we-begin')>-1:
			self.soundhandle.say("ok I am ready for command",self.voice)
			rospy.sleep(1)
			rospy.sleep(1)
			msg.data=""
			self.if_backToStart=0
			self.step=0
			self.confirm_thing=0
			self.if_locpub=0
			self.if_locpub_right=0
			self.if_listen_action=0
		        self.if_action_right=0
			self.if_listen_thing=0
		        self.if_thing_right=0
		        self.if_confirm=0
			self.if_now_answer=0
			self.is_it_edible=0
			self.is_it_solid=0
			self.is_it_snack=0
			self.is_it_sweet=0
			self.candidate_loc=""
			self.candidate_target=""
			self.candidate_action=""
			self.target_place = ""
			self.target_action = ""
			self.target_target = ""
			self.is_listen_target=0
			self.is_listen_thing=0
			self.is_listen_person=0
			self.find_target_num=0
			self.find_thing_num=0
			self.find_person_num=0
			self.target_in_sentence=[]
			self.thing_in_sentence=[]
			self.person_in_sentence=[]
			self.confirm_thing=0
			self.confirm_person=0
			self.is_answer_question=0
			self.key_sentence=""
			self.alltarget_num=0
			self.allthing_num=0
			self.allperson_num=0
			self.location_num=0
			self.thing1111_num=0
			self.thing1110_num=0
		if msg.data.find('jack')>-1 and self.if_locpub==0 and self.step==0:
			self.key_sentence=msg.data
			if (msg.data.find('the-living-room') > -1 or msg.data.find('living-room') > -1 or msg.data.find('to-living-room') > -1 or msg.data.find('to-the-living-room') > -1 ) and self.if_locpub==0:	
				self.candidate_loc="living-room"
				msg.data=""
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say("should I go to the living room",self.voice)
                                rospy.sleep(2.5)
				self.soundhandle.playWave(self.question_start_signal+"/question_start_signal.wav")
				rospy.sleep(1.3)
				os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
				self.if_locpub=1
			if (msg.data.find('the-bedroom') > -1 or msg.data.find('bedroom') > -1 or msg.data.find('to-bedroom') > -1 or msg.data.find('to-the-bedroom') > -1 ) and self.if_locpub==0:	
				self.candidate_loc="bedroom"
				msg.data=""
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say("should I go to the bedroom",self.voice)
                                rospy.sleep(2.5)
				self.soundhandle.playWave(self.question_start_signal+"/question_start_signal.wav")
				rospy.sleep(1.3)
				os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
				self.if_locpub=1
			if (msg.data.find('the-kitchen') > -1 or msg.data.find('kitchen') > -1 or msg.data.find('to-kitchen') > -1 or msg.data.find('to-the-kitchen') > -1 ) and self.if_locpub==0:	
				self.candidate_loc="kitchen"
				msg.data=""
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say("should I go to the kitchen",self.voice)
                                rospy.sleep(2.5)
				self.soundhandle.playWave(self.question_start_signal+"/question_start_signal.wav")
				rospy.sleep(1.3)
				os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
				self.if_locpub=1
			if (msg.data.find('the-kids-room') > -1 or msg.data.find('kids-room') > -1 or msg.data.find('to-kids-room') > -1 or msg.data.find('to-the-kids-room') > -1 ) and self.if_locpub==0:	
				self.candidate_loc="kidsroom"
				msg.data=""
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say("should I go to the kidsroom",self.voice)
                                rospy.sleep(2.5)
				self.soundhandle.playWave(self.question_start_signal+"/question_start_signal.wav")
				rospy.sleep(1.3)
				os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
				self.if_locpub=1
			if (msg.data.find('the-corridor') > -1 or msg.data.find('corridor') > -1 or msg.data.find('to-corridor') > -1 or msg.data.find('to-the-corridor') > -1 ) and self.if_locpub==0:	
				self.candidate_loc="corridor"
				msg.data=""
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say("should I go to the corridor",self.voice)
                                rospy.sleep(2.5)
				self.soundhandle.playWave(self.question_start_signal+"/question_start_signal.wav")
				rospy.sleep(1.3)
				os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
				self.if_locpub=1
			if (msg.data.find('the-cupboard') > -1 or msg.data.find('cupboard') > -1 or msg.data.find('to-cupboard') > -1 or msg.data.find('to-the-cupboard') > -1 ) and self.if_locpub==0:	
				self.candidate_loc="kitchen"
				msg.data=""
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say("should I go to the cupboard",self.voice)
                                rospy.sleep(2.5)
				self.soundhandle.playWave(self.question_start_signal+"/question_start_signal.wav")
				rospy.sleep(1.3)
				os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
				self.if_locpub=1
			if (msg.data.find('the-kitchen-table') > -1 or msg.data.find('kitchen-table') > -1 or msg.data.find('to-kitchen-table') > -1 or msg.data.find('to-the-kitchen-table') > -1 ) and self.if_locpub==0:	
				self.candidate_loc="kitchen"
				msg.data=""
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say("should I go to the kitchen-table",self.voice)
                                rospy.sleep(2.5)
				self.soundhandle.playWave(self.question_start_signal+"/question_start_signal.wav")
				rospy.sleep(1.3)
				os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
				self.if_locpub=1
			if (msg.data.find('the-kitchen-rack') > -1 or msg.data.find('kitchen-rack') > -1 or msg.data.find('to-kitchen-rack') > -1 or msg.data.find('to-the-kitchen-rack') > -1 ) and self.if_locpub==0:	
				self.candidate_loc="kitchen"
				msg.data=""
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say("should I go to the kitchen-rack",self.voice)
                                rospy.sleep(2.5)
				self.soundhandle.playWave(self.question_start_signal+"/question_start_signal.wav")
				rospy.sleep(1.3)
				os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
				self.if_locpub=1
			if (msg.data.find('the-bed') > -1 or msg.data.find('bed') > -1 or msg.data.find('to-bed') > -1 or msg.data.find('to-the-bed') > -1 ) and self.if_locpub==0:	
				self.candidate_loc="bedroom"
				msg.data=""
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say("should I go to the bed",self.voice)
                                rospy.sleep(2.5)
				self.soundhandle.playWave(self.question_start_signal+"/question_start_signal.wav")
				rospy.sleep(1.3)
				os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
				self.if_locpub=1
			if (msg.data.find('the-teepee') > -1 or msg.data.find('teepee') > -1 or msg.data.find('to-teepee') > -1 or msg.data.find('to-the-teepee') > -1 ) and self.if_locpub==0:	
				self.candidate_loc="bedroom"
				msg.data=""
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say("should I go to the teepee",self.voice)
                                rospy.sleep(2.5)
				self.soundhandle.playWave(self.question_start_signal+"/question_start_signal.wav")
				rospy.sleep(1.3)
				os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
				self.if_locpub=1
			if (msg.data.find('the-desk') > -1 or msg.data.find('desk') > -1 or msg.data.find('to-desk') > -1 or msg.data.find('to-the-desk') > -1 ) and self.if_locpub==0:	
				self.candidate_loc="kidsroom"
				msg.data=""
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say("should I go to the desk",self.voice)
                                rospy.sleep(2.5)
				self.soundhandle.playWave(self.question_start_signal+"/question_start_signal.wav")
				rospy.sleep(1.3)
				os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
				self.if_locpub=1
			if (msg.data.find('the-side-shelf') > -1 or msg.data.find('side-shelf') > -1 or msg.data.find('to-side-shelf') > -1 or msg.data.find('to-the-side-shelf') > -1 ) and self.if_locpub==0:	
				self.candidate_loc="bedroom"
				msg.data=""
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say("should I go to the side-shelf",self.voice)
                                rospy.sleep(2.5)
				self.soundhandle.playWave(self.question_start_signal+"/question_start_signal.wav")
				rospy.sleep(1.3)
				os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
				self.if_locpub=1
			if (msg.data.find('the-book-shelf') > -1 or msg.data.find('book-shelf') > -1 or msg.data.find('to-book-shelf') > -1 or msg.data.find('to-the-book-shelf') > -1 ) and self.if_locpub==0:	
				self.candidate_loc="kidsroom"
				msg.data=""
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say("should I go to the book-shelf",self.voice)
                                rospy.sleep(2.5)
				self.soundhandle.playWave(self.question_start_signal+"/question_start_signal.wav")
				rospy.sleep(1.3)
				os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
				self.if_locpub=1
			if (msg.data.find('the-living-rack') > -1 or msg.data.find('living-rack') > -1 or msg.data.find('to-living-rack') > -1 or msg.data.find('to-the-living-rack') > -1 ) and self.if_locpub==0:	
				self.candidate_loc="living-room"
				msg.data=""
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say("should I go to the living-rack",self.voice)
                                rospy.sleep(2.5)
				self.soundhandle.playWave(self.question_start_signal+"/question_start_signal.wav")
				rospy.sleep(1.3)
				os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
				self.if_locpub=1
			if (msg.data.find('the-sofa') > -1 or msg.data.find('sofa') > -1 or msg.data.find('to-sofa') > -1 or msg.data.find('to-the-sofa') > -1 ) and self.if_locpub==0:	
				self.candidate_loc="living-room"
				msg.data=""
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say("should I go to the sofa",self.voice)
                                rospy.sleep(2.5)
				self.soundhandle.playWave(self.question_start_signal+"/question_start_signal.wav")
				rospy.sleep(1.3)
				os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
				self.if_locpub=1
			if (msg.data.find('living-table') > -1 or msg.data.find('living-table') > -1 or msg.data.find('to-living-table') > -1 or msg.data.find('to-the-living-table') > -1 ) and self.if_locpub==0:	
				self.candidate_loc="living-room"
				msg.data=""
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say("should I go to the living-table",self.voice)
                                rospy.sleep(2.5)
				self.soundhandle.playWave(self.question_start_signal+"/question_start_signal.wav")
				rospy.sleep(1.3)
				os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
				self.if_locpub=1
#---------------------------------------看看识别出的地点名词对不对-----------------------------------------------------------------------------------			
		if msg.data.find('jack')>-1 and self.if_locpub==1 and self.if_locpub_right==0 and self.step==0:
			#-----------------------------------如果错误只能几个地点词汇一个个猜---------------------------------------------------
			if msg.data.find('no-good-answer') > -1:	
				msg.data=""
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say("so should I go to the",self.voice)
				rospy.sleep(2)
				self.soundhandle.say(self.location[self.location_num%5],self.voice)
				rospy.sleep(2)				
				self.candidate_loc=self.location[self.location_num%5]
				self.location_num=self.location_num+1
				rospy.sleep(0.5)
				self.soundhandle.playWave(self.question_start_signal+"/question_start_signal.wav")
				rospy.sleep(1.3)
				os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")

			#-----------------------------------地点词汇如果正确看看识别出的话有什么物体或者人名---------------------------------------			
			if msg.data.find('ok-very-good') > -1:	
				rospy.sleep(1)
				msg.data=""
                          	self.target_place = self.candidate_loc
				self.if_locpub_right=1	
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say("ok I will go to the",self.voice)
				rospy.sleep(2)
				self.soundhandle.say(self.target_place,self.voice)
				rospy.sleep(2)
				self.if_locpub=1
				self.if_locpub_right=0
				self.step=1
				#rospy.sleep(1)
				#for target in self.alltarget:
				#	if self.key_sentence.find(target)>-1:
				#		self.target_in_sentence.append(target)
				#for thing in self.allthing:
				#	if self.key_sentence.find(thing)>-1:
				#		self.thing_in_sentence.append(thing)
				#for person in self.allperson:
				#	if self.key_sentence.find(person)>-1:
				#		self.person_in_sentence.append(person)
				#if len(self.target_in_sentence)>0:
				#	self.soundhandle.say("is the target you want in the following list",self.voice)
				#	rospy.sleep(4)
				#	self.is_listen_target=0
				#	for x in self.target_in_sentence:
				#		self.soundhandle.say(x,self.voice)
				#		print x
				#		rospy.sleep(2)
				#	os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")

#------------------------------------------------在list范围内就可以开问是不是thing------------------------------------------------------------
		if msg.data.find('jack')>-1 and self.if_locpub==1 and self.if_locpub_right==1 and self.is_listen_target==0 and self.step==0:
			if msg.data.find('ok-very-good') > -1:					
				#如果语句中有物品出现
				msg.data=""
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				if len(self.target_in_sentence)>0:
					self.soundhandle.say("is the thing you want in the following list",self.voice)
					rospy.sleep(4)
					self.is_listen_thing=0
					os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
					for x in self.thing_in_sentence:
						os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
						self.soundhandle.say(x,self.voice)
						print x
						rospy.sleep(2)
				os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
				self.is_listen_target=1


#------------------------------------------------在list范围内就可以开问具体thing,不是thing问是不是人------------------------------------------------------------
		if msg.data.find('jack')>-1 and self.if_locpub==1 and self.if_locpub_right==1 and self.is_listen_target==1 and self.is_listen_thing==0 and self.step==0:
			if msg.data.find('ok-very-good') > -1:					
				#如果语句中有物品出现
				msg.data=""
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.candidate_target=self.thing_in_sentence[self.find_thing_num]
				self.candidate_action="take"
				self.soundhandle.say("so should I go there",self.voice)
				rospy.sleep(3)
				self.soundhandle.say("and take a",self.voice)
			        rospy.sleep(2)
				self.soundhandle.say(self.thing_in_sentence[self.find_thing_num],self.voice)
				rospy.sleep(2)
				self.soundhandle.playWave(self.question_start_signal+"/question_start_signal.wav")
				rospy.sleep(1.3)
				os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
				self.confirm_thing=1
				self.find_thing_num=self.find_thing_num+1
				self.is_listen_thing=1
			if msg.data.find('no-good-answer') > -1:
				#如果语句中有人物出现
				msg.data=""
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				if len(self.target_in_sentence)>0:
					self.soundhandle.say("is the person you want in the following list",self.voice)
					rospy.sleep(4)
					self.is_listen_person=0
					for x in self.person_in_sentence:
						self.soundhandle.say(x,self.voice)
						print x
						rospy.sleep(2)
				os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
				rospy.sleep(2)
				self.is_listen_thing=-1
#------------------------------------------------在list范围内就可以开问具体person------------------------------------------------------------
		if msg.data.find('jack')>-1 and self.if_locpub==1 and self.if_locpub_right==1 and self.is_listen_person==0 and self.is_listen_thing==-1 and self.step==0:
			self.soundhandle.say("ha ha ha ha ha",self.voice)
			rospy.sleep(3)
			if msg.data.find('ok-very-good') > -1:					
				#如果语句中有人物出现
				self.soundhandle.say("xi xi xi xi xi",self.voice)
				rospy.sleep(3)
				msg.data=""
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.candidate_target=self.person_in_sentence[self.find_person_num]
				self.soundhandle.say("one one one",self.voice)
				rospy.sleep(3)
				self.candidate_action="find"
				self.soundhandle.say("so should I go there",self.voice)
				rospy.sleep(3)
				self.soundhandle.say("and find",self.voice)
			        rospy.sleep(2)
				self.soundhandle.say(self.person_in_sentence[self.find_person_num],self.voice)
				rospy.sleep(2)
				self.soundhandle.playWave(self.question_start_signal+"/question_start_signal.wav")
				rospy.sleep(1.3)
				os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
				self.soundhandle.say("two two two",self.voice)
				rospy.sleep(3)
				self.confirm_person=1
				self.find_person_num=self.find_person_num+1
				self.is_listen_person=1
			if msg.data.find('no-good-answer') > -1:
				if msg.data.find('no-good-answer') > -1:
					self.soundhandle.say("four four four",self.voice)
					rospy.sleep(3)
					#如果语句中有answer some questions出现
					msg.data=""
					os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
					if "answer-some-questions" in self.target_in_sentence or "answer-some-question" in self.target_in_sentence:
						self.candidate_target="some questions"
						self.candidate_action="answer"
						self.soundhandle.say("so should I go there to answer some questions",self.voice)
						rospy.sleep(4)
						os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
						self.is_listen_person=-1
						self.is_answer_question=1
					
					

#-------------------------------------------------------看看物体识别的对不对----------------------------------------------------------------
		if msg.data.find('jack')>-1 and self.if_locpub_right==1 and self.confirm_thing==1 and self.is_listen_thing==1 and self.step==0:
			#---------------------------------------物体也正确的话发消息--------------------------------------			
			if msg.data.find('ok-very-good') > -1:
				msg.data=""
				self.target_action = self.candidate_action
				self.target_target = self.candidate_target
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say("ok I will go to",self.voice)
                                rospy.sleep(3.5)
				self.soundhandle.say(self.target_place,self.voice)
				rospy.sleep(2)
				self.soundhandle.say(self.target_action,self.voice)
				rospy.sleep(1)
				self.soundhandle.say(self.target_target,self.voice)
				rospy.sleep(2)
				#这里给navigation发topic
				self.loc_pub.publish(self.target_place)
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
#-------------------------------------------------------看看人物识别的对不对----------------------------------------------------------------
		if msg.data.find('jack')>-1 and self.if_locpub_right==1 and self.confirm_person==1 and self.is_listen_person==1 and self.step==0:
			#---------------------------------------人物也正确的话发消息--------------------------------------			
			if msg.data.find('ok-very-good') > -1:
				msg.data=""
				self.target_action = self.candidate_action
				self.target_target = self.candidate_target
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say("ok I will go to",self.voice)
                                rospy.sleep(3.5)
				self.soundhandle.say(self.target_place,self.voice)
				rospy.sleep(2)
				self.soundhandle.say(self.target_action,self.voice)
				rospy.sleep(1)
				self.soundhandle.say(self.target_target,self.voice)
				rospy.sleep(2)
				#这里给navigation发topic
				self.loc_pub.publish(self.target_place)
				os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
			if msg.data.find('no-good-answer') > -1:
				msg.data=""
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				if len(self.thing_in_sentence)>self.find_thing_num:
					self.candidate_target=self.thing_in_sentence[self.find_thing_num]
					self.candidate_action="find"
					self.soundhandle.say("so should I go there",self.voice)
					rospy.sleep(3)
					self.soundhandle.say("and find",self.voice)
				        rospy.sleep(2)
					self.soundhandle.say(self.candidate_target,self.voice)
					rospy.sleep(2)
					self.soundhandle.playWave(self.question_start_signal+"/question_start_signal.wav")
					rospy.sleep(1.3)
					os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
					self.confirm_person=1
					self.find_person_num=self.find_person_num+1

#-------------------------------------------------------看看是不是过去回答问题----------------------------------------------------------------
		if msg.data.find('jack')>-1 and self.if_locpub_right==1 and self.is_answer_question==1 and self.step==0:
			#---------------------------------------正确的话发消息--------------------------------------			
			if msg.data.find('ok-very-good') > -1:
				msg.data=""
				self.target_action = self.candidate_action
				self.target_target = self.candidate_target
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say("ok I will go to",self.voice)
                                rospy.sleep(3.5)
				self.soundhandle.say(self.target_place,self.voice)
				rospy.sleep(2)
				self.soundhandle.say(self.target_action,self.voice)
				rospy.sleep(1)
				self.soundhandle.say(self.target_target,self.voice)
				rospy.sleep(2)
				#这里给navigation发topic
				self.loc_pub.publish(self.target_place)
				os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")



















#-------------------------------second step--------------------------------------------------------------------------------------------
#------------------------------这个if用来确认完地点正确后询问动作------------------------------------------
		if self.if_locpub==1 and self.if_locpub_right==0 and self.step==1:
			msg.data=""	
			os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
			self.soundhandle.say("should I go there to take something",self.voice)
                        rospy.sleep(5.5)
			self.soundhandle.playWave(self.question_start_signal+"/question_start_signal.wav")
			rospy.sleep(1.3)
			os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
                        self.if_locpub_right=1
			self.if_listen_action=1
#------------------------------这个if用来确认完动作后询问对象----------------------------------------------
                if msg.data.find('jack')>-1 and self.if_locpub_right==1 and self.if_listen_action==1 and self.if_action_right==0 and self.step==1:
			if msg.data.find('ok-very-good') > -1:	
				msg.data=""              
				self.target_action = "take"	
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say("ok I will go there to take something",self.voice)
                                rospy.sleep(5.5)
				self.soundhandle.say("is it edible",self.voice)
                                rospy.sleep(3.5)
				self.soundhandle.playWave(self.question_start_signal+"/question_start_signal.wav")
				rospy.sleep(1.3)
				os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
                                self.if_action_right=1
				self.if_listen_thing=1
#-----------------------------这个if用来确认对象并确认三个target----------------------------------
                if msg.data.find('jack')>-1 and self.if_action_right==1 and self.if_listen_thing==1 and self.if_thing_right==0 and self.step==1:
			if self.is_it_edible==0:
				if msg.data.find('ok-very-good') > -1:	
					self.is_it_edible=1
					msg.data=""
					os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
					self.soundhandle.say("is it solid",self.voice)
		                        rospy.sleep(3.5)
					self.soundhandle.playWave(self.question_start_signal+"/question_start_signal.wav")
					rospy.sleep(1.3)
					os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
				if msg.data.find('no-good-answer') > -1:	
					self.is_it_edible==-1
					msg.data=""
			#进入1分支
			if self.is_it_edible==1:
				if self.is_it_solid==0:
					if msg.data.find('ok-very-good') > -1:	
						self.is_it_solid=1
						msg.data=""
						os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
						self.soundhandle.say("is it a snack",self.voice)
				                rospy.sleep(3.5)
						self.soundhandle.playWave(self.question_start_signal+"/question_start_signal.wav")
						rospy.sleep(1.3)
						os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
					#进入10分支
					if msg.data.find('no-good-answer') > -1:	
						self.is_it_solid=-1
						msg.data=""
						os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
						self.soundhandle.say("is it a snack",self.voice)
				                rospy.sleep(3.5)
						self.soundhandle.playWave(self.question_start_signal+"/question_start_signal.wav")
						rospy.sleep(1.3)
						os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
				#进入11分支
				if self.is_it_solid==1:
					if self.is_it_snack==0:
						if msg.data.find('ok-very-good') > -1:	
							self.is_it_snack=1
							msg.data=""
							os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
							self.soundhandle.say("is it sweet",self.voice)
						        rospy.sleep(3.5)
							self.soundhandle.playWave(self.question_start_signal+"/question_start_signal.wav")
							rospy.sleep(1.3)
							os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
					#进入111分支
					if self.is_it_snack==1:
						if self.is_it_sweet==0:
							if msg.data.find('ok-very-good') > -1:	
								self.is_it_sweet=1
								msg.data=""
								os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
								self.soundhandle.say("is it",self.voice)
								rospy.sleep(1)
								self.soundhandle.say(self.thing1111[self.thing1111_num%3],self.voice)
								self.thing1111_num=self.thing1111_num+1
								rospy.sleep(3.5)
								self.soundhandle.playWave(self.question_start_signal+"/question_start_signal.wav")
								rospy.sleep(1.3)
								os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
							if msg.data.find('no-good-answer') > -1:	
								self.is_it_sweet=-1
								msg.data=""
								os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
								self.soundhandle.say("is it",self.voice)
								rospy.sleep(1)
								self.soundhandle.say(self.thing1110[self.thing1110_num%3],self.voice)
								self.thing1110_num=self.thing1110_num+1
								rospy.sleep(3.5)
								self.soundhandle.playWave(self.question_start_signal+"/question_start_signal.wav")
								rospy.sleep(1.3)
								os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
						#进入1111分支
						if self.is_it_sweet==1:
							if msg.data.find('ok-very-good') > -1:	
								msg.data=""
								self.target_target = self.thing1111[(self.thing1111_num-1)%3]	
								os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
								self.soundhandle.say("so should I go to",self.voice)
								rospy.sleep(3.5)
								self.soundhandle.say(self.target_place,self.voice)
								rospy.sleep(2)
								self.soundhandle.say(self.target_action,self.voice)
								rospy.sleep(1)
								self.soundhandle.say(self.target_target,self.voice)
								rospy.sleep(2)
								self.soundhandle.playWave(self.question_start_signal+"/question_start_signal.wav")
								rospy.sleep(1.3)
								os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
								self.if_thing_right=1
								self.if_confirm=1
							if msg.data.find('no-good-answer') > -1:	
								msg.data=""
								os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
								self.soundhandle.say("is it",self.voice)
								rospy.sleep(1)
								self.soundhandle.say(self.thing1111[self.thing1111_num%3],self.voice)
								self.thing1111_num=self.thing1111_num+1
								rospy.sleep(3.5)
								self.soundhandle.playWave(self.question_start_signal+"/question_start_signal.wav")
								rospy.sleep(1.3)
								os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
						#进入1110分支
						if self.is_it_sweet==-1:
							if msg.data.find('ok-very-good') > -1:	
								msg.data=""
								self.target_target = self.thing1110[(self.thing1110_num-1)%3]	
								os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
								self.soundhandle.say("so should I go to",self.voice)
								rospy.sleep(3.5)
								self.soundhandle.say(self.target_place,self.voice)
								rospy.sleep(2)
								self.soundhandle.say(self.target_action,self.voice)
								rospy.sleep(1)
								self.soundhandle.say(self.target_target,self.voice)
								rospy.sleep(2)
								self.soundhandle.playWave(self.question_start_signal+"/question_start_signal.wav")
								rospy.sleep(1.3)
								os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
								self.if_thing_right=1
								self.if_confirm=1
							if msg.data.find('no-good-answer') > -1:	
								msg.data=""
								os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
								self.soundhandle.say("is it",self.voice)
								rospy.sleep(1)
								self.soundhandle.say(self.thing1110[self.thing1110_num%3],self.voice)
								self.thing1110_num=self.thing1110_num+1
								rospy.sleep(3.5)
								self.soundhandle.playWave(self.question_start_signal+"/question_start_signal.wav")
								rospy.sleep(1.3)
								os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
					#进入110分支
					if self.is_it_snack==-1:
						if self.is_it_vegetable==0:
							if msg.data.find('ok-very-good') > -1:	
								self.is_it_vegetable=1
								msg.data=""
								os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
								self.soundhandle.say("is it",self.voice)
								rospy.sleep(1)
								self.soundhandle.say(self.thing1111[self.thing1111_num%3],self.voice)
								self.thing1111_num=self.thing1111_num+1
								rospy.sleep(3.5)
								self.soundhandle.playWave(self.question_start_signal+"/question_start_signal.wav")
								rospy.sleep(1.3)
								os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
							if msg.data.find('no-good-answer') > -1:	
								self.is_it_vegetable=-1
								msg.data=""
								os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
								self.soundhandle.say("is it",self.voice)
								rospy.sleep(1)
								self.soundhandle.say(self.thing1110[self.thing1110_num%3],self.voice)
								self.thing1110_num=self.thing1110_num+1
								rospy.sleep(3.5)
								self.soundhandle.playWave(self.question_start_signal+"/question_start_signal.wav")
								rospy.sleep(1.3)
								os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
						#进入1101分支
						if self.is_it_vegetable==1:
							if msg.data.find('ok-very-good') > -1:	
								msg.data=""
								self.target_target = self.thing1101[(self.thing1111_num-1)%3]	
								os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
								self.soundhandle.say("so should I go to",self.voice)
								rospy.sleep(3.5)
								self.soundhandle.say(self.target_place,self.voice)
								rospy.sleep(2)
								self.soundhandle.say(self.target_action,self.voice)
								rospy.sleep(1)
								self.soundhandle.say(self.target_target,self.voice)
								rospy.sleep(2)
								self.soundhandle.playWave(self.question_start_signal+"/question_start_signal.wav")
								rospy.sleep(1.3)
								os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
								self.if_thing_right=1
								self.if_confirm=1
							if msg.data.find('no-good-answer') > -1:	
								msg.data=""
								os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
								self.soundhandle.say("is it",self.voice)
								rospy.sleep(1)
								self.soundhandle.say(self.thing1101[self.thing1101_num%3],self.voice)
								self.thing1101_num=self.thing1101_num+1
								rospy.sleep(3.5)
								self.soundhandle.playWave(self.question_start_signal+"/question_start_signal.wav")
								rospy.sleep(1.3)
								os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
						#进入1100分支
						if self.is_it_vegetable==-1:
							if msg.data.find('ok-very-good') > -1:	
								msg.data=""
								self.target_target = self.thing1100[(self.thing1100_num-1)%3]	
								os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
								self.soundhandle.say("so should I go to",self.voice)
								rospy.sleep(3.5)
								self.soundhandle.say(self.target_place,self.voice)
								rospy.sleep(2)
								self.soundhandle.say(self.target_action,self.voice)
								rospy.sleep(1)
								self.soundhandle.say(self.target_target,self.voice)
								rospy.sleep(2)
								self.soundhandle.playWave(self.question_start_signal+"/question_start_signal.wav")
								rospy.sleep(1.3)
								os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
								self.if_thing_right=1
								self.if_confirm=1
							if msg.data.find('no-good-answer') > -1:	
								msg.data=""
								os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
								self.soundhandle.say("is it",self.voice)
								rospy.sleep(1)
								self.soundhandle.say(self.thing1100[self.thing1100_num%3],self.voice)
								self.thing1100_num=self.thing1100_num+1
								rospy.sleep(3.5)
								self.soundhandle.playWave(self.question_start_signal+"/question_start_signal.wav")
								rospy.sleep(1.3)
								os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
				#进入10分支
				if self.is_it_solid==-1:
					if msg.data.find('ok-very-good') > -1:	
						msg.data=""
						self.target_target = self.thing10[(self.thing10_num-1)%4]	
						os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
						self.soundhandle.say("so should I go to",self.voice)
						rospy.sleep(3.5)
						self.soundhandle.say(self.target_place,self.voice)
						rospy.sleep(2)
						self.soundhandle.say(self.target_action,self.voice)
						rospy.sleep(1)
						self.soundhandle.say(self.target_target,self.voice)
						rospy.sleep(2)
						self.soundhandle.playWave(self.question_start_signal+"/question_start_signal.wav")
						rospy.sleep(1.3)
						#os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
						self.if_thing_right=1
						self.if_confirm=1
					if msg.data.find('no-good-answer') > -1:	
						msg.data=""
						os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
						self.soundhandle.say("is it",self.voice)
						rospy.sleep(1)
						self.soundhandle.say(self.thing10[self.thing10_num%4],self.voice)
						self.thing10_num=self.thing10_num+1
						rospy.sleep(3.5)
						self.soundhandle.playWave(self.question_start_signal+"/question_start_signal.wav")
						rospy.sleep(1.3)
						os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
					
		
#-----------------------------这个if用来确认所有以后发出topic----------------------------------
                if msg.data.find('jack')>-1 and self.if_thing_right==1 and self.if_confirm==1 and self.step==1:
			if msg.data.find('ok-very-good') > -1:	
				msg.data=""
				os.system("/home/kamerider/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say("ok I will go to",self.voice)
                                rospy.sleep(3.5)
				self.soundhandle.say(self.target_place,self.voice)
				rospy.sleep(2)
				self.soundhandle.say(self.target_action,self.voice)
				rospy.sleep(1)
				self.soundhandle.say(self.target_target,self.voice)
				rospy.sleep(2)
				#这里给navigation发topic
				#self.loc_pub.publish(self.target_place)
				os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
#------------------------------这里开始是语音用来回答问题的部分-----------------------------------
		if self.if_now_answer==1:
			self.sentence_as_array=msg.data.split('-')
			self.sentence=msg.data.replace('-',' ')
			print self.sentence
			#object
			if msg.data.find('which-city-are-we-in')>-1:
				os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say('I heared which city are we in ', self.voice)
				rospy.sleep(4)
				self.soundhandle.say('the answer is Nagoya', self.voice)
				rospy.sleep(4)
				self.soundhandle.say('OK I am ready for next question', self.voice)
				rospy.sleep(4)
				os.system("~/catkin_ws/src/speech/run_pocketsphinx_answer_questions.sh")
				self.soundhandle.playWave(self.question_start_signal + "/question_start_signal.wav")
				rospy.sleep(4)
				print('Nagoya')
			elif msg.data.find('what-is-the-name-of-your-team')>-1:
				os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say('I heared what is the name of your team', self.voice)
				rospy.sleep(4)
				self.soundhandle.say('the answer is our team name is kamerider ', self.voice)
				rospy.sleep(4)
				self.soundhandle.say('OK I am ready for next question', self.voice)
				rospy.sleep(4)
				os.system("~/catkin_ws/src/speech/run_pocketsphinx_answer_questions.sh")
				self.soundhandle.playWave(self.question_start_signal + "/question_start_signal.wav")
				rospy.sleep(4)
				print('our team name is kamerider')
			elif msg.data.find('you-can-go-back-to-do-the-next-thing')>-1:
				os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say('ok I will go back now', self.voice)
				rospy.sleep(5)
				self.soundhandle.say('byebye', self.voice)
				rospy.sleep(2)
				#发布回程消息
				self.loc_pub.publish("start")
				self.if_if_now_answer=0
				self.if_backToStart=1
				os.system("~/catkin_ws/src/speech/run_pocketsphinx.sh")
#--------------------------------------------------------------------------------------------------
		else :
			return
	def askhelp(self,msg):
		msg.data=msg.data.lower()
		if msg.data=="found_person":
			os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
			self.soundhandle.say(" new operator ",self.voice)
			rospy.sleep(1.5)
			self.soundhandle.say(" i have reached the person ",self.voice)
			rospy.sleep(3)
			self.soundhandle.say('ok I will go back now', self.voice)
			rospy.sleep(3)
			self.soundhandle.say('byebye', self.voice)
			rospy.sleep(2)
			
			self.loc_pub.publish("start")
			self.if_if_now_answer=0
			self.if_backToStart=1
			os.system("~/catkin_ws/src/speech/run_pocketsphinx.sh")
	def reachdst_callback(self,msg):
		msg.data=msg.data.lower()
		#到达operator指定的目的地
		if msg.data=="arrive_target_place" and self.if_backToStart==0:
			self.soundhandle.say("now I arrived",self.voice)
			self.soundhandle.say(self.target_place,self.voice)
			rospy.sleep(3.5)
			self.soundhandle.say("then I will",self.voice)
			rospy.sleep(1)
			self.soundhandle.say(self.target_action,self.voice)
			rospy.sleep(1)
			self.soundhandle.say(self.target_target,self.voice)
			rospy.sleep(3.5)
			#如果是去拿一个东西
			if self.target_action == "take":
				self.soundhandle.say("now I have arrive the target",self.voice)
				rospy.sleep(3)
				self.soundhandle.say("now I have find",self.voice)
				rospy.sleep(3)
				self.soundhandle.say(self.target_target,self.voice)
				rospy.sleep(1)
				self.soundhandle.say("I will go back to the start place",self.voice)
				rospy.sleep(5)
				self.loc_pub.publish("start")
			#如果是去找一个人
			if self.target_action == "find":
				self.soundhandle.say("now I have arrive the target",self.voice)
				rospy.sleep(3)
				self.soundhandle.say("now I have find",self.voice)
				rospy.sleep(3)
				self.soundhandle.say(self.target_target,self.voice)
				rospy.sleep(1)
				self.soundhandle.say("I will go back to the start place",self.voice)
				rospy.sleep(5)
				self.loc_pub.publish("start")
			#如果是去回答一个问题
			if self.target_action == "answer":
				self.soundhandle.say("now I have arrive the target",self.voice)
				rospy.sleep(3)
				self.soundhandle.say("now I have finish the action",self.voice)
				rospy.sleep(1)
				self.soundhandle.say("I will go back to the start place",self.voice)
				rospy.sleep(1)
				self.loc_pub.publish("start")				
				os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx_answer_questions.sh")
		#回到初始地
		if msg.data=="arrive_target_place" and self.if_backToStart==1:
			#初始化所有的flag开始新的一轮
			self.if_locpub=0
			self.if_locpub_right=0
			self.if_listen_action=0
		        self.if_action_right=0
			self.if_listen_thing=0
		        self.if_thing_right=0
		        self.if_confirm=0

			self.if_now_answer=0

			self.is_it_edible=0
			self.is_it_solid=0
			self.is_it_snack=0
			self.is_it_sweet=0

			self.candidate_loc=""
			self.target_place = ""
			self.target_action = ""
			self.target_target = ""


			self.location_num=0
			self.thing1111_num=0
			elf.thing1110_num=0
			self.soundhandle.say("now I am ready for next turn",self.voice)
			os.system("/home/kamerider/catkin_ws/src/speech/run_pocketsphinx.sh")
			
			

	def cleanup(self):
		rospy.loginfo("shuting down navsp node ....")


if __name__=="__main__":
	rospy.init_node('gpsr')
	try:
		gpsr()
		rospy.spin()
	except:
		pass
