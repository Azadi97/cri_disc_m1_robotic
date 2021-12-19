/*
 *****IMPORTATIONS and Global variables*****
 */
#include <IRremote.h>// IR remote library
#include <Servo.h>

// Create a new servo object:
Servo myservo;
Servo myservo2;

// Define the servo pin:
#define servoPin 5
#define servoPin2 6

// Create a variable to store the servo position:
int angle = 0;

// Copied from the example code (IRrecvDemo) to generate remote codes
# define ir_sensor 10//IR reciever pin
IRrecv irrecv(ir_sensor);
decode_results results;

//Code of all button defined thanks to the serial monitor with the example code (IRrecvDemo)
#define FWD       0xCF2F9DAB // go forward(+)
#define LFT       0xB53DCEA6 // go left(|<<)
#define RGT       0x1E3D4782 // go right(>>|)
#define BWD       0xB2BBAC69 // go backward(-)
#define STOP      0xCA31DA45 // stop(POWER)
#define ATT       0x7C101285 // ATTACH THE MOTORS(WOOFER)
#define RPEAT     0x3CEB5F42 // repeat the stored movements sequence from the temporary memory(REPT)
#define DEL       0x123CD34B // delete the stored movements sequence from the temporary temporary memory(MUTE)



/*
 *****Global Variables and Arrays for each movements and their duration*****
 */
 
unsigned long int value = 0; // stores value
byte movements = 0; //current number of executed movements sequences
byte movements_list[120];// array to store the movement movements executed in the sequence as integers. 120 is the max number of movement that we fixed

//count the number of times a specific movement is repeated
int fwd_movements_numbers = -1;
int lft_movements_numbers = -1;
int rgt_movements_numbers = -1;
int bwd_movements_numbers = -1;
int stp_movements_numbers = -1;
int att_movements_numbers = -1;

//global duration variables for each movements
unsigned long int nowtimefwd = 0;// time for FWD movement
unsigned long int nowtimelft = 0;// time for LEFT movement
unsigned long int nowtimeright = 0;// time for RIGHT movement
unsigned long int nowtimebwd = 0;// time for BWD movement
unsigned long int nowtimestp = 0;// time for STOP
unsigned long int nowtimeatt = 0;// time for ATTACH

//total time spend executing each movements
unsigned long int total_Fwd_Time[20];
unsigned long int total_Lft_Time[20];
unsigned long int total_Rgt_Time[20];
unsigned long int total_Bwd_Time[20];
unsigned long int total_Stp_Time[20];
unsigned long int total_Att_Time[20];

 

void setup() {
  // Attach the Servo variable to a pin:
  myservo.attach(servoPin);
  myservo2.attach(servoPin2);

   // set mode of the pins (5 and 6) as output
  for (int i = 5; i <= 6; i++) {
    pinMode(i, OUTPUT);
  }

//this part comes from IRrecvDemo code from arduino
  // start serial monitor
  Serial.begin(9600);
  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin");
}

void loop() {
  
//this part comes from IRrecvDemo code from arduino

if (irrecv.decode(&results)) { //if the ir receiver receive a value, put the value in the 'value' variable
    value = results.value;
    Serial.println(value, HEX);//print in the serial monitor in an HEX format
    irrecv.resume(); // Receive the next value
    delay(200);
  }

  delay(100);
  check_function(value);
  value=0;


}

/*
 *****Important general functions*****
 */

  void Forward() { //funtion used to execute the perform forward function
  perform_Fwd(); //function to perform the fwd movement

  nowtimefwd = millis();
  int i = movements_list[(movements - 1)];
  if(i == 2){
    total_Lft_Time[lft_movements_numbers + 1] = (nowtimefwd - nowtimelft);
      lft_movements_numbers++;
  }
  else if(i == 3){
      total_Rgt_Time[rgt_movements_numbers + 1] = (nowtimefwd - nowtimeright);
      rgt_movements_numbers++;
  }
  else if(i == 4){
      total_Bwd_Time[bwd_movements_numbers + 1] = (nowtimefwd - nowtimebwd);
      bwd_movements_numbers++;
  }
  else if(i == 5){
      total_Stp_Time[stp_movements_numbers + 1] = (nowtimefwd - nowtimestp);
      stp_movements_numbers++;
  }
  else if(i == 6){
      total_Att_Time[att_movements_numbers + 1] = (nowtimefwd - nowtimeatt);
      att_movements_numbers++;
  }

  movements_list[movements] = 1;
  movements++;
}

