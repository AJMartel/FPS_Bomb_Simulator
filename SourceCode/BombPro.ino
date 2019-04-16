#include <Wire.h> 
#include <Keypad.h>
//#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal.h>
/*
 Arduino Bomb Pro
 
 The circuit:
 * More info at : http://yin.mainstreamds.com/
 If you need some help mail me to yinbot@gmail.com
 
 created 4,Sep, 2010
 Modified 24 May 2014
 by Ignacio Lillo
 
 */

//LiquidCrystal_I2C lcd(0x38,16,2);
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {
    '1','2','3','a'                          }
  ,
  {
    '4','5','6','b'                          }
  ,
  {
    '7','8','9','c'                          }
  ,
  {
    '*','0','#','d'                          }
};

byte rowPins[ROWS] = {
  A4, A5, 13, 12}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {
  A0, A1, A2, A3
}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


char enteredText[8];
byte time[4];
byte refresh=0;//1 if is refreshed once time...
char password[8];
int key=-1;
char lastKey;
char var;
boolean passwordEnable=false;

//Buttons for lcd shield
char BT_RIGHT = '4';
char BT_UP = 'a';
char BT_DOWN = 'b';
char BT_LEFT = '6';
char BT_SEL = 'd';   // Ok key  
char BT_CANCEL = 'c';
char BT_DEFUSER = 'x';   // not implemented

//leds

const int REDLED = 11;
const int GREENLED = 10;
//const int BLUELED = 12;
//mosfet
boolean mosfetEnable = false;
const int mosfet = 9;
//IS VERY IMPORTANT THAT YOU TEST THIS TIME. BY DEFAULT IS IN 1 SEC. THAT IS NOT TOO MUCH. SO TEST IT!
const int MOSFET_TIME = 5000;

//TIME INTS
int GAMEHOURS = 0;
int GAMEMINUTES = 45;
int BOMBMINUTES = 4;
int ACTIVATESECONDS = 5;

boolean endGame = false;

boolean sdStatus = false; //search and destroy game enable used in config
boolean saStatus = false; //same but SAbotaghe
boolean doStatus = false; //for DEmolition
boolean start = true;
boolean defuseando;
boolean cancelando;
// SOUND TONES
boolean soundEnable = true;
int tonepin = 8; // Pin 13 for the sound
int tonoPitido = 3000;
int tonoAlarma1 = 700;
int tonoAlarma2 = 2600;
int tonoActivada = 1330;
int errorTone = 100;


char* menu1[]={"Search&Destroy","Sabotage","Domination"      };
char* menu2[]={"Game Config","Sound Config", "Mosfet Test", "Auto Test"      };   
char* GAME_TIME="Game Time:";
char* BOMB_TIME="Bomb Time:";
char* ZERO_MINUTES="00 minutes";
char* ARM_TIME="Arm Time:";
char* ZERO_SECS="00 seconds";
char* ENABLE_SOUND="Enable Sound?";
char* YES_OR_NOT="A : Yes B : No";
char* ENABLE_MOSFET="Enable Mosfet?";
char* ENABLE_CODE="Enable Code Arm?";
char* GAME_TIME_TOP="GAME TIME";
char* ARMING_BOMB = "ARMING BOMB";
char* ENTER_CODE = "Enter Code";
char* CODE_ERROR = "Code Error!";
char* BOMB_ARMED = "BOMB ARMED";
char* DETONATION_IN = "DETONATION IN";
char* DISARMING = "DISARMING BOMB" ;
char* DISARM = "DISARMING";
char* GAME_OVER = " GAME OVER! ";
char* DEFENDERS_WIN = " DEFENDERS WIN ";

unsigned long iTime;
unsigned long timeCalcVar;
unsigned long redTime;
unsigned long greenTime;
unsigned long iZoneTime;//initial time for zone
byte team=0; // 0 = neutral, 1 = green team, 2 = red team

void setup(){
  lcd.begin(16, 2);
  Serial.begin(9600);
  //  lcd.init();                      // initialize the lcd 
  //  lcd.backlight();
  lcd.setCursor(3,0);
  tone(tonepin,2400,30);
  lcd.print("IGNIS ONE");// you can add your team name or someting cool
  lcd.setCursor(0,1);
  lcd.print(" AIRSOFT SYSTEM");// you can add your team name or someting cool
  keypad.setHoldTime(50);
  keypad.setDebounceTime(50);
  keypad.addEventListener(keypadEvent);
  delay(2000);
  pinMode(GREENLED, OUTPUT);     
//  pinMode(8, OUTPUT);  
//  digitalWrite(8,HIGH);
  pinMode(REDLED, OUTPUT); 
  pinMode(mosfet, OUTPUT);  
  // CONFIGURE THE BARS OF PROGRESS BAR
  byte bar1[8] = {
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
  };
  byte bar2[8] = {
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
  };
  byte bar3[8] = {
    B11100,
    B11100,
    B11100,
    B11100,
    B11100,
    B11100,
    B11100,
    B11100,
  };
  byte bar4[8] = {
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
  };
  byte bar5[8] = {
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
  };
  byte up[8] = {
    B00000,
    B00100,
    B01110,
    B11111,
    B11111,
    B00000,
    B00000,
  };

  byte down[8] = {
    B00000,
    B00000,
    B11111,
    B11111,
    B01110,
    B00100,
    B00000,
  };
  lcd.createChar(0,bar1);
  lcd.createChar(1,bar2);
  lcd.createChar(2,bar3);
  lcd.createChar(3,bar4);
  lcd.createChar(4,bar5);
  lcd.createChar(5,up);
  lcd.createChar(6,down);
}

void loop(){
  menuPrincipal();
}

//##################MENUS###############################

