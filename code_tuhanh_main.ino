#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
BluetoothSerial SerialBT;
char c;
String voice;
#define IN1 21
#define IN2 19
#define IN3 18
#define IN4 5
const int freq = 5000;  // tần số xung
const int ledChannel0 = 6; // kênh PWM
const int ledChannel1 = 7; // kênh PWM
const int ledChannel2 = 4; // kênh PWM
const int ledChannel3 = 5; // kênh PWM

const int resolution = 8;

#include <Servo.h>

static const int servoPin1 = 13;//Servo bom
static const int servoPin2 = 27;//Servo tu hanh
static const int servoPin3 = 14;//ESC
Servo servo1;
Servo servo2;
Servo servo3;

const int trig = 23;     // chân trig của HC-SR04
const int echo = 22;     // chân echo của HC-SR04
unsigned long duration; // biến đo thời gian
int distance;           // biến lưu khoảng cách

#define choi 4
#define bom1 17
#define bom2 16
#define coi 12
#define hongngoai 15
unsigned long time_wait; 
unsigned long time_coi; 
uint32_t aLDR[6] = { 0, 0, 0, 0, 0, 0};
uint16_t  avgLine[6], avgOut[6], value[6];
uint8_t ldrPin[6] = {35, 34, 36, 32, 25, 26};
float dig[6], Err = 0, Pre_Err = 0;
float P = 0, I = 0, D = 0;

#define  Offset   100
#define Sampling_Time        10 // thoi gian lay mau
#define Inv_Sampling_Time    100  //  1/sampling_time
#define kp   17
#define kd  0.4

#define ki   0
signed int x = 0;
unsigned int PWM = 180;
unsigned int PWMA;
unsigned int PWMB;
#include "Ticker.h"
Ticker blinker1;
unsigned long time_servobom;
bool status1=0;
bool status2=0;
bool status3=0;
bool status4=0;
bool status5=0;
bool status6=0;
bool status7=0;
void setup() {
  Serial.begin(9600);
  pinMode(36, INPUT);
  pinMode(39, INPUT);
  pinMode(34, INPUT);
  pinMode(35, INPUT);
  pinMode(32, INPUT);
  pinMode(33, INPUT);
  pinMode(25, INPUT);
  pinMode(26, INPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(coi, OUTPUT);
  pinMode(hongngoai,INPUT);
  pinMode(choi, OUTPUT);
  pinMode(bom1, OUTPUT);
  pinMode(bom2, OUTPUT);
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 0);
  ledcSetup(ledChannel0, freq, resolution);
  ledcSetup(ledChannel1, freq, resolution);
  ledcSetup(ledChannel2, freq, resolution);
  ledcSetup(ledChannel3, freq, resolution);
  ledcAttachPin(IN1, ledChannel0);
  ledcAttachPin(IN2, ledChannel1);
  ledcAttachPin(IN3, ledChannel2);
  ledcAttachPin(IN4, ledChannel3);
  digitalWrite(coi,0);
  servo1.attach(servoPin1);
  servo1.write(65);
  servo2.attach(servoPin2);
  servo2.write(85);
  servo3.attach(servoPin3);
  servo3.write(180);
  delay(2000);
  servo3.write(20);
  delay(2000);
  servo3.write(0);
  delay(1000);
  Serial.println("Done ESC");
  servo2.write(30);
  pinMode(trig, OUTPUT);  // chân trig sẽ phát tín hiệu
  pinMode(echo, INPUT);   // chân echo sẽ nhận tín hiệu
  SerialBT.begin("Clean_Robot");
  while (!SerialBT.available());
while(voice!="A"){  
  while (SerialBT.available())   //Check if there is an available byte to read
  {                            
    delay(10);                   //Delay added to make thing stable
    c = SerialBT.read();      //Conduct a serial read
    if (c == '#') {break;}       //Exit the loop when the # is detected after the word
    voice += c;                  //Shorthand for voice = voice + c
    Serial.println("voice");
  }
  if (voice.length() > 0){
    if(voice == "A"){
      Serial.println("hocline");
      readLinee();
      delay(1000);
      Serial.println("done realine");
      tien();
      delay(1000);
      Serial.println("done tien");
      dung();
      delay(500);
      readOut();
      delay(500);
      Serial.println("done readout");
      lui();
      delay(800);
      Serial.println("done lui");
      phai();
      delay(1500);
      dung();
      servo2.write(85);
    }
    if(voice=="H"){
      trai();
    }
    if(voice=="I"){
      tien();
    }
    if(voice=="K"){
      lui();
    }
    if(voice=="S"){
      phai();
    }
    if(voice=="P"){
      dung();
    }
    if(voice!="A"){
      voice="";
    }
  }
}
  
  time_servobom=millis();
  time_coi=millis();
  time_wait=millis();
  
  blinker1.attach(0.01, pidCal); 
  
}
void read_sr04() {
  digitalWrite(trig, 0);  // tắt chân trig
  delayMicroseconds(2);
  digitalWrite(trig, 1);  // phát xung từ chân trig
  delayMicroseconds(5);   // xung có độ dài 5 microSeconds
  digitalWrite(trig, 0);  // tắt chân trig

  /* Tính toán thời gian */
  // Đo độ rộng xung HIGH ở chân echo.
  duration = pulseIn(echo, HIGH);
  // Tính khoảng cách đến vật.
  distance = int(duration / 2 / 29.412);

  /* In kết quả ra Serial Monitor */
  Serial.print(distance);
  Serial.println("cm");
  delay(200);
}
int distance_left;
int distance_right;
void auto_run() {
  read_sr04();
  Serial.print(distance);
  Serial.println("cm");
  if (distance < 20) {
    dung();
    delay(1000);

    servo2.write(150);
    delay(1500);
    read_sr04();
    distance_left = distance;
    Serial.print("left:");
    Serial.println(distance_left);

    servo2.write(30);
    delay(1500);
    read_sr04();
    distance_right = distance;
    Serial.print("right:");
    Serial.println(distance_right);

    servo2.write(85);
    delay(1000);
    if (distance_left < distance_right) {
      Serial.println("Re phai");
      lui();
      delay(1000);
      phai();
      delay(2000);
    }
    else {
      Serial.println("Re trai");
      lui();
      delay(1000);
      trai();
      delay(2000);
    }
  }
  else {
    tien();
  }
}
void tien() {
  ledcWrite(ledChannel0, 200);
  ledcWrite(ledChannel1, 0);
  ledcWrite(ledChannel2, 200);
  ledcWrite(ledChannel3, 0);
}
void lui() {
  ledcWrite(ledChannel0, 0);
  ledcWrite(ledChannel1, 200);
  ledcWrite(ledChannel2, 0);
  ledcWrite(ledChannel3, 200);
}
void trai() {
  ledcWrite(ledChannel0, 0);
  ledcWrite(ledChannel1, 100);
  ledcWrite(ledChannel2, 100);
  ledcWrite(ledChannel3, 0);
}
void phai() {
  ledcWrite(ledChannel0, 100);
  ledcWrite(ledChannel1, 0);
  ledcWrite(ledChannel2, 0);
  ledcWrite(ledChannel3, 100);
}
void dung() {
  ledcWrite(ledChannel0, 0);
  ledcWrite(ledChannel1, 0);
  ledcWrite(ledChannel2, 0);
  ledcWrite(ledChannel3, 0);
}
bool stt_trai=0;
bool stt_phai=0;
bool stt_tien=0;
bool stt_lui=0;
bool stt_dung=0;