void Left() {
  perform_Lft();

  nowtimelft = millis();
  int i = movements_list[(movements - 1)];
  if (i == 1){
    total_Fwd_Time[fwd_movements_numbers + 1] = (nowtimelft - nowtimefwd);
    fwd_movements_numbers++;
  }
  else if (i == 3){
      total_Rgt_Time[rgt_movements_numbers + 1] = (nowtimelft - nowtimeright);
      rgt_movements_numbers++;
  }
  else if (i == 4){
      total_Bwd_Time[bwd_movements_numbers + 1] = (nowtimelft - nowtimebwd);
      bwd_movements_numbers++;
  }
  else if (i == 5){
      total_Stp_Time[stp_movements_numbers + 1] = (nowtimelft - nowtimestp);
      stp_movements_numbers++;
  }
   else if (i == 6){
      total_Att_Time[att_movements_numbers + 1] = (nowtimefwd - nowtimeatt);
      att_movements_numbers++;
  }

  movements_list[movements] = 2;
  movements++;
}

void Right() {
  perform_Rgt();

  nowtimeright = millis();
  int i = movements_list[(movements - 1)];
  if (i == 1){
      total_Fwd_Time[fwd_movements_numbers + 1] = (nowtimeright - nowtimefwd);
      fwd_movements_numbers++;
  }
  else if (i == 2){
      total_Lft_Time[lft_movements_numbers + 1] = (nowtimeright - nowtimelft);
      lft_movements_numbers++;
  }
  else if (i == 4){
      total_Bwd_Time[bwd_movements_numbers + 1] = (nowtimeright - nowtimebwd);
      bwd_movements_numbers++;
  }
  else if (i == 5){
      total_Stp_Time[stp_movements_numbers + 1] = (nowtimeright - nowtimestp);
      stp_movements_numbers++;
  }
  else if (i == 6){
      total_Att_Time[att_movements_numbers + 1] = (nowtimefwd - nowtimeatt);
      att_movements_numbers++;
  }

  movements_list[movements] = 3;
  movements++;
}

void Backward() {
  perform_Bwd();

  nowtimebwd = millis();
  int i = movements_list[(movements - 1)];
  if (i == 1){
      total_Fwd_Time[fwd_movements_numbers + 1] = (nowtimebwd - nowtimefwd);
      fwd_movements_numbers++;   
  }
  else if (i == 2){
      total_Lft_Time[lft_movements_numbers + 1] = (nowtimebwd - nowtimelft);
      lft_movements_numbers++;
  }
  else if (i == 3){
      total_Rgt_Time[rgt_movements_numbers + 1] = (nowtimebwd - nowtimeright);
      rgt_movements_numbers++;  
  }
  else if (i == 5){
      total_Stp_Time[stp_movements_numbers + 1] = (nowtimebwd - nowtimestp);
      stp_movements_numbers++;
  }
  else if (i == 6){
      total_Att_Time[att_movements_numbers + 1] = (nowtimefwd - nowtimeatt);
      att_movements_numbers++;
  }

  movements_list[movements] = 4;
  movements++;
}

void Stop() {
  perform_Stp();

  nowtimestp = millis();
  int i = movements_list[(movements - 1)];
  if (i == 1){
      total_Fwd_Time[fwd_movements_numbers + 1] = (nowtimestp - nowtimefwd);
      fwd_movements_numbers++;
  }
  else if (i == 2){
      total_Lft_Time[lft_movements_numbers + 1] = (nowtimestp - nowtimelft);
      lft_movements_numbers++;
  }
  else if (i == 3){
      total_Rgt_Time[rgt_movements_numbers + 1] = (nowtimestp - nowtimeright);
      rgt_movements_numbers++;
  }
  else if (i == 4){
      total_Bwd_Time[bwd_movements_numbers + 1] = (nowtimestp - nowtimebwd);
      bwd_movements_numbers++;
  }
  else if (i == 6){
      total_Att_Time[att_movements_numbers + 1] = (nowtimefwd - nowtimeatt);
      att_movements_numbers++;
  }

  movements_list[movements] = 5;
  movements++;
}