void menuPrincipal(){   //MAIN MENU

  digitalWrite(GREENLED, LOW); 
  digitalWrite(REDLED, LOW); 

  //   if whe start a new game from another we need to restart propertly this variables
  saStatus=false;
  sdStatus=false;
  doStatus=false;
  //Draw menu
  cls();//clear lcd and set cursor to 0,0
  int i=0;
 // HERE YOU CAN ADD MORE ITEMS ON THE MAIN MENU
  lcd.print(menu1[i]);
  lcd.setCursor(15,1);
  checkArrows(i,2);
  while(1){

    var = keypad.waitForKey();
    if(var == BT_UP && i>0){
      tone(tonepin,2400,30);
      i--;
      cls();
      lcd.print(menu1[i]);
      checkArrows(i,2);
      delay(50);
    }
    if(var == BT_DOWN && i<2){
      tone(tonepin,2400,30);
      i++;
      cls(); 
      lcd.print(menu1[i]);    
      checkArrows(i,2);
      delay(50);
    }

    if(var == BT_SEL){
      tone(tonepin,2400,30);
      cls();
      switch (i){

      case 0:
        sdStatus=true;
        configQuickGame();
        startGameCount();
        search();
        break;
      case 1: 
        saStatus=true;
        configQuickGame();
        startGameCount();
        sabotage();
        break;
      case 2:

        doStatus=true;
        configQuickGame();
        startGameCount();
        domination();
        break;
      case 3:
        config();
        break;

      }
    }
  }
}

void drawPorcent(byte porcent){
  //TODO: Optimize this code 
  int aDibujar=(8*porcent)/10;
  lcd.setCursor(0,1);

  if(aDibujar<5)
  {
    switch(aDibujar){
    case 0:
      break;
    case 1:
      lcd.write((uint8_t)0);
      break;
    case 2:
      lcd.write(1);
      break;
    case 3:
      lcd.write(2);
      break;
    case 4:
      lcd.write(3);
      break;
    }
  }
  while(aDibujar>=5){
    if(aDibujar>=5)
    {
      lcd.write(4);
      aDibujar-=5;
    }
    if(aDibujar<5)
    {
      switch(aDibujar){
      case 0:
        break;
      case 1:
        lcd.write((uint8_t)0);
        break;
      case 2:
        lcd.write(1);
        break;
      case 3:
        lcd.write(2);
        break;
      case 4:
        lcd.write(3);
        break;
      }
    }
  }
}
void cls(){
  lcd.clear();
  lcd.setCursor(0,0);
}

void printTime(unsigned long minutos, unsigned long aTiempo){

  timeCalcVar=(minutos-aTiempo/60000);
  //Hours
  
  if(timeCalcVar/60<1 && refresh==0){
      lcd.clear();
      refresh=1;
      delay(100);
      lcd.setCursor(3,1);
  }
   
  if(timeCalcVar/60>=1){
    
    if(timeCalcVar/60<10)
  {
    
    lcd.setCursor(2,1);
    lcd.print("0");
    lcd.print(timeCalcVar/60);
  }
  else
  {
    lcd.print(timeCalcVar/60);
  }
  
  lcd.print(":");
  
  }
  //minutes
  if((timeCalcVar%60)<10)
  {
    lcd.print("0");
    lcd.print(timeCalcVar%60);
  }
  else
  {
    lcd.print(timeCalcVar%60);
  }
  lcd.print(":");
  //seconds
  timeCalcVar=(aTiempo/1000);
  if((59-(timeCalcVar%60))<10)
  {
    lcd.print("0");
    lcd.print(59-(timeCalcVar%60));
  }
  else
  {
    lcd.print(59-(timeCalcVar%60));
  }
  lcd.print(":");
  //this not mach with real time, is just a effect, it says 999 because millis%1000 sometimes give 0 LOL
  lcd.print(999-(millis()%1000));
}

void printTimeDom(unsigned long aTiempo, boolean showMillis){
  //minutes
  if((aTiempo/60000)<10)
  {
    lcd.print("0");
    lcd.print(aTiempo/60000);
  }
  else
  {
    lcd.print(aTiempo/60000);
  }
  lcd.print(":");
  //seconds
  if(((aTiempo/1000)%60)<10)
  {
    lcd.print("0");
    lcd.print((aTiempo/1000)%60);
  }
  else
  {
    lcd.print((aTiempo/1000)%60);
  }
  if(showMillis){
    lcd.print(":");
    //this not mach with real time, is just a effect, it says 999 because millis%1000 sometimes give 0 LOL
      lcd.print(999-millis()%1000);

  }
}


void startGameCount(){
  cls();
  lcd.setCursor(1,0);
  lcd.print("Ready to Begin");
  lcd.setCursor(0,1);
  lcd.print("Push ANY Button");
  keypad.waitForKey();//if you press a button game start

  cls();
  lcd.setCursor(1,0);
  lcd.print("Starting Game");
  for(int i = 5; i > 0 ; i--){ // START COUNT GAME INIT
    lcd.setCursor(5,1);
    tone(tonepin,2000,100);
    lcd.print("IN ");
    lcd.print(i);
    delay(1000);
  }
  cls();
}

void checkArrows(byte i,byte maxx ){

  if(i==0){
    lcd.setCursor(15,1);
    lcd.write(6); 
  }
  if(i==maxx){  
    lcd.setCursor(15,0);
    lcd.write(5);
  }
  if(i>0 && i<maxx){
    lcd.setCursor(15,1);
    lcd.write(6);
    lcd.setCursor(15,0);
    lcd.write(5);  
  }
}

