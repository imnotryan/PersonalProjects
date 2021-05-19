
#include <LiquidCrystal.h>
#include <DS3231.h>
#include <Keypad.h>
LiquidCrystal lcd(8, 9, 10, 11, 12,13);

// Init the DS3231 using the hardware interface
DS3231  rtc(SDA, SCL);


//BELOW IS FOR KEYPAD MODULE//////////////////////////////////
/*
//four rows
const byte ROWS = 4;

//four columns 
const byte COLS = 4;

//define the cymbols on the buttons of the keypads 
char hexaKeys[ROWS][COLS] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}};

//connect to the row pinouts of the keypad 
byte rowPins[ROWS] = {7, 6, 5, 4};//USES DIGITAL PIN 7,6,5,4 for keypad module

//connect to the column pinouts of the keypad 
byte colPins[COLS] = {3, 2, 1, 0}; //USES DIGITAL PIN 3,2,1,0 for keypad module

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

//ABOVE IS FOR KEYPAD MODULE/////////////////////////////////////////////
*/


void setup() {   // put your setup code here, to run once:
  

//below for LCD
  lcd.begin(16,2);
  lcd.print("Hello World");
//above for LCD///////////////////////

//below for Real Time Clock///////////

  // Setup Serial connection
  //Serial.begin(9600);
 
  // Initialize the rtc object
  rtc.begin();
  
  // The following lines can be uncommented to set the date and time BUT ONLY TO **INITIALLY** SET THE DATE AND TIME AKA SHOULDN'T EVER UNCOMMENT
  //THE REST OF THE LINES BELOW FOR RTC UNTIL LIKE 5 YEARS FROM MARCH 20 2021 lol
  //rtc.setDOW(SATURDAY);     // Set Day-of-Week to SUNDAY
  //rtc.setTime(18, 33, 0);     // Set the time to 12:00:00 (24hr format)
  //rtc.setDate(20, 3, 2021);   // Set the date to January 1st, 2014

//above for Real Time Clock///////////




  
}

void loop() {
  // put your main code here, to run repeatedly:
  //below for LCD////////////////////////////////////////
  //lcd.setCursor(0, 1);
// print the number of seconds since reset:
  //lcd.print(millis() / 1000);
// above for LCD////////////////////////////////////////


//below for Real Time Clock//////////////////////////////////////////////

// Send Day-of-Week 

//THIS CODE is for printing to the serial monitor, NOT the LCD like I want it to 
  /*Serial.print(rtc.getDOWStr());
  Serial.print(" ");
  
  // Send date
  Serial.print(rtc.getDateStr());
  Serial.print(" -- ");

  // Send time
  Serial.println(rtc.getTimeStr());
  
  // Wait one second before repeating :)
  delay (1000);
*/

//BELOW IS FOR OUTPUTTING THE DAY OF WEEK, DATE, AND TIME FROM RTC

//lcd.setCursor(0,0);
//lcd.print("Day:");
//lcd.print(rtc.getDOWStr()); //prints day of week

//lcd.setCursor(0,0);
//lcd.print("Date:");
//lcd.print(rtc.getDateStr());

lcd.setCursor(0,1);
lcd.print("Time:");
lcd.print(rtc.getTimeStr());

//ABOVE IS FOR OUTPUTTING THE DAY OF WEEK, DATE, AND TIME FROM RTC
//above for Real Time Clock///////////////////////////////////////////////




}

//below for water level sensor module

///?????? look at given code in elegoo project stuff

//above for water level sensor module



  
