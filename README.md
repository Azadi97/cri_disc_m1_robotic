# cri_disc_m1_robotic

 Everything is on GitHub
Here is the link : https://github.com/Azadi97/cridiscm1_robotic Final Robot: Blind Check, The robotic Dog (robotic for good)
Problem : make a robotic dog able to guide the user from point A to point B.

Robotic Challenge (assigned by Kevin and Rajeev): Map a Room

Strategy: we decided to use the Path remembering technique. This technique allows the robot to reproduce a path after following it once.

Features: 
- Follow a path once by being directed by a remote control 

-Remember the path

-Repeat the path in an autonomous way
  
 Components

● IR Receiver

● IR remote controller

● Breadboard

● Arduino Leonardo

● Wires

● 2 servo motors

● 2 wheels

● cardboard

● Arduino Software

● Balance wheel

● others (tapes, ...)


Logic:

For this challenge, our logic can be summarized in one sentence: "try something, see if it works, if yes it's great, if no try something else". After a time to review the tutorials, online examples, follow the step provided by Kevin, and question our teacher Rajeev (aka Batman). We created our own code that led us to absolute victory. Actually, we did even better, following Rajeev’s advice we created two different codes for this challenge: One main code (this one is the code that allowed us to meet the challenge (you can already find him on the git repository)) that we built based on skills developed in previous robotics courses, online tutorial and Arduino software example code . One second code that we totally built from scratch thanks to the EEPROM Library (we didn’t manage to make it on time but we explained it in our slides with a little video demo and it works (you can also find this code in the git repository))

For the main code the idea is :

1- to control the robot with an IR remote controller and an Ir receiver in order to make him follow a path

2- to store each movement and its duration in an array (in arduino temporary memory) that will be read after pressing the repeat button on the remote.


Logic of the main code:

● step 0 : We import the servo and IR. remote library

● step 1: We create an object for each servo motor and the default angle.

● Step 2:We define the pins on which are connected to the servo on the arduino.

● step 3: We define the IR receiver pin

● Step 4: we define the IR remote controller button code (that we found thanks to the serial
monitor)

● Step 5: we define the general array and a variable where the Ir receiver value will be
stored.

● Step 6: we define some global variable for each movement (counter, duration and total
duration)

● Step 7: we start de servo and the receiver and we check if the instruction received by the
receiver are the good ones

● Step 8 : We control the robot by executing the function and their sub functions with the
conditions each move is automatically stored.


Idea for the second code: Check on GitHub Logic for the second code: SUCCESS



Reference:

RESEARCH PAPER

1. Chuang T-K, Wang H-C, Lin N-C, Chen J-S, Hung C-H, Huang Y-W, et al. Deep Trail-Following Robotic Guide Dog in Pedestrian Environments for People who are Blind and Visually Impaired - Learning from Virtual and Real Worlds. In: 2018 IEEE International Conference on Robotics and Automation (ICRA) [Internet]. Brisbane, QLD: IEEE; 2018 [cité 17 déc 2021]. p. 5849‐55. Disponible sur: https://ieeexplore.ieee.org/document/8460994/


2. Sharkey P, éditeur. The 2nd European Conference on Disability, Virtual Reality and Associated Technologies: proceedings; 10,11 of September, 1998 Mount Billingen, Skövde, Sweden. Reading: Univ. of Reading; 1998. 268 p.


OTHERS SIMILAR/interesting PROJECT

https://create.arduino.cc/projecthub/saiyam/vision-a-torch-for-the-visually-impaired-6e205c


https://create.arduino.cc/projecthub/muhammedazhar/third-eye-for-the-blind-8c246d?ref=platform&ref_id=424_trendi ng___&offset=2
     
 