void activateMosfet(){

  //lcd.print("Mosfet ON!");
  digitalWrite(mosfet, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(MOSFET_TIME);   // wait for 4 second
  //lcd.print("Mosfet OFF!");
  digitalWrite(mosfet, LOW);

}

void config(){
  //Draw menu
  lcd.clear();
  lcd.setCursor(0, 0);
  int i=0;
  
  delay(500);
  lcd.print(menu2[i]);
  checkArrows(i,3);

  while(1){
    var=keypad.waitForKey();
    if(var == BT_UP && i>0){
      tone(tonepin,2400,30);
      i--;
      lcd.clear();  
      lcd.print(menu2[i]);
      checkArrows(i,3);
      delay(50);

    }
    if(var == BT_DOWN && i<3){
      tone(tonepin,2400,30);
      i++;
      lcd.clear();  
      lcd.print(menu2[i]);
      checkArrows(i,3);
      delay(50);
    }
    if(var == BT_CANCEL){
      tone(tonepin,2400,30);
      menuPrincipal();
    }
    if(var == BT_SEL){
      tone(tonepin,2400,30);
      lcd.clear();
      switch (i){

      case 0:
        //gameConfigMenu();
        break;

      case 1:
        //soundConfigMenu();
        break;

      case 2:
        cls();
        lcd.print("Mosfet ON!");
        digitalWrite(mosfet, HIGH);   // turn the LED on (HIGH is the voltage level)
        delay(4000);   // wait for 4 second
        cls();
        lcd.print("Mosfet OFF!");
        digitalWrite(mosfet, LOW);
        delay(2000);
        config();
        break;        

      }
    }
  }
}

void configQuickGame(){

  cls();
  //GAME TIME
  if(sdStatus || doStatus || saStatus){
    menu1:
    cls();
    lcd.print(GAME_TIME);
    delay(100);
    lcd.setCursor(0,1);
    lcd.print("00:00 hh:mm");
    lcd.cursor();
    lcd.blink();
    lcd.setCursor(0,1);
    byte var2=0;
    for(int i=0;i<4;i++){ 
      while(1){
        if(i==2 && var2==0){
          lcd.print(":");
          var2=1;
        }

        byte varu= getRealNumber();
        if(varu !=11){

          time[i] =  varu;
          Serial.print(varu);


          lcd.print(varu);
          tone(tonepin,2400,30);

          break;
        }
      }  
    }
    lcd.noCursor();
    lcd.noBlink();
    lcd.setCursor(13,1);
    lcd.print("ok?");
    //zona donde pasamos los items a
    //redibujar
    while(1){
      var = keypad.waitForKey();
      if(var == 'd') // Cancel or Back Button :')
      {
        tone(tonepin,2400,30);
        GAMEMINUTES= ((time[0]*600)+(time[1]*60)+(time[2]*10)+(time[3]));
        break;
      }    
  if(var == 'c') // Cancel or Back Button :')
      {
        tone(tonepin,2400,30);
        goto menu1;
      }           
    }
    tone(tonepin,2400,30);
    cls();
  }
  //BOMB TIME
  if(sdStatus || saStatus){
 
    menu2:
    cls();
    lcd.print(BOMB_TIME);
    delay(100);
    lcd.setCursor(0,1);
    lcd.print(ZERO_MINUTES);
    lcd.cursor();
    lcd.blink();
    lcd.setCursor(0,1);
    for(int i=0;i<2;i++){ 
      while(1){
        byte varu= getRealNumber();
        if(varu !=11){
          time[i] =  varu;
          lcd.print(varu);
          tone(tonepin,2400,30);
          break;
        }
      }  
    }
    lcd.noCursor();
    lcd.noBlink();   
    lcd.setCursor(13,1);
    lcd.print("ok?");
    //zona donde pasamos los items a
    //redibujar
    while(1){
      var = keypad.waitForKey();
      if(var == 'd') // Cancel or Back Button :')
      {
        tone(tonepin,2400,30);
        BOMBMINUTES= ((time[0]*10)+(time[1]));
        break;
      }    
  if(var == 'c') // Cancel or Back Button :')
      {
        tone(tonepin,2400,30);
        goto menu2;
      }           
    }
    tone(tonepin,2400,30);
    cls();
  }
  cls();
  //ARMING TIME
  if(sdStatus || doStatus || saStatus){
        
    menu3:
    cls();
    lcd.print(ARM_TIME);
    delay(100);
    lcd.setCursor(0,1);
    lcd.print(ZERO_SECS);
    lcd.cursor();
    lcd.blink();
    lcd.setCursor(0,1);
    for(int i=0;i<2;i++){ 
      while(1){
        byte varu= getRealNumber();
        if(varu !=11){
          time[i] =  varu;
          lcd.print(varu);
          tone(tonepin,2400,30);
          break;
        }
      }  
    }
    lcd.noCursor();
    lcd.noBlink(); 
    lcd.setCursor(13,1);
    lcd.print("ok?");  
    
    //zona donde pasamos los items a
    //redibujar
    while(1){
      var = keypad.waitForKey();
      if(var == 'd') // Cancel or Back Button :')
      {
        tone(tonepin,2400,30);
        ACTIVATESECONDS= ((time[0]*10)+(time[1]));
        break;
      }    
  if(var == 'c') // Cancel or Back Button :')
      {
        tone(tonepin,2400,30);
        goto menu3;
      }           
    }
    tone(tonepin,2400,30);
    cls();
  }
  //Want sound??
  if(sdStatus || saStatus || doStatus){
    cls();
    lcd.print(ENABLE_SOUND);
    lcd.setCursor(0,1);
    lcd.print(YES_OR_NOT);

    while(1)
    {
      var = keypad.waitForKey();
      if(var == 'a' ){
        soundEnable=true;
        tone(tonepin,2400,30);
        break;
      }  

      if(var == 'b' ){
        soundEnable=false;
        tone(tonepin,2400,30);
        break;
      }  
    }
  } 
  //Activate Mosfet at Terrorist game ends??? Boom!

  if(sdStatus || saStatus){
    cls();
    lcd.print(ENABLE_MOSFET);
    lcd.setCursor(0,1);
    lcd.print(YES_OR_NOT);
    while(1)
    {
      var = keypad.waitForKey();
      if(var == 'a' ){
        mosfetEnable=true;
        tone(tonepin,2400,30);
        break;
      }  
      if(var == 'b' ){
        mosfetEnable=false;
        tone(tonepin,2400,30);
        break;
      }  
    } 
  }
  //You Want a password enable-disable game?
  if(sdStatus || saStatus){
    cls();
    lcd.print(ENABLE_CODE);
    lcd.setCursor(0,1);
    lcd.print(YES_OR_NOT);

    while(1)
    {
      var = keypad.waitForKey();
      if(var == 'a' ){
        tone(tonepin,2400,30);
        setNewPass();
        passwordEnable = true;
        break;
      }  
      if(var == 'b' ){
        tone(tonepin,2400,30);
        passwordEnable = false;
        break;
      }  
    } 
    tone(tonepin,2400,30);
  }  
  //Continue the game :D
}

void keypadEvent(KeypadEvent key){
  switch (keypad.getState()){
    case PRESSED:
      switch (key){

      }
    break;
    case RELEASED:
      switch (key){
         case 'd': defuseando= false;
         //Serial.println("d Releases");
         break;
         case 'c': cancelando=false;
         //Serial.println("c Releases");
         break;
      }
    break;
    case HOLD:
      switch (key){
        case 'd': defuseando= true;
        //Serial.println("d hold");
        break;
        case 'c': cancelando=true;
        //Serial.println("c hold");
        break;
      }
    break;
  }
}

void disarmedSplash(){
  endGame = false;
  digitalWrite(REDLED, LOW); 
  digitalWrite(GREENLED, LOW);
  if(sdStatus || saStatus){
    lcd.clear();
    lcd.setCursor(2,0);
    lcd.print("BOMB DISARMED");
    lcd.setCursor(3,1);
    lcd.print("GOODS WIN");
    digitalWrite(GREENLED, HIGH);  
    delay(5000);
    digitalWrite(GREENLED, LOW); 
  }
  //end code
  lcd.clear();
  lcd.print("Play Again?");
  lcd.setCursor(0,1);
  lcd.print("A : Yes B : No");
  digitalWrite(REDLED, LOW);  
  digitalWrite(GREENLED, LOW); 
  while(1)
  {
    var = keypad.waitForKey();
    if(var == 'a' ){
      tone(tonepin,2400,30);
      //We have two options, search & destroy and sabotaje play again options so!
      if(sdStatus){
        startGameCount();
        search();
      }
      if(saStatus){
        saStatus=true;
        startGameCount();
        start=true; //to set iTime to actual millis() :D
        sabotage();
      }
    }  
    if(var == 'b' ){
      tone(tonepin,2400,30);
      menuPrincipal();
      break;
    }  
  } 
}

void explodeSplash(){
  digitalWrite(REDLED, LOW);  
  digitalWrite(GREENLED, LOW); 
  cls();
  delay(100);
  endGame = false;
  lcd.setCursor(1,0);
  lcd.print("TERRORISTS WIN");
  lcd.setCursor(4,1);
  lcd.print("GAME OVER");
  for(int i = 200; i>0; i--)// this is the ultra hi definition explosion sound xD
  {
    tone(tonepin,i);
    delay(20);
  }
  noTone(tonepin);
  if(mosfetEnable){
    activateMosfet(); 
  }
  delay(5000);
  cls();

  //end code
  lcd.print("Play Again?");
  lcd.setCursor(0,1);
  lcd.print("A : Yes B : No");
  while(1)
  {
    var = keypad.waitForKey();
    if(var == 'a' ){
      tone(tonepin,2400,30);
      //We have two options, search & destroy and sabotaje play again options so!
      if(sdStatus){
        startGameCount();
        search();
      }
      if(saStatus){
        saStatus=true;
        startGameCount();
        start=true; //to set iTime to actual millis() :D
        sabotage();
      }
    }  
    if(var == 'b' ){
      tone(tonepin,2400,30);
      menuPrincipal();

      break;
    }  
  } 
}

//Used to get keys, here you can configure how works the input without modify the other code
boolean isPressed(char key) 
{

//  Serial.print("checkeando= ");
//  Serial.print(key);

//  Serial.print(" estado = ");
//  Serial.print(keypad.getState());

//  Serial.print(" estado = ");
//  Serial.print(keypad.getKey());

  if(keypad.getKey() == key)
  {
//    Serial.println(" TRUE");
    return true;
  }
  else if(keypad.getKey() == key && keypad.getState() == 2)
  {
//    Serial.print(" Hold!!");
//    Serial.println(key);
    return true;
  }
//  Serial.println(" Falso");
  return false;
}

//This fuction compare enteredText[8] and password[8] variables
boolean comparePassword(){

  for(int i=0;i<8;i++){
    if(enteredText[i]!=password[i])return false;
  }
  return true;

}

//Set the password variable
void setCode(){

  lcd.setCursor(0, 1);
  for(int i=0;i<8;i++){
    while(1){
      var= getNumber();
      if(var !='x'){
        enteredText[i] = var;

        if (i != 0){
          lcd.setCursor(i-1,1);
          lcd.print("*");
          lcd.print(var);
        }
        else
        {
          lcd.print(var);
        }
        tone(tonepin,2400,30);
        break;
      }
    }
  }
}
void setCodeTime(){

  timeCalcVar=millis();

  for(int i=0;i<8;i++){
    while(1){
      if(5000+timeCalcVar-millis()<=100){
        enteredText[i]='x';
        break;
      }

      lcd.setCursor(11,0);
      printTimeDom(5000+timeCalcVar-millis(),false);

      var= getNumber();
      if(var !='x'){
        enteredText[i] = var;

        if (i != 0){
          lcd.setCursor(i-1,1);
          lcd.print("*");
          lcd.print(var);
        }
        else
        {
          lcd.print(var);
        }
        tone(tonepin,2400,30);
        break;
      }
    }
  }
}
void setPass(){
  lcd.setCursor(0, 1);

  for(int i=0;i<8;i++){ 
    while(1){
      var= getNumber();
      if(var !='x'){
        password[i] =  var;
        if (i != 0){
          lcd.setCursor(i-1,1);
          lcd.print("*");
          lcd.print(var);
        }
        else
        {
          lcd.print(var);
        }
        tone(tonepin,2400,30);
        break;
      }
    }  
  }
}

void setNewPass(){

  while(1){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Enter New Pass");
    setPass();

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Retype Pass");

    setCode();

    if(comparePassword()){

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Password Set OK!");
      delay(2000); 
      break; 
    }
    else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("ERROR Dont Match!");
      if(soundEnable)tone(tonepin,errorTone,200);
      delay(2000); 

    }
  }
}
//Whait until a button is pressed is is a number return the number 'char' if not return x



