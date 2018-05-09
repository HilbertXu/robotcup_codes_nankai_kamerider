#!/usr/bin/env python
# -*- coding: utf-8 -*-


"""
    play riddle game
"""

import roslib; roslib.load_manifest('speech')
import rospy
import re
import os
from std_msgs.msg import String
from std_msgs.msg import Int8
import time
from sound_play.libsoundplay import SoundClient
import xml.etree.ElementTree as ET
f=open('/home/kamerider/catkin_ws/src/speech/save.txt','w')
womannumber= 0
mannumber= 0
class spr:
	def __init__(self):

		rospy.on_shutdown(self.cleanup)
		self.voice = rospy.get_param("~voice", "voice_cmu_us_rms_cg_clunits")
		self.question_start_signal = rospy.get_param("~question_start_signal", "")



		self.if_say=0
		#for crowd question
		self.appl=['children','adults','elders']
		self.gppl=['females','males','women','men','boys','girls']
		self.people=self.appl+self.gppl
		self.posprs=['standing','sitting','lying']
		self.posppl=['standing','sitting','lying','standing or sitting','standing or lying','sitting or lying']
		self.gesture=['waving','rising left arm','rising right arm','pointing left','pointing right']
		self.gprsng=['male or female','man or woman','boy or girl']
		self.gprsn=['female','male','woman','man','boy','girl']
		self.w=0

		self.female_num=0
		self.male_num=0
		self.crowd_num=0
		self.sit_num=0
		self.stand_num=0
		self.sit_man_num=0
		self.sit_female_num=0
		self.stand_man_num=0
		self.stand_female_num=0
		

		#for object question
		#read object.xml
		self.adja=['heaviest','smallest','biggest','lightest']
		self.adjr=['heavier','smaller','bigger','lighter']
		self.size_order = (
			'mixed-nuts', 'food', 'fork', 'cutlery', 'spoon', 'cutlery',
			'knife', 'cutlery','canned-fish', 'food', 'cup', 'container', 
			'orange-juice', 'drink', 'pringles', 'snack', 'cereal', 'food', 
			'apple-juice', 'drink','milk-tea', 'drink','jelly', 'snack', 
			'milk-biscuit', 'snack', 'root-beer', 'drink', 'potato-chip', 'snack',
			'instant-noodle', 'food', 'green-tea', 'drink','disk','container',
			'cereal-bowl','container','tray','container','shopping-bag','container')
		self.weight_order1= (
            'cup','container',               'cereal-bowl','container',
            'disk','container',           'tray','container',
	    'mixed nuts','food',
	    'potato-chip', 'snack',    'shopping-bag','container',
            'cereal','food',          'instant-noodle','food',
            'milk-biscuit', 'snack',          'pringles','snack',
            'fork', 'cutlery',          'spoon', 'cutlery',
            'knife','cutlery',         'canned-fish','food',
            'apple-juice','drink',   'orange-juice', 'drink',
            'milk-tea', 'drink',          'root-bear','drink',
            'jelly', 'snack',    'green-tea', 'drink')		


		self.weight_order= (
            'cup','the top of the shelf',               'cereal-bowl','the top of the shelf',
            'disk','the top of the shelf',           'tray','the top of the shelf',
	    'mixed nuts','kitchen-table',
	    'potato-chip', 'coffee-table',    'shopping-bag','the top of the shelf',
            'cereal','kitchen-table',          'instant-noodle','kitchen-table',
            'milk-biscuit', 'coffee-table',          'pringles','coffee-table',
            'fork', 'the top of the shelf',          'spoon', 'the top of the shelf',
            'knife','the top of the shelf',         'canned-fish','kitchen-table',
            'apple-juice','bar-table',   'orange-juice', 'bar-table',
            'milk-tea', 'bar-table',          'root-bear','bar-table',
            'jelly', 'coffee-table',    'green-tea', 'bar-table','cutlery','the top of the shelf', 'container','the top of the shelf','food','kitchen-table','snack','bar-table','drink','bar-table')
		self.category = ('container', '5', 'cutlery', '3', 'drink', '5', 'food', '4', 'snack', '4')
		

		self.object_colour = ( 'cup','green red and orange',               'cereal-bowl','red',
		'mixed-nuts','white',
            'disk','blue',         'tray','purple',
	    'potato-chip', 'yellow',    'shopping-bag','red and white',
            'cereal','red and blue',          'instant-noodle','yellow',
            'milk-biscuit', 'blue and red',          'pringles','green and red',
            'fork', 'silver',          'spoon', 'silver',
            'knife','silver',         'canned-fish','red and white',
            'apple-juice','red',   'orange-juice', 'white and greed',
            'milk-tea', 'blue and black',          'root-bear','brown',
            'jelly', 'red and pink',    'green-tea', 'greed')
		









		self.location=('small shelf','living-room','sofa','living-room','coffee-table','living-room',
					   'arm-chair-a','living-room','arm-chair-b','living-room','kitchen-rack','kitchen','kitchen-table','kitchen',
					   'kitchen shelf','kitchen','kitchen-counter','kitchen','fridge','kitchen',
					   'chair','dining-room','dining-table-a','dining-room','little table','dining-room',
					   'right planks','balcony','balcony-shelf','balcony','entrance-shelf','entrance',
					   'bar-table','dining-room','dining-table-b','dining-room','shelf','dining-room')
		self.doornum=('living-room','2','kitchen','1','dining-room','1','hallway','1')
		self.thingnum=('2','arm-chair','living-room','6','chair','dining-room','2','dining-table','dining-room',
				'1','kitchen tack','kitchen','1','kitchen-table','kitchen',
				'1','small shelf','living-room','1','sofa','living-room','1','coffee-table','living-room',
				'1','little table','dining-room','1','bar-table','dining-room','1','shelf','dining-room')


		# Create the sound client object
		self.soundhandle = SoundClient() 
		rospy.sleep(1)
		self.riddle_turn = rospy.Publisher('turn_signal', String, queue_size=15)
		self.soundhandle.stopAll()
		self.soundhandle.say('hello I want to play riddles',self.voice)
		rospy.sleep(3)
		self.soundhandle.say('I will turn back after ten seconds',self.voice)
		rospy.sleep(3)
		self.soundhandle.say('ten',self.voice)
		rospy.sleep(1)
		self.soundhandle.say('nine',self.voice)
		self.riddle_turn.publish("turn_robot")#publish msg to nav
		rospy.sleep(1)
		self.soundhandle.say('eight',self.voice)
		rospy.sleep(1)
		self.soundhandle.say('seven',self.voice)
		rospy.sleep(1)
		self.soundhandle.say('six',self.voice)
		rospy.sleep(1)
		self.soundhandle.say('five',self.voice)
		rospy.sleep(1)
		self.soundhandle.say('four',self.voice)
		rospy.sleep(1)
		self.soundhandle.say('three',self.voice)
		rospy.sleep(1)
		self.soundhandle.say('two',self.voice)
		rospy.sleep(1)
		self.soundhandle.say('one',self.voice)
		rospy.sleep(1)
		self.soundhandle.say('here I come',self.voice)
		rospy.sleep(1)
		rospy.Subscriber('human_num', String, self.h_num)
		rospy.Subscriber('female_num', String, self.f_num)
		rospy.Subscriber('male_num', String, self.m_num)
		rospy.Subscriber('sit_num', String, self.sit_num)
		rospy.Subscriber('stand_num', String, self.stand_num)
		rospy.Subscriber('stand_male_num', String, self.sit_man_num)
		rospy.Subscriber('stand_female_num', String, self.sit_female_num)
		rospy.Subscriber('sit_male_num', String, self.stand_man_num)
		rospy.Subscriber('stand_female_num', String, self.stand_female_num)


		rospy.Subscriber('taking_photo_signal', String, self.remind_people)
		if self.if_say==0:
			rospy.Subscriber('recognizer_output', String, self.talk_back)
	def sit_num(self,msg):
		msg.data=msg.data.lower()
		self.sit_num=msg.data

	def stand_num(self,msg):
		msg.data=msg.data.lower()
		self.stand_num=msg.data

	def sit_man_num(self,msg):
		msg.data=msg.data.lower()
		self.sit_man_num=msg.data
	def sit_female_num(self,msg):
		msg.data=msg.data.lower()
		self.sit_female_num=msg.data
	def stand_man_num(self,msg):
		msg.data=msg.data.lower()
		self.stand_man_num=msg.data
	def stand_female_num(self,msg):
		msg.data=msg.data.lower()
		self.stand_female_num=msg.data

	def h_num(self,msg):
		msg.data=msg.data.lower()
		self.soundhandle.say('I have already taken the photo',self.voice)
		rospy.sleep(3)
		self.soundhandle.say('please wait for a moment',self.voice)
		rospy.sleep(3)
		self.crowd_num=msg.data
		print "human number is " + msg.data
		self.soundhandle.say('human number is  '+msg.data,self.voice)
		rospy.sleep(4)

	def f_num(self,msg):
		msg.data=msg.data.lower()
                womannumber= msg.data
		print "female number is " + msg.data
		self.female_num=msg.data
		self.soundhandle.say('female number is  '+msg.data,self.voice)
		rospy.sleep(4)

	def m_num(self,msg):
		msg.data=msg.data.lower()
		print "male number is " + msg.data
                mannumber= msg.data
		self.male_num=msg.data
		self.soundhandle.say('male number is ' +msg.data,self.voice)
		rospy.sleep(4)
		self.soundhandle.say('who wants to play riddles with me',self.voice)
		rospy.sleep(3.5)
		self.soundhandle.say('please stand in front of me and wait for five seconds',self.voice)
		rospy.sleep(8.5)
		self.soundhandle.say('please ask me after you hear',self.voice)
		rospy.sleep(2.5)
		self.soundhandle.playWave(self.question_start_signal+"/question_start_signal.wav")
		rospy.sleep(1.3)
		self.soundhandle.say('Im ready',self.voice)
		rospy.sleep(1.3)
		self.soundhandle.playWave(self.question_start_signal+"/question_start_signal.wav")
		rospy.sleep(1.3)
		self.w=1

	def answer_How_many_people_are_in_the_crowd(self,msg):
		msg.data=msg.data.lower()
		self.soundhandle.say('the answer is there are '+msg.data+' in the crowd',self.voice)
		rospy.sleep(3.5)
		self.soundhandle.say('OK I am ready for next question', self.voice)
		rospy.sleep(2)
		self.soundhandle.playWave(self.question_start_signal + "/question_start_signal.wav")
		rospy.sleep(1.2)

	def remind_people(self, msg):
		msg.data = msg.data.lower()
		self.turn_end = rospy.Publisher('turn_end', String, queue_size=15)
		if msg.data=='start':
			self.soundhandle.say('Im going to take a photo',self.voice)
			rospy.sleep(3)
			self.soundhandle.say('please look at me and smile',self.voice)
			rospy.sleep(3)
			self.soundhandle.say('three',self.voice)
			rospy.sleep(1)
			self.soundhandle.say('two',self.voice)
			rospy.sleep(1)
			self.soundhandle.say('one',self.voice)
			rospy.sleep(1)
			self.turn_end.publish("in_position")

	def talk_back(self, msg):
		msg.data = msg.data.lower()
		print msg.data
		if self.w==1 :
			self.sentence_as_array=msg.data.split('-')
			self.sentence=msg.data.replace('-',' ')
			print self.sentence
			#object
			if msg.data.find('where-are-we')>-1:
				os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say('where-are-we', self.voice)
				rospy.sleep(4)
				self.soundhandle.say('the answer is Japan', self.voice)
				rospy.sleep(4)
				self.soundhandle.say('OK I am ready for next question', self.voice)
				rospy.sleep(4)
				os.system("~/catkin_ws/src/speech/run_pocketsphinx.sh")
				self.soundhandle.playWave(self.question_start_signal + "/question_start_signal.wav")
				rospy.sleep(4)
                                print "where-are-we"
				print "Japan"
			elif msg.data.find('how-many-teams-are-there')>-1:
				os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say('I heared how-many-teams-are-there', self.voice)
				rospy.sleep(4)
				self.soundhandle.say('the answer is five', self.voice)
				rospy.sleep(4)
				self.soundhandle.say('OK I am ready for next question', self.voice)
				rospy.sleep(4)
				os.system("~/catkin_ws/src/speech/run_pocketsphinx.sh")
				self.soundhandle.playWave(self.question_start_signal + "/question_start_signal.wav")
				rospy.sleep(4)
                                print "how-many-teams-are-there"
				print "5"
			elif msg.data.find('participants-come-from')>-1 or msg.data.find('how-many-countries')>-1:
				os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say('I heared how-many-countries-the-participants-come-from', self.voice)
				rospy.sleep(4)
				self.soundhandle.say('the answer is three', self.voice)
				rospy.sleep(4)
				self.soundhandle.say('OK I am ready for next question', self.voice)
				rospy.sleep(4)
				os.system("~/catkin_ws/src/speech/run_pocketsphinx.sh")
				self.soundhandle.playWave(self.question_start_signal + "/question_start_signal.wav")
                                print "how-many-countries-the-participants-come-from"
				rospy.sleep(4)
				print "3"
			elif msg.data.find('what-month-is-it-now')>-1:
				os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say('I heared what-month-is-it-now', self.voice)
				rospy.sleep(4)
				self.soundhandle.say('the answer is May', self.voice)
				rospy.sleep(4)
				self.soundhandle.say('OK I am ready for next question', self.voice)
				rospy.sleep(4)
				os.system("~/catkin_ws/src/speech/run_pocketsphinx.sh")
				self.soundhandle.playWave(self.question_start_signal + "/question_start_signal.wav")
				rospy.sleep(4)
                                print "what-month-is-it-now"
				print "May"
			elif msg.data.find('where-are-the-chairs')>-1:
				os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say('I heared where-are-the-chairs', self.voice)
				rospy.sleep(4)
				self.soundhandle.say('the answer is in the living room', self.voice)
				rospy.sleep(4)
				self.soundhandle.say('OK I am ready for next question', self.voice)
				rospy.sleep(4)
				os.system("~/catkin_ws/src/speech/run_pocketsphinx.sh")
				self.soundhandle.playWave(self.question_start_signal + "/question_start_signal.wav")
				rospy.sleep(4)
                                f.write('where-are-the-chairs')
				f.write('living-room')
			elif msg.data.find('how-many-chairs-are-there-in-the-house')>-1:
				os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say('I heared how-many-chairs-are-there-in-the-house', self.voice)
				rospy.sleep(4)
				self.soundhandle.say('the answer is five', self.voice)
				rospy.sleep(4)
				self.soundhandle.say('OK I am ready for next question', self.voice)
				rospy.sleep(4)
				os.system("~/catkin_ws/src/speech/run_pocketsphinx.sh")
				self.soundhandle.playWave(self.question_start_signal + "/question_start_signal.wav")
				rospy.sleep(4)
                                print "how-many-chairs-are-there-in-the-house"
				print "5"
			elif msg.data.find('how-many-woman-are-there')>-1:
				os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say('I heared how-many-woman-are-there', self.voice)
				rospy.sleep(4)
				self.soundhandle.say('the answer is', self.voice)
				rospy.sleep(3)
				self.soundhandle.say(str(self.female_num), self.voice)
				rospy.sleep(1)
				self.soundhandle.say('OK I am ready for next question', self.voice)
				rospy.sleep(4)
				os.system("~/catkin_ws/src/speech/run_pocketsphinx.sh")
				self.soundhandle.playWave(self.question_start_signal + "/question_start_signal.wav")
				rospy.sleep(4)
                                print "how-many-woman-are-there"
				print self.female_num
			elif msg.data.find('how-many-man-is-standing')>-1:
				os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say('I heared how-many-man-is-standing', self.voice)
				rospy.sleep(4)
				self.soundhandle.say(str(self.stand_man_num), self.voice)
				rospy.sleep(3)
				self.soundhandle.say('OK I am ready for next question', self.voice)
				rospy.sleep(2.5)
				os.system("~/catkin_ws/src/speech/run_pocketsphinx.sh")
				self.soundhandle.playWave(self.question_start_signal + "/question_start_signal.wav")
				print "how-many-man-is-standing"
				print self.self.stand_man_num
			elif msg.data.find('where-is-the-tea')>-1:
				os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say('I heared where-is-the-tea', self.voice)
				rospy.sleep(4)
				self.soundhandle.say('the answer is on the table', self.voice)
				rospy.sleep(3)
				self.soundhandle.say('OK I am ready for next question', self.voice)
				rospy.sleep(2.5)
				os.system("~/catkin_ws/src/speech/run_pocketsphinx.sh")
				self.soundhandle.playWave(self.question_start_signal + "/question_start_signal.wav")
                                print "I heared where-is-the-tea"
                                print "on the table"
			elif msg.data.find('what-is-next-to-the-tea')>-1:
				os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say('I heared what-is-next-to-the-tea', self.voice)
				rospy.sleep(4)
				self.soundhandle.say('the answer is milk', self.voice)
				rospy.sleep(3)
				self.soundhandle.say('OK I am ready for next question', self.voice)
				rospy.sleep(2.5)
				os.system("~/catkin_ws/src/speech/run_pocketsphinx.sh")
				self.soundhandle.playWave(self.question_start_signal + "/question_start_signal.wav")
                                print "what-is-next-to-the-tea"
                                print "milk"
			elif msg.data.find('what-is-your-team-name')>-1:
				os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say('I heared what-is-your-team-name', self.voice)
				rospy.sleep(4)
				self.soundhandle.say('the answer is kamirider', self.voice)
				rospy.sleep(3)
				self.soundhandle.say('OK I am ready for next question', self.voice)
				rospy.sleep(2.5)
				os.system("~/catkin_ws/src/speech/run_pocketsphinx.sh")
				self.soundhandle.playWave(self.question_start_signal + "/question_start_signal.wav")
                                print "what-is-your-team-name"
                                print "kamirider"
			elif msg.data.find('what-is-your-team-name')>-1:
				os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say('I heared what-is-your-team-name', self.voice)
				rospy.sleep(4)
				self.soundhandle.say('the answer is kamirider', self.voice)
				rospy.sleep(3)
				self.soundhandle.say('OK I am ready for next question', self.voice)
				rospy.sleep(2.5)
				os.system("~/catkin_ws/src/speech/run_pocketsphinx.sh")
				self.soundhandle.playWave(self.question_start_signal + "/question_start_signal.wav")
                                print "what-is-your-team-name"
                                print "kamirider"
			elif msg.data.find('what-is-the-weather-today')>-1:
				os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say('I heared what-is-the-weather-today', self.voice)
				rospy.sleep(4)
				self.soundhandle.say('the answer is sunny', self.voice)
				rospy.sleep(3)
				self.soundhandle.say('OK I am ready for next question', self.voice)
				rospy.sleep(2.5)
				os.system("~/catkin_ws/src/speech/run_pocketsphinx.sh")
				self.soundhandle.playWave(self.question_start_signal + "/question_start_signal.wav")
                                print "what-is-the-weather-today"
                                print "sunny"
			elif msg.data.find('what-is-the-date-today')>-1:
				os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say('I heared what-is-the-date-today', self.voice)
				rospy.sleep(4)
				self.soundhandle.say('the answer is 3th May', self.voice)
				rospy.sleep(3)
				self.soundhandle.say('OK I am ready for next question', self.voice)
				rospy.sleep(2.5)
				os.system("~/catkin_ws/src/speech/run_pocketsphinx.sh")
				self.soundhandle.playWave(self.question_start_signal + "/question_start_signal.wav")
                                print "what-is-the-date-today"
                                print "3th May"
			elif msg.data.find('where-is-the-robotcup-held')>-1:
				os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say('I heared where-is-the-robotcup-held', self.voice)
				rospy.sleep(4)
				self.soundhandle.say('the answer is Ogaki Gifu', self.voice)
				rospy.sleep(3)
				self.soundhandle.say('OK I am ready for next question', self.voice)
				rospy.sleep(2.5)
				os.system("~/catkin_ws/src/speech/run_pocketsphinx.sh")
				self.soundhandle.playWave(self.question_start_signal + "/question_start_signal.wav")
                                print "where-is-the-robotcup-held"
                                print "Ogaki Gifu"
			elif msg.data.find('what-color-is-the-tea')>-1:
				os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say('I heared what-color-is-the-tea', self.voice)
				rospy.sleep(4)
				self.soundhandle.say('the answer is green', self.voice)
				rospy.sleep(3)
				self.soundhandle.say('OK I am ready for next question', self.voice)
				rospy.sleep(2.5)
				os.system("~/catkin_ws/src/speech/run_pocketsphinx.sh")
				self.soundhandle.playWave(self.question_start_signal + "/question_start_signal.wav")
                                print "what-color-is-the-tear"
                                print "green"
			elif msg.data.find('what-is-the-game')>-1:
				os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say('I heared what-is-the-game', self.voice)
				rospy.sleep(4)
				self.soundhandle.say('the answer is robotcup', self.voice)
				rospy.sleep(3)
				self.soundhandle.say('OK I am ready for next question', self.voice)
				rospy.sleep(2.5)
				os.system("~/catkin_ws/src/speech/run_pocketsphinx.sh")
				self.soundhandle.playWave(self.question_start_signal + "/question_start_signal.wav")
                                print "what-is-the-game"
                                print "robotcup"
			elif msg.data.find('how-many-beds-are-there-in-the-bedroom')>-1:
				os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say('I heared what-is-the-game', self.voice)
				rospy.sleep(4)
				self.soundhandle.say('the answer is one', self.voice)
				rospy.sleep(3)
				self.soundhandle.say('OK I am ready for next question', self.voice)
				rospy.sleep(2.5)
				os.system("~/catkin_ws/src/speech/run_pocketsphinx.sh")
				self.soundhandle.playWave(self.question_start_signal + "/question_start_signal.wav")
                                print "how-many-beds-are-there-in-the-bedroom"
                                print "one"
			elif msg.data.find('what-is-the-smallest-country-in-the-world')>-1:
				os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say('I heared what-is-the-smallest-country-in-the-world', self.voice)
				rospy.sleep(4)
				self.soundhandle.say('the answer is Vatican', self.voice)
				rospy.sleep(3)
				self.soundhandle.say('OK I am ready for next question', self.voice)
				rospy.sleep(2.5)
				os.system("~/catkin_ws/src/speech/run_pocketsphinx.sh")
				self.soundhandle.playWave(self.question_start_signal + "/question_start_signal.wav")
                                print "what-is-the-smallest-country-in-the-world"
                                print "Vatican"
			elif msg.data.find('what-is-the-smallest-country-in-the-world')>-1:
				os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say('I heared what-is-the-smallest-country-in-the-world', self.voice)
				rospy.sleep(4)
				self.soundhandle.say('the answer is Vatican', self.voice)
				rospy.sleep(3)
				self.soundhandle.say('OK I am ready for next question', self.voice)
				rospy.sleep(2.5)
				os.system("~/catkin_ws/src/speech/run_pocketsphinx.sh")
				self.soundhandle.playWave(self.question_start_signal + "/question_start_signal.wav")
                                print "what-is-the-smallest-country-in-the-world"
                                print "Vatican"
			elif msg.data.find('where-is-the-next-robotcup-held')>-1:
				os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say('I heared where-is-the-next-robotcup-held', self.voice)
				rospy.sleep(4)
				self.soundhandle.say('the answer is Canada', self.voice)
				rospy.sleep(3)
				self.soundhandle.say('OK I am ready for next question', self.voice)
				rospy.sleep(2.5)
				os.system("~/catkin_ws/src/speech/run_pocketsphinx.sh")
				self.soundhandle.playWave(self.question_start_signal + "/question_start_signal.wav")
                                print "where-is-the-next-robotcup-held"
                                print "Canada"
			elif msg.data.find('is-there-a-woman')>-1:
				os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say('I heared is-there-a-woman', self.voice)
				rospy.sleep(4)
				self.soundhandle.say('the answer is yes', self.voice)
				rospy.sleep(3)
				self.soundhandle.say('OK I am ready for next question', self.voice)
				rospy.sleep(2.5)
				os.system("~/catkin_ws/src/speech/run_pocketsphinx.sh")
				self.soundhandle.playWave(self.question_start_signal + "/question_start_signal.wav")
                                print "is-there-a-woman"
                                print "yes"
			elif msg.data.find('what-color-is-the-dekopon')>-1:
				os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say('I heared what-color-is-the-dekopon', self.voice)
				rospy.sleep(4)
				self.soundhandle.say('the answer is orange', self.voice)
				rospy.sleep(3)
				self.soundhandle.say('OK I am ready for next question', self.voice)
				rospy.sleep(2.5)
				os.system("~/catkin_ws/src/speech/run_pocketsphinx.sh")
				self.soundhandle.playWave(self.question_start_signal + "/question_start_signal.wav")
                                print "what-color-is-the-dekopon"
                                print "orange"
			elif msg.data.find('where-is-kiwi')>-1:
				os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say('I heared where-is-kiwi', self.voice)
				rospy.sleep(4)
				self.soundhandle.say('the answer is in the kitchen', self.voice)
				rospy.sleep(3)
				self.soundhandle.say('OK I am ready for next question', self.voice)
				rospy.sleep(2.5)
				os.system("~/catkin_ws/src/speech/run_pocketsphinx.sh")
				self.soundhandle.playWave(self.question_start_signal + "/question_start_signal.wav")
                                print "where-is-kiwi"
                                print "kitchen"
			elif msg.data.find('what-is-the-highest-mountain-in-japan')>-1:
				os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say('I heared what-is-the-highest-mountain-in-japan', self.voice)
				rospy.sleep(4)
				self.soundhandle.say('the answer is in the Mount Fuji', self.voice)
				rospy.sleep(3)
				self.soundhandle.say('OK I am ready for next question', self.voice)
				rospy.sleep(2.5)
				os.system("~/catkin_ws/src/speech/run_pocketsphinx.sh")
				self.soundhandle.playWave(self.question_start_signal + "/question_start_signal.wav")
                                print "what-is-the-highest-mountain-in-japan"
                                print "Mount Fuji"
			elif msg.data.find('who-is-the-statue-in-the-corridor')>-1:
				os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say('I heared what-is-the-highest-mountain-in-japan', self.voice)
				rospy.sleep(4)
				self.soundhandle.say('the answer is no bu na ka', self.voice)
				rospy.sleep(3)
				self.soundhandle.say('OK I am ready for next question', self.voice)
				rospy.sleep(2.5)
				os.system("~/catkin_ws/src/speech/run_pocketsphinx.sh")
				self.soundhandle.playWave(self.question_start_signal + "/question_start_signal.wav")
                                print "who-is-the-statue-in-the-corridor"
                                print "no bu na ka"
			elif msg.data.find('what-is-the-animal-detected-in-the-biscuit-package')>-1:
				os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say('I heared what-is-the-animal-detected-in-the-biscuit-package', self.voice)
				rospy.sleep(4)
				self.soundhandle.say('the answer is beare', self.voice)
				rospy.sleep(3)
				self.soundhandle.say('OK I am ready for next question', self.voice)
				rospy.sleep(2.5)
				os.system("~/catkin_ws/src/speech/run_pocketsphinx.sh")
				self.soundhandle.playWave(self.question_start_signal + "/question_start_signal.wav")
                                print "what-is-the-animal-detected-in-the-biscuit-package"
                                print "bear"
			else:
				print 2	

		
		
	def cleanup(self):
		rospy.loginfo("Shutting down spr node...")



if __name__=="__main__":
	rospy.init_node('spr')
	try:
		spr()
		rospy.spin()
	except:
		pass




		
