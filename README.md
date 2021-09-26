# Shelly Bike Guard Musical Alarm (+ amazon echo) Inspiration

A security system for the theft prevention of bicycles, particularly on college cmapuses. As students return to classes there has been 
an increase in bicycle theft on campus. This project was created at Shellhacks 2021, with some basic hardware repurposed from 
https://github.com/origamiNDroid/Vehicle-IoT-Security-System, specifically the esp8266 with the accelerometer inside the 3D printed container. 
The code is different and the implementation is different. This is a college student budget friendly approach that is easy to reproduce and 
deploy to deter bicycle theft. This project demphasized the use of hardware in favor of a more pleasant user experience via software over the IFTTT network.


# Purpose
 
Many bicycles are protected by utilizing bike locks. Sadly these locks are not secure enough to protect against theft. With tools such as angle 
grinders, bolt cutters and even wire cutters being used to get around the locking system, theives are able to steal a bicycle in less than a minute. 
Furthermore, when a theft is in progress the owner is away and has no way of knowing a thief is riding away on their favorite mode of transportation. 
The solution being proposed is to utilize an internet of things device (IoT) paired with an accelerometer in order to alert the cyclist owner of 
an ongoing theft via a phone call, a musical alarm, and an amazon echo device notification. By creating an IoT enabled device, the user will be 
alerted to a potential theft from a remote location.


# Bicycle Device

The bicycle device consists of an ESP8266 NodeMCU v1.0, a 9V battery, and an Adafruit LIS3DH Triple-Axis Accelerometer Breakout Board. This device is the 
client, and it connects to a nearby network of the user's choosing. This device is meant to be placed on the bicycle. The device will send a webhook http 
request to the IFTTT web server when motion is detected by the accelerometer, through the ESP8266 via a client-and-server protocol over a network connection. 
See the image below for the breadboard layout of the bicycle device.


# IFTTT Setup
IFTTT is a programmable automation system that allows for custom connections via individually programmed applets. These applets utilize a trigger to initiate 
a series of actions. In this project the trigger is activated when the agitated accelerometer causes the esp8266 to send an http request to the IFTTT web server via the ifttt webhook application. This trigger will cause the user's cellphone to be placed at maximum volume regardless of do not disturb settings and silencing, a robot call from Shelly the ShellHacks mascot will call the user to warn them of the possible bicycle theft. The Amazon Echo device will receive a notification as well. Lastly, the song “Bicycle Race” by Queen (or any song of the user's choosing) will be automatically played on a Spotify Premium account upon screen unlocking. This ensures the user will be notified upon first
use of the cellphone. A diagram of the trigger and all the actions are included below.


# Requirements For Full-Functionality (Not all requirements are needed for partial functionality)

Basic Functionality Requirements (Important to receive Shelly's loud warning call):
- Android phone
- US Phone Number is required
- IFTTT Mobile Phone App installation required
  - Allow Display Over Other Apps 
  - Allow fucntionality over Do Not Disturb

Mobile Device Requirements:
- Android phone
- US Phone Number is required
- IFTTT Mobile Phone App installation required
  - Allow Display Over Other Apps 
  - Allow fucntionality over Do Not Disturb
- Spotify Premium is required to play the song of choice
  - If premium is not available a random song will play instead
  - Spotify needs to be set to Always open when triggered by IFTTT
- Music Volume needs to be at an audible level for song to play
  - Phone ringtone volume may be on silence, that's not important as it will be changed to maximum volume automatically when Shelly calls...
- Amazon Alexa App is required in order to allow amazon echo to receive notifications from IFTTT
  - Amazon echo will provide a time stamp of the event in the notification
  
Bicycle Device Requirements
- Must be near Wifi location (not too hard to hard to accomplish on a college campus, especially if created using a LoRa Gateway)
- Create C header file with ssid and password
- Create C header file with API key resource
- Upload arduino sketch to ESP8266 
- Refer to diagram for more
 
IFTTT Requirements
- Pro version is required for simplicity, otherwise user will have to create to Applets separately

# Total Cost of Project 
- Esp8266 = $5 fixed
- Adafruit LIS3DH = $5 fixed
- perfboard + solder + random non-metallic case + misc = $10 fixed
- Spotify Premium = $10 monthly
- IFTTT Pro = $3.33 monthly

Total Down Payment: $33.33

Monthly Subscriptions after first month: $13.33 

# Improvements for the Future

Potential improvements for this project include:
- Reduce Form factor
- Replace IFTTT with a custom standalone mobile application compatible with android and iOS systems
- Use of an ESP32 instead of ESP8266 for Bluetooth access as well as WiFi
- Improve power electronics and get rid of developement board in favor of barebones esp32 board for battery longetivity
- RFM95W LoRa transceiver for ESP32
- Utilize LoRa gateway to communicate with sensor instead of relying solely on a wifi router connection
- Communicate with universities in order to establish LoRa gateways on campus as a common practice
  - LoRa stands for Long Range and can provide network connectivity of up to 3 miles in urban areas and 10 miles in rural areas.

This project is very feasible and practical, especially with the improvements mentioned above. This is the solution to a campus free of stolen bicycles.

# Project Inspiration
- https://panthernow.com/2021/09/20/theft-expected-to-rise-amid-in-person-classes/
- https://www.wftv.com/news/local/ucf-police-crack-down-bicycle-thefts-bait-bike-tec/271591798/
- https://www.reddit.com/r/ufl/comments/ho3yle/is_bike_theft_a_big_issue_at_uf/
- https://randomnerdtutorials.com/esp8266-wi-fi-button-diy-amazon-dash-button-clone/
- https://github.com/origamiNDroid/Vehicle-IoT-Security-System
