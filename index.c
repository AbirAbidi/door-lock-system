// C++ code
//
//1)when you first start the simulation , you will have to enter a new pass
//2)after entering the new pass , you will have 3 attempts to open the door
//otherwise it will be blocked 
//in case you wrote the correct pass the door will open up
#include<arduino.h>
#include <string.h>
#include<Keypad.h>
#include<LiquidCrystal.h>
#include<Servo.h>
Servo motor ;
char password[5];
char verfpassword[5];
int m =0; 
//String password  ;
//String verfpassword ;
// -----LCD---------
LiquidCrystal lcd (3,2,A0,A1,A2,A3);
// -----RGB LED----------
int redPin = 9;
int greenPin = A5;
int bluePin = A4;
// -----KEYPAD---------
const byte row = 4;
const byte col = 4;
//-----MATRICE--------
char rowcol[4][4] ={
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
					};
//----MATRICE WITH PINS------
byte rowPin[row] = {13,12,11,10};
byte colPin[col] = {8,7,6,5};

Keypad customKeypad = Keypad( makeKeymap(rowcol), rowPin, colPin, row, col); 
void setup()
{
  motor.attach(4);
  motor.write(0);
  Serial.begin(9600);
  lcd.begin(16,2);
  digitalWrite(redPin,OUTPUT);
  digitalWrite(greenPin,OUTPUT);
  digitalWrite(bluePin,OUTPUT);
  lcd.clear();
  lcd.setCursor(0,0);
  //fun();
}

void loop(){
fun();
}
void fun(){ 
  if(strlen(password) == 0){
    newpassword();
  }else{
    memset(verfpassword,0,strlen(verfpassword));
    existingPassword();
    };
   lcd.clear();
}

void ledRed(){
		lcd.write("access denied");
      	analogWrite(redPin,255);
        analogWrite(greenPin,0);
        analogWrite(bluePin,0);
        delay(1000);
  		analogWrite(redPin,0);
  lcd.clear();
}

void ledGreen(){
  motor.write(1450);
	lcd.write("access proved");
     	analogWrite(redPin,0);
        analogWrite(greenPin,255);
        analogWrite(bluePin,0);
      delay(2000);
  analogWrite(greenPin,0);
  motor.write(0);
  lcd.clear();
}
void newpassword(){
    int i = 0;
lcd.write("New pass");
    while(i<4){
      char customKey = customKeypad.getKey();
      if(customKey){
      password[i] = customKey ;
        verfpassword[i] =customKey;
        Serial.print(customKey);
        lcd.setCursor(9+i,0);
        lcd.print(customKey);
    i++;}
    }
  delay(1500);
  lcd.clear();
}

void existingPassword(){
  int k =0;
lcd.write("Enter pass");
    while(k<4){
      char customKey = customKeypad.getKey();
      if(customKey){
        lcd.setCursor(11+k,0);
      	lcd.write(customKey); 
        verfpassword[k] = customKey ;
          k++;}
      }
  lcd.clear();
    Serial.println(password);
    Serial.println(verfpassword);
  testPassword();
      };
      
    


  void testPassword(){
  int cmp =strcmp(password,verfpassword);
    if(cmp == 0){
    	ledGreen();
      m=0;
      delay(3000);
      fun();
     // exit(1);
    }else{
      m ++;
    	ledRed();
      if(m<3){ 
		   lcd.write("Oups!try again"); 
        delay(1000);
        lcd.clear();
         lcd.print(3-m);
        lcd.print(" ");
        lcd.write("attempts");
        delay(2000);
        lcd.clear();
        memset(verfpassword,0,strlen(verfpassword));
        existingPassword();
      }else{
       lcd.write("access blocked");
        delay(2000);
        exit(1);
  }
}
  }


