char getNumber(){

  while(1){
    var = keypad.getKey();

    if (var){//
      switch (var) {
      case 'a': 
        return 'x';
        break;
      case 'b': 
        return 'x';
        break;

      case 'c': 
        return 'x';
        break;
      case 'd': 
        return 'x';
        break;
      case '*': 
        return 'x';
        break;
      case '#': 
        return 'x';
        break;
      default:
        return var;
        break;
      }
    }
    return 'x';
  }
}

byte getRealNumber(){

  while(1){
    var = keypad.waitForKey();

    if (var){//
      switch (var) {
      case '1': 
        return 1;
        break;
      case '2': 
        return 2;
        break;

      case '3': 
        return 3;
        break;
      case '4': 
        return 4;
        break;
      case '5': 
        return 5;
        break;
      case '6': 
        return 6;
      case '7': 
        return 7;
        break;
      case '8': 
        return 8;
        break;
      case '9': 
        return 9;
        break;
        case '0': 
        return 0;
        break;
        
      default:
        return 11;
        break;
      }

    }
    return 11;
  }
}

void search(){
  cls();
  digitalWrite(REDLED, LOW); 
  digitalWrite(GREENLED, LOW);   
  //SETUP INITIAL TIME 
  int minutos = GAMEMINUTES-1;
  unsigned long iTime=millis(); //  initialTime in millisec 
  unsigned long aTime;
  //var='o';

  //Starting Game Code
  while(1){  // this is the important code, is a little messy but works good.

    //If you fail disarm. 
    if(endGame){
      endSplash();
    }

    //Code for led blinking
    timeCalcVar=(millis()- iTime)%1000;
    if(timeCalcVar >= 0 && timeCalcVar <= 50)
    {
      digitalWrite(GREENLED, HIGH);  
    }
    if(timeCalcVar >= 90 && timeCalcVar <= 130)
    {    
      digitalWrite(GREENLED, LOW);  
    }

    lcd.setCursor(3,0);
    lcd.print(GAME_TIME_TOP);
    aTime=millis()- iTime;
    lcd.setCursor(3,1);

    //PRINT TIME ON LCD

    printTime(minutos, aTime);

    //###########################CHECKINGS##################

    //Check If Game End
    if(minutos-aTime/60000==0 && 59-((aTime/1000)%60)==0)
    {
      endSplash();
    }
    //Serial.println(keypad.getKey());
    //USED IN PASSWORD GAME 
    if('d' == keypad.getKey() && passwordEnable){
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print(ARMING_BOMB);
      delay(1000);//a little delay to think in the password
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(ENTER_CODE);

      setCodeTime();// we need to set the comparation variable first it writes on enteredText[]

      //then compare :D

      if(comparePassword()){
        destroy();
      }        
      lcd.clear();
      lcd.setCursor(3,0);
      lcd.print(CODE_ERROR);
      if(soundEnable)tone(tonepin,errorTone,200);
      delay(500);
      cls();
    }
    //Check If Is Activating
    while(defuseando && !passwordEnable)
    {
      digitalWrite(GREENLED, LOW);
      lcd.clear();
      lcd.setCursor(2,0);
      lcd.print(ARMING_BOMB);
      lcd.setCursor(0,1);
      unsigned int percent=0;
      unsigned long xTime=millis(); //start disabling time
      while(defuseando)
      {
        keypad.getKey();
        timeCalcVar = (millis()- xTime)%1000;

        if( timeCalcVar >= 0 && timeCalcVar <= 40)
        {
          digitalWrite(REDLED, HIGH);  
          if(soundEnable)tone(tonepin,tonoAlarma1,200);
        }
        if(timeCalcVar >= 480 && timeCalcVar <= 520)
        {
          if(soundEnable)tone(tonepin,tonoAlarma2,200);
          digitalWrite(REDLED, LOW);
        }

        unsigned long seconds= millis() - xTime;
        percent = (seconds)/(ACTIVATESECONDS*10);
        drawPorcent(percent);

        if(percent >= 100)
        {
          digitalWrite(GREENLED, LOW);
          destroy();// jump to the next gamemode
        }
      }
      cls();
      digitalWrite(REDLED, LOW);  

    }
  }
}