void Att() {
  perform_Att();

  nowtimeatt = millis();
  int i = movements_list[(movements - 1)];
  if(i == 1){
      total_Fwd_Time[fwd_movements_numbers + 1] = (nowtimestp - nowtimefwd);
      fwd_movements_numbers++;
  }
  else if(i == 2){
      total_Lft_Time[lft_movements_numbers + 1] = (nowtimestp - nowtimelft);
      lft_movements_numbers++;
  }
  else if(i == 3){
      total_Rgt_Time[rgt_movements_numbers + 1] = (nowtimestp - nowtimeright);
      rgt_movements_numbers++;
  }
  else if(i == 4){
      total_Bwd_Time[bwd_movements_numbers + 1] = (nowtimestp - nowtimebwd);
      bwd_movements_numbers++;
  }
  else if(i == 5){
      total_Stp_Time[stp_movements_numbers + 1] = (nowtimebwd - nowtimestp);
      stp_movements_numbers++;
  }

  movements_list[movements] = 6;
  movements++;
}


void store_In_movements(void) {
  value = 0;
  for (int i = 0; i < (movements + 1); i++) {
    int value1 = 0;
    value1 = movements_list[i];
    switch (value1) {
      case 1:
        static int j = 0;
        Forward_movements(j);
        j++;
        break;
      case 2:
        static int k = 0;
        Left_movements(k);
        k++;
        break;
      case 3:
        static int l = 0;
        Right_movements(l);
        l++;
        break;
      case 4:
        static int m = 0;
        Backward_movements(m);
        m++;
        break;
      case 5:
        static int n = 0;
        Stop_movements(n);
        n++;
        break;
      case 6:
        static int o = 0;
        Att_movements(o);
        o++;
        break;
      default:
        j = 0; k = 0; l = 0; m = 0; n = 0; o = 0;
    }
  }
}

void deleteseq() {//function to delete from arduino memory
  // set count to default value
  fwd_movements_numbers = -1;
  lft_movements_numbers = -1;
  rgt_movements_numbers = -1;
  bwd_movements_numbers = - 1;
  stp_movements_numbers = - 1;
  att_movements_numbers = -1;
  //set total movement duration to default value
  for (int i = 0; i < 10; i++) {
    total_Fwd_Time[i] = 0;
    total_Lft_Time[i] = 0;
    total_Rgt_Time[i] = 0;
    total_Bwd_Time[i] = 0;
    total_Stp_Time[i] = 0;
    total_Att_Time[i] = 0;
  }

  // Reset the movement array
  for (int i = 0; i < 50; i++) {
    movements_list[i] = 0;
  }

  movements = 0;
  
}

/*******************************
          Functions to store each movements
********************************/
void Forward_movements(int j) {
  perform_Fwd();
  delay(total_Fwd_Time[j]);
}

void Left_movements(int k) {
  perform_Lft();
  delay(total_Lft_Time[k]);
}

void Right_movements(int l) {
  perform_Rgt();
  delay(total_Rgt_Time[l]);
}

void Backward_movements(int m) {
  perform_Bwd();
  delay(total_Bwd_Time[m]);
}

void Stop_movements(int n) {
  perform_Stp();
  delay(total_Stp_Time[n]);
}
void Att_movements(int o) {
  perform_Att();
  delay(total_Att_Time[o]);
}


/*******************************
          Functions to perform the movements
********************************/
void perform_Fwd(void) {// function to perform the forward movement
  Serial.println("Forward");
    myservo.write(180);
    myservo2.write(0);
}

void perform_Lft(void) {// function to perform the left movement
  Serial.println("Left");
    myservo.write(0);
    myservo2.write(0);
}

void perform_Rgt(void) { // function to perform the right movement
  Serial.println("Right"); 
    myservo.write(180);
    myservo2.write(180);
}

void perform_Bwd(void) {// function to perform the backward movement
  Serial.println("Backward");
    myservo.write(0);
    myservo2.write(180);
}

void perform_Stp(void) {// function to perform the stop movement
  Serial.println("Stop");
  myservo.detach();
  myservo2.detach();
}

void perform_Att(void) {// function to perform the attach instruction (attach the servo motors)
  Serial.println("Attach");
  myservo.attach(servoPin);
  myservo2.attach(servoPin2);
}
void check_function(long int value) { //fuction to check if the data stored in variable value match with the remote code
//example for case 1: if variable value = FWD perform the Forward function and so on, if none of the cases value = 0
  if (value == FWD){
    Forward();
      delay(10);
  }
  else if (value == LFT){
    Left();
      delay(10);
  }
  else if (value == RGT){
    Right();
      delay(10);
  }
  else if (value == BWD){
    Backward();
      delay(10);
  }
  else if (value == STOP){
    Stop();
      delay(10);
  }
  else if (value == ATT){
    Att();
      delay(10);
  }
  else if (value == RPEAT){
    store_In_movements();
      delay(10);
  }
  else if (value == DEL){
    deleteseq();
      delay(10);
  }
  else {
    value = 0;
  }
}
