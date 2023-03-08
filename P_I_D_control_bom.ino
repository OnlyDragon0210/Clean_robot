void read_sensor_value()
{
     
    for(int i=0; i<6; i++){
    if( analogRead(ldrPin[i])>=value[i])  dig[i]=1;
    else dig[i]=0;
//    Serial.print(dig[i]);
//    Serial.print("   ");  
  }
//  Serial.println(); 

  if     ((dig[0]==1) && (dig[1]==0) && (dig[2]==0) && (dig[3]==0) && (dig[4]==0) && (dig[5]==0)   ) Err =-3;//-3.5
  else if((dig[0]==1) && (dig[1]==1) && (dig[2]==0) && (dig[3]==0) && (dig[4]==0) && (dig[5]==0)   ) Err =-2.5;  //-3
  else if((dig[0]==0) && (dig[1]==1) && (dig[2]==0) && (dig[3]==0) && (dig[4]==0) && (dig[5]==0)   ) Err =-2;//-2.5
//  else if((dig[0]==0) && (dig[1]==1) && (dig[2]==1) && (dig[3]==0) && (dig[4]==0) && (dig[5]==0)   ) Err =-1.5;//-2
  else if((dig[0]==0) && (dig[1]==0) && (dig[2]==1) && (dig[3]==0) && (dig[4]==0) && (dig[5]==0)   ) Err =0.5;//-3
  else if((dig[0]==0) && (dig[1]==0) && (dig[2]==1) && (dig[3]==1) && (dig[4]==0) && (dig[5]==0)   ) Err =0;//-2
  else if((dig[0]==0) && (dig[1]==0) && (dig[2]==0) && (dig[3]==1) && (dig[4]==0) && (dig[5]==0)   ) Err =0.5;//-1
//  else if((dig[0]==0) && (dig[1]==0) && (dig[2]==0) && (dig[3]==1) && (dig[4]==1) && (dig[5]==0)   ) Err =0;//0
  else if((dig[0]==0) && (dig[1]==0) && (dig[2]==0) && (dig[3]==0) && (dig[4]==1) && (dig[5]==0)   ) Err =2;//1
  else if((dig[0]==0) && (dig[1]==0) && (dig[2]==0) && (dig[3]==0) && (dig[4]==1) && (dig[5]==1)   ) Err =2.5;//2
  else if((dig[0]==0) && (dig[1]==0) && (dig[2]==0) && (dig[3]==0) && (dig[4]==0) && (dig[5]==1)   ) Err =3;//3
//  else if((dig[0]==0) && (dig[1]==0) && (dig[2]==0) && (dig[3]==0) && (dig[4]==0) && (dig[5]==1)   ) Err =2;//4
//  else if((dig[0]==0) && (dig[1]==0) && (dig[2]==0) && (dig[3]==0) && (dig[4]==0) && (dig[5]==0)   ) Err =2.5;//5
//  else if((dig[0]==0) && (dig[1]==0) && (dig[2]==0) && (dig[3]==0) && (dig[4]==0) && (dig[5]==0)   ) Err =3;//6
//  else if((dig[0]==0) && (dig[1]==0) && (dig[2]==0) && (dig[3]==0) && (dig[4]==0) && (dig[5]==0)   ) Err =3.5;//7

  else if((dig[0]==0) && (dig[1]==1) && (dig[2]==1) && (dig[3]==1) && (dig[4]==0) && (dig[5]==0)   ) Err =-2;//0
  else if((dig[0]==0) && (dig[1]==0) && (dig[2]==1) && (dig[3]==1) && (dig[4]==1) && (dig[5]==0)   ) Err =2;//0
//  else if((dig[0]==0) && (dig[1]==0) && (dig[2]==0) && (dig[3]==1) && (dig[4]==1) && (dig[5]==1)   ) Err =2.5;//0
//  else if((dig[0]==0) && (dig[1]==0) && (dig[2]==0) && (dig[3]==0) && (dig[4]==1) && (dig[5]==1)   ) Err =2;//0


  else if((dig[0]==1) && (dig[1]==1) && (dig[2]==1) && (dig[3]==0) && (dig[4]==0) && (dig[5]==0)   ) Err =-2.5;
  else if((dig[0]==1) && (dig[1]==1) && (dig[2]==1) && (dig[3]==1) && (dig[4]==0) && (dig[5]==0)   ) Err =-2.5;
  else if((dig[0]==1) && (dig[1]==1) && (dig[2]==1) && (dig[3]==1) && (dig[4]==1) && (dig[5]==0)   ) Err =-2.5;
  else if((dig[0]==1) && (dig[1]==1) && (dig[2]==1) && (dig[3]==1) && (dig[4]==1) && (dig[5]==1)   ) Err =-3;
//  else if((dig[0]==1) && (dig[1]==1) && (dig[2]==1) && (dig[3]==1) && (dig[4]==1) && (dig[5]==1)   ) Err =-3;
//  else if((dig[0]==0) && (dig[1]==0) && (dig[2]==0) && (dig[3]==0) && (dig[4]==0) && (dig[5]==1)   ) Err =3.5;
//  else if((dig[0]==0) && (dig[1]==0) && (dig[2]==0) && (dig[3]==0) && (dig[4]==1) && (dig[5]==1)   ) Err =3.5;
//  else if((dig[0]==0) && (dig[1]==0) && (dig[2]==0) && (dig[3]==1) && (dig[4]==1) && (dig[5]==1)   ) Err =3.5;
  else if((dig[0]==0) && (dig[1]==0) && (dig[2]==1) && (dig[3]==1) && (dig[4]==1) && (dig[5]==1)   ) Err =2.5;
  else if((dig[0]==0) && (dig[1]==1) && (dig[2]==1) && (dig[3]==1) && (dig[4]==1) && (dig[5]==1)   ) Err =2.5;
  
  else if ((dig[1]==0) && (dig[2]==0) && (dig[3]==0) && (dig[4]==0) && (dig[5]==0)  &&   (dig[0]==0))
    {
      if(Pre_Err==-2.5) Err=-3;
    else if(Pre_Err==2.5) Err=3;
    }
//  Serial.print(Err);
//  Serial.println();

}
///-4 LA BEN PHAI,in3,IN4
///4 LA BEN TRAI,IN1,IN2
void readLinee()
{
      for (int i = 0; i < 6; i++) {
        aLDR[i] = 0;
        for (int j = 0; j < 100; j++) {
          aLDR[i] = aLDR[i] + analogRead(ldrPin[i]);
          delay(1);
        }
        avgLine[i] = aLDR[i] / 100;
      }
}
void readOut()
{
      for (int i = 0; i < 6; i++) {
        aLDR[i] = 0;
        for (int j = 0; j < 100; j++) {
          aLDR[i] = aLDR[i] + analogRead(ldrPin[i]);
          delay(1);
        }
        avgOut[i] = aLDR[i] / 100;
//        Serial.print(i);
//        Serial.print(": ");
//        Serial.print(avgOut[i]);
//        Serial.print(" ");
      }
//      Serial.println("");
    nguong();
}
void nguong() {
  //    Serial.print("nguong la ");
  for (int i = 0; i < 6; i++) {
    value[i] = (7 * avgLine[i] + 3*avgOut[i]) / 10;
  }
}

