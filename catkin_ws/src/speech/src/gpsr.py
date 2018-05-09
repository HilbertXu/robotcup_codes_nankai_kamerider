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
		self.loc_pub = rospy.Publisher('/voice2bring', String, queue_size=15)
		self.srt_guide = rospy.Publisher('/voice2guide', String, queue_size=15)
		self.inspect = rospy.Publisher('go_out', String, queue_size=15)
		rospy.Subscriber('/nav2speech',String,self.follow_adj)

		rospy.Subscriber('/inspect2speech',String,self.inspect_callback)
		rospy.Subscriber('/emergency2speech',String,self.emergency_callback)		


		self.if_answer=0		
		self.question_num=0
		self.speech2nav_pub=rospy.Publisher('/speech2nav', String, queue_size=15)

		self.www=0
		self.difmsg='null'
		self.if_followme=0
		self.if_stop=0
		self.if_locpub=0
		self.say_time=0
	def follow_adj(self,msg):
		msg.data=msg.data.lower()
		if msg.data=="get_pose":
			self.soundhandle.say("please ask me the first category question",self.voice)
			self.location="start"
			rospy.sleep(3.5)
			rospy.Subscriber('recognizer_output',String,self.follow)

		if self.question_num==3:
			os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
			self.soundhandle.say("i have finished the mission",self.voice)
			rospy.sleep(3)
			self.soundhandle.say("i am going to leave",self.voice)
			rospy.sleep(3)
			self.speech2nav_pub.publish("exit")
		if msg.data.find("arrived") > -1:
			self.question_num+=1
			os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
			self.soundhandle.say("i have finished the mission",self.voice)
			rospy.sleep(3)
			self.soundhandle.say("please ask me the next question",self.voice)
			rospy.sleep(3)
			self.soundhandle.say("i choose the first category question",self.voice)
			os.system("~/catkin_ws/src/speech/run_pocketsphinx_gpsr.sh")
			rospy.sleep(3)

	def emergency_callback(self,msg):
		msg.data=msg.data.lower()
		if msg.data=="true":
			self.state="true"
		else :
			self.state="false"
			self.inspect.publish("false")
			print "2222222222222222222222"
	def follow(self,msg):
		msg.data=msg.data.lower()
		if msg.data.find("kitchen") > -1:
			self.ww==1
			os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
			self.soundhandle.say("should i go to the kitchen",self.voice)
			self.location="kitchen-table"
			rospy.sleep(3)
			os.system("~/catkin_ws/src/speech/run_pocketsphinx_gpsr.sh")
		elif msg.data.find("dining-room") > -1:
			self.ww==1
			os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
			self.soundhandle.say("should i go to the dining-room",self.voice)
			self.location="bar-table"
			rospy.sleep(3)
			os.system("~/catkin_ws/src/speech/run_pocketsphinx_gpsr.sh")
		elif msg.data.find("living-room") > -1:
			os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
			self.soundhandle.say("should i go to the living-room",self.voice)
			self.ww==1
			self.location="coffee-table"
			rospy.sleep(3)
			os.system("~/catkin_ws/src/speech/run_pocketsphinx_gpsr.sh")
		elif msg.data.find("yes") > -1:
			self.ww==1
			os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
			self.soundhandle.say("i will go to the " + self.location,self.voice)
			self.speech2nav_pub.publish(self.location)
			rospy.sleep(3)

		elif msg.data.find("no") > -1:
			if self.ww==1:
				os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
				self.soundhandle.say("please ask me the question again",self.voice)
				rospy.sleep(3)
				os.system("~/catkin_ws/src/speech/run_pocketsphinx_gpsr.sh")
				self.ww=0

		elif msg.data.find('which-country-is-the-host-of-robocup-ap')>-1:
			os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
			self.ww==1
			self.soundhandle.say('I heared which-country-is-the-host-of-robocup-ap', self.voice)
			rospy.sleep(4)
			self.soundhandle.say('the answer is thailand', self.voice)
			rospy.sleep(4)
			os.system("~/catkin_ws/src/speech/run_pocketsphinx_gpsr.sh")
			rospy.sleep(4)
		elif msg.data.find('what-is-the-name-of-your-team')>-1:
			os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
			self.soundhandle.say('I heared what is the name of your team', self.voice)
			rospy.sleep(4)
			self.ww==1
			self.soundhandle.say('the answer is our team name is kamerider ', self.voice)
			rospy.sleep(4)
			os.system("~/catkin_ws/src/speech/run_pocketsphinx_gpsr.sh")
			rospy.sleep(4)
		elif msg.data.find('who-is-the-lead-actress-of-wonder-women')>-1:
			os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
			self.ww==1
			self.soundhandle.say('I heared who-is-the-lead-actress-of-wonder-women', self.voice)
			rospy.sleep(4)
			self.soundhandle.say('the answer is gal gadot', self.voice)
			rospy.sleep(4)
			os.system("~/catkin_ws/src/speech/run_pocketsphinx_gpsr.sh")
		elif msg.data.find('which-operating-system-are-you-using')>-1:
			os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
			self.ww==1	
			self.soundhandle.say('I heared which-operating-system-are-you-using', self.voice)
			rospy.sleep(4)
			self.soundhandle.say('the answer is linux', self.voice)
			rospy.sleep(4)
				
			os.system("~/catkin_ws/src/speech/run_pocketsphinx_gpsr.sh")
			
		elif msg.data.find('who-is-the-richest-man-in-the-world')>-1:
			os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
			self.soundhandle.say('I heared who-is-the-richest-man-in-the-world', self.voice)
			rospy.sleep(4)
			self.soundhandle.say('the answer is jeff bezos', self.voice)
			
			self.ww==1
			rospy.sleep(4)
				
			os.system("~/catkin_ws/src/speech/run_pocketsphinx_gpsr.sh")
				
			rospy.sleep(4)
		elif msg.data.find('name-one-of-the-famous-thai-food')>-1:
			os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
			self.soundhandle.say('I heared name-one-of-the-famous-thai-food', self.voice)
			rospy.sleep(4)
			self.soundhandle.say('the answer is tom yum goong', self.voice)
			rospy.sleep(4)
			self.ww==1				
			os.system("~/catkin_ws/src/speech/run_pocketsphinx_gpsr.sh")
		elif msg.data.find('where-are-you-from')>-1:
			os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
			self.soundhandle.say('I heared where-are-you-from', self.voice)
			rospy.sleep(4)
			self.soundhandle.say('I come from China', self.voice)
			rospy.sleep(4)
			self.ww==1				
			os.system("~/catkin_ws/src/speech/run_pocketsphinx_gpsr.sh")
				
		elif msg.data.find('who-is-current-US-president')>-1 or msg.data.find('who-is-current-United-State-president')>-1:
			os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
			self.soundhandle.say('I heared who-is-current-US-president', self.voice)
			rospy.sleep(4)
			self.soundhandle.say('the answer is donald trump', self.voice)
			rospy.sleep(4)
			self.ww==1				
			os.system("~/catkin_ws/src/speech/run_pocketsphinx_gpsr.sh")
				
				
		elif msg.data.find('how-many-stations-are-there-in-BTS-skytrains')>-1:
			os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
			self.soundhandle.say('I heared how-many-stations-are-there-in-BTS-skytrains', self.voice)
			rospy.sleep(4)
			self.soundhandle.say('the answer is thrity-five', self.voice)
			rospy.sleep(4)
			self.ww==1				
			os.system("~/catkin_ws/src/speech/run_pocketsphinx_gpsr.sh")
				
		elif msg.data.find('where-will-next-world-robocup-be-held')>-1:
			os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
			self.soundhandle.say('I heared where-will-next-world-robocup-be-held', self.voice)
			rospy.sleep(4)
			self.soundhandle.say('the answer is Montresl canada ', self.voice)
			rospy.sleep(4)
			self.ww==1				
			os.system("~/catkin_ws/src/speech/run_pocketsphinx_gpsr.sh")
			
				#print('over 410000 square metres')
		elif msg.data.find('Who-is-the-singer-of-the-song-grenade')>-1:
			os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
			self.soundhandle.say('I heared Who-is-the-singer-of-the-song-grenade', self.voice)
			rospy.sleep(4)
			self.soundhandle.say('the answer is Bruno mars', self.voice)
			rospy.sleep(4)
			self.ww==1				
			os.system("~/catkin_ws/src/speech/run_pocketsphinx_gpsr.sh")
			
		elif msg.data.find('which-robot-platfrorm-is-used-for-educaational=league')>-1:
			os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
			self.soundhandle.say('I heared which-robot-platfrorm-is-used-for-educaational=league', self.voice)
			rospy.sleep(4)
			self.soundhandle.say('the answer is turtle bot', self.voice)
			rospy.sleep(4)
			self.ww==1			
			os.system("~/catkin_ws/src/speech/run_pocketsphinx_gpsr.sh")
			
		elif msg.data.find('tell-me-the-name-of-this-venue')>-1:
			os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
			self.soundhandle.say('I heared tell-me-the-name-of-this-venue', self.voice)
			rospy.sleep(4)
			self.soundhandle.say('the answer is bangkok international trade and exhibition center ', self.voice)
			rospy.sleep(4)
			self.ww==1				
			os.system("~/catkin_ws/src/speech/run_pocketsphinx_gpsr.sh")
			
		elif msg.data.find('how-much-doex-iphone-x-cost-in usa')>-1:
			os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
			self.soundhandle.say('I heared how-much-doex-iphone-x-cost-in usa', self.voice)
			rospy.sleep(4)
			self.soundhandle.say('the answer is 999 us dollars ', self.voice)
			rospy.sleep(4)
			self.ww==1			
			os.system("~/catkin_ws/src/speech/run_pocketsphinx_gpsr.sh")
				
				#print('the inventor of the first compiler')
		elif msg.data.find('what-is-the-batman-super-power')>-1:
			os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
			self.soundhandle.say('I heared what-is-the-batman-super-power', self.voice)
			rospy.sleep(4)
			self.soundhandle.say('the answer is rich ', self.voice)
			rospy.sleep(4)
			self.ww==1
			os.system("~/catkin_ws/src/speech/run_pocketsphinx_gpsr.sh")
				
		elif msg.data.find('how-many-team-in-at-home-league')>-1:
			os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
			self.soundhandle.say('I heared how-many-team-in-at-home-league', self.voice)
			rospy.sleep(4)
			self.soundhandle.say('the answer is 7 teams ', self.voice)
			rospy.sleep(4)
			self.ww==1				
			os.system("~/catkin_ws/src/speech/run_pocketsphinx_gpsr.sh")
				
		elif msg.data.find('what-is-the-biggest-airport-in-thailand')>-1:
			os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
			self.soundhandle.say('I heared what-is-the-biggest-airport-in-thailand', self.voice)
			rospy.sleep(4)
			self.soundhandle.say('the answer is suvarnabhumi airport', self.voice)
			rospy.sleep(4)
			self.ww==1			
			os.system("~/catkin_ws/src/speech/run_pocketsphinx_gpsr.sh")
		elif msg.data.find('what-is-the-tallest-building-in-the-world')>-1:
			os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
			self.soundhandle.say('I heared what-is-the-tallest-building-in-the-world', self.voice)
			rospy.sleep(4)
			self.soundhandle.say('the answer is burj khalifa', self.voice)
			rospy.sleep(4)
			self.ww==1				
			os.system("~/catkin_ws/src/speech/run_pocketsphinx_gpsr.sh")
		elif msg.data.find('what-is-the-name-of-our-galaxy')>-1:
			os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
			self.soundhandle.say('I heared what-is-the-name-of-our-galaxy', self.voice)
			rospy.sleep(4)
			self.soundhandle.say('the answer is milky way', self.voice)
			rospy.sleep(4)
			self.ww==1				
			os.system("~/catkin_ws/src/speech/run_pocketsphinx_gpsr.sh")
		elif msg.data.find('what-is-the-symbolic-animal-of-thailand')>-1:
			os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
			self.soundhandle.say('I heared what-is-the-symbolic-animal-of-thailand', self.voice)
			rospy.sleep(4)
			self.soundhandle.say('the answer is elephant', self.voice)
			rospy.sleep(4)
			self.ww==1				
			os.system("~/catkin_ws/src/speech/run_pocketsphinx_gpsr.sh")
		elif msg.data.find('how-many-time-robocup-held-in-thailand')>-1:
			os.system("~/catkin_ws/src/speech/kill_pocketsphinx.sh")
			self.soundhandle.say('I heared how-many-time-robocup-held-in-thailand', self.voice)
			rospy.sleep(4)
			self.soundhandle.say('the answer is one time', self.voice)
			rospy.sleep(4)
			self.ww==1
			os.system("~/catkin_ws/src/speech/run_pocketsphinx_gpsr.sh")

		elif msg.data.find("question") > -1:
			self.if_answer=1

	def just_say(self,msg):
		msg.data=msg.data.lower()
		self.soundhandle.say( msg.data,self.voice)
		rospy.sleep(4)
	def inspect_callback(self,msg):
		msg.data=msg.data.lower()
		if msg.data=="get_pose":
			self.soundhandle.say("please say jack before each question",self.voice)
			rospy.sleep(3.5)
			self.soundhandle.say("please ask me the first category question",self.voice)
			rospy.sleep(3.5)
			rospy.Subscriber('recognizer_output',String,self.follow)

	def cleanup(self):
		rospy.loginfo("shuting down navsp node ....")
if __name__=="__main__":
	rospy.init_node('help_me_carry')
	try:
		help_me_carry()
		rospy.spin()
	except:
		pass