void destroy(){
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print(BOMB_ARMED);
  delay(1000);
  int minutos=BOMBMINUTES-1;
  unsigned long iTime=millis();
  unsigned long aTime;
  int largoTono = 50;

  //MAIN LOOP
  while(1){

    //If you fail disarm. 
    if(endGame){
      explodeSplash();
    }

    //Led Blink

    timeCalcVar=(millis()- iTime)%1000;
    if(timeCalcVar >= 0 && timeCalcVar <= 40)
    {
      digitalWrite(REDLED, HIGH);  
      if(soundEnable)tone(tonepin,tonoActivada,largoTono);
    }
    if(timeCalcVar >= 180 && timeCalcVar <= 220){
      digitalWrite(REDLED, LOW);  
    }
    //Sound 
    aTime= millis()- iTime;
    timeCalcVar=(millis()- iTime)%1000;
    if(timeCalcVar >= 245 && timeCalcVar <= 255 && minutos-aTime/60000<2 && soundEnable)tone(tonepin,tonoActivada,largoTono);
    if(timeCalcVar >= 495 && timeCalcVar <= 510 && minutos-aTime/60000<4 && soundEnable)tone(tonepin,tonoActivada,largoTono);
    if(timeCalcVar >= 745 && timeCalcVar <= 760 && minutos-aTime/60000<2 && soundEnable)tone(tonepin,tonoActivada,largoTono);
    if( minutos-aTime/60000==0 && 59-((aTime/1000)%60) < 10)largoTono = 300;

    lcd.setCursor(1,0);
    lcd.print(DETONATION_IN);
    //Passed Time

    lcd.setCursor(3,1);

    ////////HERE ARE THE TWO OPTIONS THAT ENDS THE GAME///////////

    ////TIME PASED AWAY AND THE BOMB EXPLODES
    if(minutos-aTime/60000==0 && 59-((aTime/1000)%60)==0)// Check if game ends
    {
      explodeSplash();
    }
    //print time

    printTime(minutos, aTime);

    //// SECOND OPTION: YOU PRESS DISARMING BUTTON  

    //IF IS A PASSWORD GAME 

    if('d' == keypad.getKey() && passwordEnable){

      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print(DISARMING);
      delay(1000);//a little delay to think in the password

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(ENTER_CODE);

      setCodeTime();// we need to set the compare variable first

      //then compare :D

      if(comparePassword()){
        disarmedSplash();
      }        
      lcd.clear();
      lcd.setCursor(3,0);
      lcd.print(CODE_ERROR);
      if(soundEnable)tone(tonepin,errorTone,200);
      delay(500);
      cls();
    }

    if(defuseando && !passwordEnable)// disarming bomb
    {
      lcd.clear();
      digitalWrite(REDLED, LOW);  
      lcd.setCursor(3,0);
      lcd.print(DISARM);
      lcd.setCursor(0,1);
      unsigned int percent=0;
      unsigned long xTime=millis();
      while(defuseando)
      {
        keypad.getKey();
        //check if game time runs out during the disabling
        aTime= millis()- iTime;
        if((minutos-aTime/60000==0 && 59-((aTime/1000)%60)==0) || minutos-aTime/60000>4000000000){ 
          endGame = true;
        }
        timeCalcVar=(millis()- xTime)%1000;
        if(timeCalcVar>= 0 && timeCalcVar <= 20)
        {
          digitalWrite(GREENLED, HIGH);  
          if(soundEnable)tone(tonepin,tonoAlarma1,200);
        }
        if(timeCalcVar >= 480 && timeCalcVar <= 500)
        {
          if(soundEnable)tone(tonepin,tonoAlarma2,200);
          digitalWrite(GREENLED, LOW);  
        }
        unsigned long seconds=(millis()- xTime);
        percent= seconds/(ACTIVATESECONDS*10);
        drawPorcent(percent);  

        //BOMB DISARMED GAME OVER
        if(percent >= 100)
        {
          disarmedSplash();   
        }
      }
      digitalWrite(REDLED, LOW); 
      digitalWrite(GREENLED, LOW);
      cls();
    }
  }
}