void read_blt(){
    c = SerialBT.read(); 
//    Serial.print("c:");
//    Serial.println(c);      
    voice += c; 
    Serial.println(voice); 
  if (voice.length() > 0){
    
    if(voice == "A")
    {
//      Serial.println("Hocline");
                   
    }
    else if(voice=="C")
    {
      status3=!status3;
//      Serial.println("do line");      
    }
    else if(voice=="B")
    {
      status2=!status2;
//      Serial.println("netranhvatcan");
    }
    else if(voice=="D")
    {
      status4=!status4;
//      Serial.println("bom1");           
    }
    else if(voice=="E")
    {
      status5=!status5;
//      Serial.println("bom2");      
    }
    else if(voice== "F"){
      status6=!status6;
//      Serial.println("choi");
    }
    else if(voice== "G"){
      status7=!status7;
//      Serial.println("hutbui");
    }
    else if(voice=="H"){
      stt_trai=1;
      stt_dung=0;
    }
    else if(voice=="I"){
      stt_tien=1;
      stt_dung=0;
    }
    else if(voice=="S"){
      stt_phai=1;
      stt_dung=0;
    }
    else if(voice=="K"){
      stt_lui=1;
      stt_dung=0;
    }
    else if(voice=="P"){
      stt_trai=0;
      stt_phai=0;
      stt_tien=0;
      stt_lui=0;
      stt_dung=1;
    }
    voice=""; 
  }    
}
void dieukhien(){
  if(status2==0&&status3==0&&stt_dung==1){
    dung();
//    Serial.println("DC dung");
  }
  if(status2==0&&status3==0&&stt_trai==1){
    trai();
  }
  if(status2==0&&status3==0&&stt_phai==1){
    phai();
  }
  if(status2==0&&status3==0&&stt_tien==1){
    tien();
  }
  if(status2==0&&status3==0&&stt_lui==1){
    lui();
  }
  if(status2==1&&status3==1){
    dung();
//    Serial.println("DC dung");
  }  
   if(status2==1&&status3==0){
    auto_run();
//    Serial.println("DC netranh vat can");
  }
  if(status3==1&&status2==0){
    read_sensor_value();
    motor_pid();
//    Serial.println("DC PID");
  }
  if(status4==0){
    digitalWrite(bom1,0);
//    Serial.println("b1 dung");
  }
  if(status4==1){
    digitalWrite(bom1,1);
//    Serial.println("b1 run");
  }
  if(status5==0){
    digitalWrite(bom2,0);
//    Serial.println("b2 dung");
  }
  if(status5==1){
    digitalWrite(bom2,1);
//    Serial.println("b2 run");
  }  
  if(status6==0){
    digitalWrite(choi,0);
//    Serial.println("choi dung");
  }  
  if(status6==1){
    digitalWrite(choi,1);
//    Serial.println("choi run");
  }
  if(status7==0){
    servo3.write(0);
//    Serial.println("esc dung");
  }  
  if(status7==1){
    servo3.write(38);
//    Serial.println("esc run");
  }
}
void loop() {
  read_blt();
  dieukhien();
}