float hieu;
void pidCal()
{
  hieu = Err - Pre_Err;///////line thang Err = -0.75->0.75

  P = kp * Err;/////P =6*+-0.75=4.5 or -4.5
  D = kd * (hieu) * Inv_Sampling_Time;//0.16*+-0.75*100=+-12
  I += ki * Sampling_Time * (Err + Pre_Err) / 2000;//I=0 do ki =0
  x = (P + I + D);//x=+-16.5
  Pre_Err = Err;//=+-0.75
  if(2000<=millis()-time_servobom&&millis()-time_servobom<4000){
      servo1.write(130);
      //phai
  }
  if(4000<=millis()-time_servobom&&millis()-time_servobom<6000){
      //giua
      servo1.write(65);
  }
  if(6000<=millis()-time_servobom&&millis()-time_servobom<8000){
      //trai
      servo1.write(0);
  }
  if(8000<=millis()-time_servobom&&millis()-time_servobom<10000){
      //giua
      servo1.write(65);
      time_servobom=millis();
  }
  if(digitalRead(hongngoai)==0){
   if((unsigned long)(millis()-time_wait)>3000){ 
    if((unsigned long)(millis()-time_coi)>200){
      if(digitalRead(coi)==0){
        digitalWrite(coi,1);
      }
      else{
        digitalWrite(coi,0);
      }
      time_coi=millis();
    }
   }
  }
  
  if(digitalRead(hongngoai)==1){
    digitalWrite(coi,0);
    time_wait=millis();
  }
}
void motor_pid(){
  if(x<0){
     PWMA = PWM - x;
     if (PWMA > 255)  PWMA = 255;
     if (PWMA < 0)     PWMA = 0; 
     PWMB = PWM + x;
     if (PWMB > 255)  PWMB = 255;
     if (PWMB < 0)     PWMB = 0;
  }
  if(x>0){
     PWMA = PWM - x;
     if (PWMA > 255)  PWMA = 255;
     if (PWMA < 0)     PWMA = 0; 
     PWMB = PWM + x;
     if (PWMB > 255)  PWMB = 255;
     if (PWMB < 0)     PWMB = 0;    
  }
  if(x=0){
    PWMA=PWM;
    PWMB=PWM;
  }
//  Serial.print("PWMA: ");
//  Serial.print(PWMA);
//  Serial.print(" PWMB: ");
//  Serial.println(PWMB);
  ledcWrite(ledChannel0, PWMA);
  ledcWrite(ledChannel1,0);
  ledcWrite(ledChannel2, PWMB);  
  ledcWrite(ledChannel3,0);
}