void endSplash(){
  lcd.clear();
  while(1){
    lcd.print(GAME_OVER);
    lcd.setCursor(0,1);
    lcd.print(DEFENDERS_WIN);  

    for(int i = 1000; i>200; i--){
      if(soundEnable)tone(tonepin,i);
      delay(5);
    }
    noTone(tonepin);
    delay(5000);
    cls();
    menuPrincipal();
  } 

}


void sabotage(){
  cls();
  digitalWrite(REDLED, LOW); 
  digitalWrite(GREENLED, LOW);   
  //SETUP INITIAL TIME 
  int minutos = GAMEMINUTES-1;

  
  if(start){
  iTime=millis(); //  initialTime in millisec 
  start=false;
  }
  
  unsigned long aTime;

  //Starting Game Code
  while(1){  // this is the important code, is a little messy but works good.

    //Code for led blinking
    timeCalcVar=(millis()- iTime)%1000;
    if(timeCalcVar >= 0 && timeCalcVar <= 50)
    {
      digitalWrite(GREENLED, HIGH);  
    }
    if(timeCalcVar >= 90 && timeCalcVar <= 130)
    {    
      digitalWrite(GREENLED, LOW);  
    }

    lcd.setCursor(3,0);
    lcd.print(GAME_TIME);
    aTime=millis()- iTime;
    lcd.setCursor(3,1);

    //PRINT TIME ON LCD

    printTime(minutos, aTime);

    //###########################CHECKINGS##################

    //Check If Game End
    if(minutos-aTime/60000==0 && 59-((aTime/1000)%60)==0)
    {
      lcd.clear();
      while(1){
        lcd.print(GAME_OVER);
        lcd.setCursor(0,1);
        lcd.print(DEFENDERS_WIN);  

        for(int i = 1000; i>200; i--){
          if(soundEnable)tone(tonepin,i);
          delay(5);
        }
        noTone(tonepin);
        delay(5000);
        cls();
        menuPrincipal();
      }
    }
    //USED IN PASSWORD GAME 
    if('d' == keypad.getKey() && passwordEnable){
      lcd.clear();
      lcd.setCursor(2,0);      
      lcd.print(ARMING_BOMB);
      delay(1000);//a little delay to think in the password
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(ENTER_CODE);

      setCode();// we need to set the compare variable first

      //then compare :D

      if(comparePassword()){
        destroySabotage();
      }        
      lcd.clear();
      lcd.setCursor(2,0);
      lcd.print(CODE_ERROR);
      if(soundEnable)tone(tonepin,errorTone,200);
      delay(500);
      cls();
    }

    //Check If Is Activating
    while(defuseando && !passwordEnable)
    {
      keypad.getKey();
      cls();
      digitalWrite(GREENLED, LOW);
      lcd.clear();
      lcd.setCursor(2,0);
      lcd.print(ARMING_BOMB);
      lcd.setCursor(0,1);
      unsigned int percent=0;
      unsigned long xTime=millis(); //start disabling time
      while(defuseando)
      {
        keypad.getKey();
        timeCalcVar = (millis()- xTime)%1000;

        if( timeCalcVar >= 0 && timeCalcVar <= 40)
        {
          digitalWrite(REDLED, HIGH);  
          if(soundEnable)tone(tonepin,tonoAlarma1,200);
        }
        if(timeCalcVar >= 480 && timeCalcVar <= 520)
        {
          if(soundEnable)tone(tonepin,tonoAlarma2,200);
          digitalWrite(REDLED, LOW);
        }
        unsigned long seconds= millis() - xTime;
        percent = (seconds)/(ACTIVATESECONDS*10);
        drawPorcent(percent);

        if(percent >= 100)
        {
          digitalWrite(GREENLED, LOW);
          destroySabotage();// jump to the next gamemode
        }
      }
      cls();
      digitalWrite(REDLED, LOW);  
    }
  }
}

void destroySabotage(){
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print(BOMB_ARMED);
  delay(1000);
  int minutos=BOMBMINUTES-1;
  unsigned long iTime=millis();
  unsigned long aTime;
  int largoTono = 50;

  //MAIN LOOP
  while(1){

    //If you fail disarm. 
    if(endGame){
      explodeSplash();
    }

    //Led Blink

    timeCalcVar=(millis()- iTime)%1000;
    if(timeCalcVar >= 0 && timeCalcVar <= 40)
    {
      digitalWrite(REDLED, HIGH);  
      if(soundEnable)tone(tonepin,tonoActivada,largoTono);
    }
    if(timeCalcVar >= 180 && timeCalcVar <= 220){
      digitalWrite(REDLED, LOW);  
    }
    //Sound 

    timeCalcVar=(millis()- iTime)%1000;
    aTime= millis()- iTime;
    if(timeCalcVar >= 245 && timeCalcVar <= 255 && minutos-aTime/60000<2 && soundEnable)tone(tonepin,tonoActivada,largoTono);
    if(timeCalcVar >= 495 && timeCalcVar <= 510 && minutos-aTime/60000<4 && soundEnable)tone(tonepin,tonoActivada,largoTono);
    if(timeCalcVar >= 745 && timeCalcVar <= 760 && minutos-aTime/60000<2 && soundEnable)tone(tonepin,tonoActivada,largoTono);
    if( minutos-aTime/60000==0 && 59-((aTime/1000)%60) < 10)largoTono = 300;

    lcd.setCursor(1,0);
    lcd.print(DETONATION_IN);
    //Passed Time
    
    lcd.setCursor(3,1);

    ////////HERE ARE THE TWO OPTIONS THAT ENDS THE GAME///////////

    ////TIME PASED AWAY AND THE BOMB EXPLODES
    if(minutos-aTime/60000==0 && 59-((aTime/1000)%60)==0)// Check if game ends
    {
      explodeSplash();
    }
    //print time
    printTime(minutos, aTime);

    //// SECOND OPTION: YOU PRESS DISARMING BUTTON  

    //IF IS A PASSWORD GAME 

    if('d' == keypad.getKey() && passwordEnable){

      cls();
      digitalWrite(REDLED, LOW);  
      digitalWrite(GREENLED, HIGH); 
      lcd.print(DISARMING);
      delay(1000);//a little delay to think in the password

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(ENTER_CODE);

      setCode();// we need to set the compare variable first

      //then compare :D

      if(comparePassword()){
        sabotage();
      }        
      lcd.clear();
      lcd.setCursor(2,0);
      lcd.print(CODE_ERROR);
      if(soundEnable)tone(tonepin,errorTone,200);
      delay(500);
      cls();
    }

    if(defuseando && !passwordEnable)// disarming bomb
    {
      lcd.clear();
      digitalWrite(REDLED, LOW);
      lcd.setCursor(3,0);
      lcd.print(DISARM);
      lcd.setCursor(0,1);
      unsigned int percent=0;
      unsigned long xTime=millis();
      while(defuseando)
      {
        keypad.getKey();
        //check if game time runs out during the disabling
        aTime= millis()- iTime;
        if((minutos-aTime/60000==0 && 59-((aTime/1000)%60)==0) || minutos-aTime/60000>4000000000){ 
          endGame = true;
        }
        timeCalcVar=(millis()- xTime)%1000;
        if(timeCalcVar>= 0 && timeCalcVar <= 20)
        {
          digitalWrite(GREENLED, HIGH);  
          if(soundEnable)tone(tonepin,tonoAlarma1,200);
        }
        if(timeCalcVar >= 480 && timeCalcVar <= 500)
        {
          if(soundEnable)tone(tonepin,tonoAlarma2,200);
          digitalWrite(GREENLED, LOW);  
        }
        unsigned long seconds=(millis()- xTime);
        percent= seconds/(ACTIVATESECONDS*10);
        drawPorcent(percent);  

        //BOMB DISARMED GAME OVER
        if(percent >= 100)
        {
          sabotage();   
        }
      }
      digitalWrite(REDLED, LOW); 
      digitalWrite(GREENLED, LOW);
      cls(); 
    }
  }
}
  
void domination(){

  //SETUP INITIAL TIME 
  int minutos = GAMEMINUTES-1;
  boolean showGameTime=true;
  unsigned long a;
  unsigned long iTime=millis(); //  initialTime in millisec 
  unsigned long aTime;
 
  team=0;
  iZoneTime=0;
  aTime=0;
  redTime=0;
  greenTime=0;

  int largoTono = 50;
  // 0 = neutral, 1 = green team, 2 = red team
  a=millis();
  //Starting Game Code
  while(1)  // this is the important code, is a little messy but works good.
  {
    if(endGame){
      gameOver();
    }
    
    keypad.getKey();
    aTime=millis()- iTime;
    //Code for led blinking
    timeCalcVar=(millis()- iTime)%1000;
    if(timeCalcVar >= 0 && timeCalcVar <= 40)
    {
      if(team==1)digitalWrite(GREENLED, HIGH);  
      if(team==2)digitalWrite(REDLED, HIGH);  
    }
    if(timeCalcVar >= 50 && timeCalcVar <= 100)
    {    
      if(team==1)digitalWrite(GREENLED, LOW);  
      if(team==2)digitalWrite(REDLED, LOW);
    }
    // Sound!!! same as Destroy 
    if(timeCalcVar >= 0 && timeCalcVar <= 40 && soundEnable)tone(tonepin,tonoActivada,largoTono);

    if(timeCalcVar >= 245 && timeCalcVar <= 255 && minutos-aTime/60000<2 && soundEnable)tone(tonepin,tonoActivada,largoTono);
    if(timeCalcVar >= 495 && timeCalcVar <= 510 && minutos-aTime/60000<4 && soundEnable)tone(tonepin,tonoActivada,largoTono);
    if(timeCalcVar >= 745 && timeCalcVar <= 760 && minutos-aTime/60000<2 && soundEnable)tone(tonepin,tonoActivada,largoTono);
    //Help to count 3 secs
    if(a+2000<millis()){
      a=millis();   
      showGameTime=!showGameTime;
      cls();
    }
    //THE NEXT TO METHODS SHOW "GAME TIME" AND "CONTROLED ZONE TIME" IT SHOWS 2 AND 2 SEC EACH

    if(showGameTime){ //THE SECOND IS /2
      lcd.setCursor(3,0);
      lcd.print("GAME TIME");
      lcd.setCursor(3,1);
      printTime(minutos, aTime);
    }
    else if (!showGameTime){

      lcd.setCursor(2,0);
      if(team == 0)lcd.print("NEUTRAL ZONE");
      if(team == 1)lcd.print(" GREEN ZONE");
      if(team == 2)lcd.print("  RED ZONE");

      if(team>0){
        lcd.setCursor(3,1);
        printTimeDom(millis()-iZoneTime,true);
      }
    }

    //###########################CHECKINGS##################

    //Check If Game End
    if(minutos-aTime/60000==0 && 59-((aTime/1000)%60)==0)
    {
      gameOver();
    }

    //Check If IS neutral
    while((defuseando || cancelando) && team > 0)
    {
      cls();
      if(team>0)lcd.print("NEUTRALIZING...");
      lcd.setCursor(0,1);
      unsigned int percent=0;
      unsigned long xTime=millis(); //start disabling time
      while(defuseando || cancelando)
      {
        //check if game time runs out during the disabling
        aTime= millis()- iTime;
        if((minutos-aTime/60000==0 && 59-((aTime/1000)%60)==0) || minutos-aTime/60000>4000000000){ 
          endGame = true;
        }
        
        keypad.getKey();
        timeCalcVar = (millis()- xTime)%1000;

        if( timeCalcVar >= 0 && timeCalcVar <= 20)
        {
          if(soundEnable)tone(tonepin,tonoAlarma1,200);
        }
        if(timeCalcVar >= 480 && timeCalcVar <= 500)
        {
          if(soundEnable)tone(tonepin,tonoAlarma2,200);
          digitalWrite(REDLED, LOW);
        }

        unsigned long seconds= millis() - xTime;
        percent = (seconds)/(ACTIVATESECONDS*10);
        drawPorcent(percent);

        if(percent >= 100)
        {
          delay(1000);

          if(team==1){ 
            greenTime+=millis()-iZoneTime;
            iZoneTime=0; 

          }
          if(team==2){ 
            redTime+=millis()-iZoneTime;
            iZoneTime=0; 
          }
          team=0;
          break;
        }
      }
      cls();
    }

    //Capturing red

    while(defuseando && team == 0 )
    {
      cls();
      if(team==0)lcd.print(" CAPTURING ZONE");
      lcd.setCursor(0,1);
      unsigned int percent=0;
      unsigned long xTime=millis(); //start disabling time
      while(defuseando)
      {
        keypad.getKey();
        //check if game time runs out during the disabling
        aTime= millis()- iTime;
        if((minutos-aTime/60000==0 && 59-((aTime/1000)%60)==0) || minutos-aTime/60000>4000000000){ 
          endGame = true;
        }
        timeCalcVar = (millis()- xTime)%1000;

        if( timeCalcVar >= 0 && timeCalcVar <= 20)
        {
          digitalWrite(REDLED, HIGH);  
          if(soundEnable)tone(tonepin,tonoAlarma1,200);
        }
        if(timeCalcVar >= 480 && timeCalcVar <= 500)
        {
          if(soundEnable)tone(tonepin,tonoAlarma2,200);
          digitalWrite(REDLED, LOW);
        }

        unsigned long seconds= millis() - xTime;
        percent = (seconds)/(ACTIVATESECONDS*10);
        drawPorcent(percent);

        if(percent >= 100)
        {
          digitalWrite(GREENLED, LOW);
          team=2;
          iZoneTime=millis();
          delay(1000);
          break;
        }
      }
      cls();
      digitalWrite(REDLED, LOW);
    }

    //getting to green zone
    while(cancelando && team == 0 )
    {
      cls();
      if(team==0)lcd.print(" CAPTURING ZONE");
      lcd.setCursor(0,1);
      unsigned int percent=0;
      unsigned long xTime=millis(); //start disabling time
      while(cancelando)
      {
        keypad.getKey();
        //check if game time runs out during the disabling
        aTime= millis()- iTime;
        if((minutos-aTime/60000==0 && 59-((aTime/1000)%60)==0) || minutos-aTime/60000>4000000000){ 
          endGame = true;
        }
        timeCalcVar = (millis()- xTime)%1000;

        if( timeCalcVar >= 0 && timeCalcVar <= 20)
        {
          digitalWrite(GREENLED, HIGH);  
          if(soundEnable)tone(tonepin,tonoAlarma1,200);
        }
        if(timeCalcVar >= 480 && timeCalcVar <= 500)
        {
          if(soundEnable)tone(tonepin,tonoAlarma2,200);
          digitalWrite(GREENLED, LOW);
        }

        unsigned long seconds= millis() - xTime;
        percent = (seconds)/(ACTIVATESECONDS*10);
        drawPorcent(percent);

        if(percent >= 100)
        {
          digitalWrite(GREENLED, LOW);
          team=1;
          iZoneTime=millis();
          delay(1000);
          break;
        }
      }
      cls();
      digitalWrite(GREENLED, LOW);  
    }
  }
}

void gameOver(){

  if(team==1)greenTime+=millis()-iZoneTime;
  if(team==2)redTime+=millis()-iZoneTime;
  digitalWrite(GREENLED, LOW);
  digitalWrite(REDLED, LOW);
  while(!defuseando){
    keypad.getKey();
    if(defuseando){
      keypad.getKey();
      break;
    }
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("TIME OVER!");
    lcd.setCursor(0,1);

    //check who team win the base
    if(greenTime>redTime){
      //greenteam wins
      lcd.print(" GREEN TEAM WIN");
      digitalWrite(GREENLED, HIGH);
    }
    else{
      //redteam wins 
      lcd.print("  RED TEAM WIN");
      digitalWrite(REDLED, HIGH);
    }
    delay(3000);
    keypad.getKey();
    if(defuseando){
      keypad.getKey();
      break;
    }
    cls();
    lcd.print("Red Time:");
    lcd.setCursor(5,1);
    printTimeDom(redTime,false);
    delay(3000);
    keypad.getKey();
    if(defuseando){
      
      break;
    }
    cls();
    lcd.print("Green Time:");
    lcd.setCursor(5,1);
    printTimeDom(greenTime,false);
    delay(3000);
    keypad.getKey();
    if(defuseando){
      keypad.getKey();
      break;
    }
  }
  cls();
  delay(100);
  lcd.print("Play Again?");
  lcd.setCursor(0,1);
  lcd.print("A : Yes B : No");
  while(1)
  {
    var = keypad.waitForKey();
    if(var == 'a' ){
      tone(tonepin,2400,30);
      cls();
      domination();
      break;
    }  
    if(var == 'b' ){
      tone(tonepin,2400,30);
      menuPrincipal();
      break;
    }  
  } 
}