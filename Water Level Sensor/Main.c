
#include <LiquidCrystal.h>
#include <DS3231.h>
#include <Keypad.h>
//#include <WaterLevelSensor.h>

LiquidCrystal lcd(8, 9, 10, 11, 12,13); // sets pins 8, 9, 10, 11, 12, 13 to work with LCD

// Initialize the DS3231 using the hardware interface
DS3231  rtc(SDA, SCL);

int adc_id = 0;
int numberOfStoredObjects = 0; // total objects stored 
bool waterHasEnteredHouse = false; 
bool resetPushed = false; //for reset button
bool displayedDataPushed = false; // for display button
class WaterData
{
  public: 
  void setIDofData(); 
  void setDayOfWeek(); 
  void setTimeForStoring();
  void setDateForStoring();
  void setWaterLevelInCMandIN(); 

  int getIDofData();
  float getWaterLevelInCM();
  float getWaterLevelInIN();
  
  void printAllData(); // prints the Date, day of week, and then time two times with delays of three seconds
  void printID();
  void printDayOfWeek();
  void printTimeForStoring();
  void printDateForStoring();
  void printWaterLevelInCM();
  void printWaterLevelInIN();
  
  void resetWaterDataObject();
  
  private:
  int IDCount = -1;
  char dayOfWeek[11] = "NotSet"; // 10 for Wednesday plus null char (Wednesday is longest string DOW)
  char dateForStoring[11] = "NotSet";
  char timeForStoring[11] = "NotSet";
  float waterLevelInCM = 0;
  float waterLevelInIN = 0;
};

void WaterData::setIDofData()
{
  numberOfStoredObjects++;
  IDCount = numberOfStoredObjects;
}
void WaterData::setDayOfWeek() 
{
  strcpy(dayOfWeek,rtc.getDOWStr());
}
void WaterData::setTimeForStoring() 
{
  strcpy(timeForStoring,rtc.getTimeStr());
}
void WaterData::setDateForStoring()
{
  strcpy(dateForStoring, rtc.getDateStr());
}
void WaterData::setWaterLevelInCMandIN()
{
  waterLevelInCM = (analogRead(adc_id)-21.1) / 330.5;
  if (waterLevelInCM < 0) //gets rid of negative numbers
  {
    waterLevelInCM = 0; 
  }
  waterLevelInIN = waterLevelInCM * 0.393701; // 1 cm = 0.393701 inches
  if (waterLevelInIN < 0)
  {
    waterLevelInIN = 0;
  }
}
int WaterData::getIDofData()
{
  return IDCount;
}
float WaterData::getWaterLevelInCM()
{
  return waterLevelInCM;
}
float WaterData::getWaterLevelInIN()
{
  return waterLevelInIN;
}
void Delay100ms(uint32_t count)
{
  uint32_t volatile time;
  while(count>0){
    time = 48483;  // 0.1sec at 16 MHz //very close to exactly one second hand-timed
    while(time){
      time--;
    }
    count--;
  }
}
void WaterData::printAllData()
{
  //first prints water level
  lcd.setCursor(0,0);
  lcd.print("Water Height:");
  lcd.setCursor(0,1);
  lcd.print(waterLevelInCM);
  lcd.print("CM/");
  lcd.print(waterLevelInIN);
  lcd.print("IN");
  Delay100ms(30); //30 for three seconds

if (resetPushed == true)
{
  goto STOP;
}
  //then prints the date and DOW
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("D.M.Y:");
  lcd.print(dateForStoring);
  lcd.setCursor(0,1);
  lcd.print(dayOfWeek);
  Delay100ms(30);

if (resetPushed == true)
{
  goto STOP;
}

  //finally, prints out the time
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Time HH:MM:SS");
  lcd.setCursor(0,1);
  lcd.print(timeForStoring);
  
  STOP:
  Delay100ms(30);
  lcd.clear();
}
void WaterData::printID()
{
  lcd.print(IDCount);
}
void WaterData::printDayOfWeek()
{
  lcd.print(dayOfWeek);
}
void WaterData::printTimeForStoring()
{
  lcd.print(timeForStoring);
}
void WaterData::printDateForStoring()
{
  lcd.print(dateForStoring);
}
void WaterData::printWaterLevelInCM()
{
  lcd.print(waterLevelInCM);
}
void WaterData::printWaterLevelInIN()
{
  lcd.print(waterLevelInIN);
}

void WaterData::resetWaterDataObject()//resets all parameters to NULL or -1
{
  IDCount = -1;
  waterLevelInCM=0;
  waterLevelInIN=0;
  for (int i = 0; i < 11; i ++)
  {
    dayOfWeek[i] = NULL;
    dateForStoring[i] = NULL;
    timeForStoring[i] = NULL;
  }
  dayOfWeek[11] = "NotSet"; 
  dateForStoring[11] = "NotSet";
  timeForStoring[9] = "NotSet";
}


WaterData arrayOfObjectsToStoreWaterLevel[75];//saving one water level object every hour for 3 days. 72 objects stored but have 75 for extra space
int HistoryValue = 0;
char printBuffer[128];

void displayCurrentWaterLevel() // THIS IS THE INTERRUPT
{
  //should display the current highest water level in cm/in, date, time, and DOW two times for three seconds each
  //NOTE: NORMAL DELAY() FUNCTION DOESN'T WORK INSIDE ANY (INCLUDING THIS) INTERRUPT

if (resetPushed == false) // don't wanna display data that isn't initialized unless reset HAS NOT been pushed
{
  displayedDataPushed = true;
  int highestIndex = 0;
  lcd.clear();
  lcd.setCursor(0,0);
  if (waterHasEnteredHouse == false)
  {
    lcd.print("Water has not");
    lcd.setCursor(0,1);
    lcd.print("entered house");
    Delay100ms(30);
    lcd.clear();
  }
  else if (waterHasEnteredHouse == true)
  {
    for (int i = 0; i < 2; i ++) // prints out the highest water level so far, twice
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Highest Water");
      lcd.setCursor(0,1);
      lcd.print("level so far:"); 
    
      Delay100ms(30);
      lcd.clear();
      lcd.setCursor(0,0);
      
    highestIndex = findAndReturnHighestWaterLevelIDX();
    arrayOfObjectsToStoreWaterLevel[highestIndex].printAllData();
    }
  }
}
}

void resetArrayOfObjects()
{
  for (int i = 0; i < numberOfStoredObjects; i ++) // OR i < 75 bc 75 is highest array of objects count
  {
    arrayOfObjectsToStoreWaterLevel[i].resetWaterDataObject();
  }
}

void RESET() // clears LCD screen, resets arrayOfWaterDataObjects, and goes to function 'checkIfWaterEnteredHouse()'
{
  resetPushed = true; // should only call reset once until it is reset in 'storeDataInArrayUntilThreeDaysLater' function
  waterHasEnteredHouse = false; 
  resetArrayOfObjects(); //resets all stored data
  numberOfStoredObjects = 0; //resets total number of stored objects- used in WaterData class functions
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Resetting Data");
  Delay100ms(30);
  lcd.clear();
}

void setup() {   // initializes pins and real-time clock 
  
  lcd.begin(16,2); // 16 cols, 2 rows (initializes 16x2 LCD)
 
  // Initialize the rtc object
  rtc.begin();
  
  // The following lines can be uncommented to set the date and time BUT ONLY TO **INITIALLY** SET THE DATE AND TIME 
  //rtc.setDOW(SATURDAY);     // Set Day-of-Week to SUNDAY
  //rtc.setTime(18, 33, 0);     // Set the time to 12:00:00 (24hr format)
  //rtc.setDate(20, 3, 2021);   // Set the date to January 1st, 2014


pinMode(2, INPUT);    // sets the digital pin 2 as input 
attachInterrupt(digitalPinToInterrupt(2), displayCurrentWaterLevel, RISING); // sets pin 2 as edge-triggered interrupt

pinMode(3, INPUT);    // sets the digital pin 3 as input
attachInterrupt(digitalPinToInterrupt(3), RESET, RISING); //sets pin 3 as edge-triggered interrupt
}

int findAndReturnHighestWaterLevelIDX()
{ 
  int indexOfHighestWaterLevel = 0;
  int indexOfLowestWaterLevel = 0;
  
  for (int currentWaterObjectIDX = 0; currentWaterObjectIDX < numberOfStoredObjects;  currentWaterObjectIDX++)
  {
     if ( arrayOfObjectsToStoreWaterLevel[currentWaterObjectIDX].getWaterLevelInCM() > 
     arrayOfObjectsToStoreWaterLevel[indexOfHighestWaterLevel].getWaterLevelInCM() ) // compares current Water Level with highest Water Level
     {
        indexOfHighestWaterLevel = currentWaterObjectIDX; // finds highest water level index
     }
  }

  return indexOfHighestWaterLevel;
}


float value = 0;
void checkIfWaterEnteredHouse() //need to have ten consecutive seconds of water on water sensor above a certain height to begin
{
  int ifTenThenWaterEnteredHouse;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("  Checking for");
  lcd.setCursor(0,1);
  lcd.print("     water...");
  while(true) // loops until water has reached high-enough level to warrant saving water level in memory
  {
    if ( (resetPushed == true) || (displayedDataPushed == true) )
    {
      lcd.setCursor(0,0);
      lcd.print("  Checking for");
      lcd.setCursor(0,1);
      lcd.print("     water...");
      resetPushed = false;
      displayedDataPushed = false;
    }
     value = analogRead(adc_id); //updates the ADC level into 'value' variable
     if ( value > 320 )
     {
      ifTenThenWaterEnteredHouse++;
      Delay100ms(10);// wait for one second
     }
     else if (value <= 320)
     {
      ifTenThenWaterEnteredHouse = 0;
     }
     if ( ifTenThenWaterEnteredHouse >= 10 )
     {
      //water entered house. Then, need to break out of loop and then start storing data in new class objects in an array
      break;
     }
  }
  waterHasEnteredHouse = true;
}


bool gotToDisplayCurrentWaterLevelInterruptForLcdPrint = false;
void storeDataInArrayUntilThreeDaysLater()
{
  //this function stores objects in arrayOfObjectsToStoreWaterLevel once an hour for three days (72 hours)

if (resetPushed == false)
{
  for (int currentHour = 0; currentHour < 72; currentHour ++) // for loop stores one object with water data each hour for 72 hours (three days)
  {
    if (resetPushed == true)//want to stop storing if reset was pushed
    {
        lcd.clear();
        break;
    }
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("    Storing");
    lcd.setCursor(0,1);
    lcd.print("  Water Data...");
    WaterData newObjectToStore;
    newObjectToStore.setIDofData(); // sets ID of object stored
    newObjectToStore.setDayOfWeek(); // sets DOW
    newObjectToStore.setTimeForStoring(); //sets time at which water level was measured
    newObjectToStore.setDateForStoring(); // sets Date
    newObjectToStore.setWaterLevelInCMandIN(); // gets and stores water level in CM and IN
    arrayOfObjectsToStoreWaterLevel[currentHour] = newObjectToStore; //stores data in global array

    Delay100ms(20);//delays TWO seconds

    for (int i = 0; i < 1800; i ++) //1800 for one hour
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("    Storing");
      lcd.setCursor(0,1);
      lcd.print("  Water Data...");
      if (resetPushed == true)//want to stop storing if reset was pushed
      {
        lcd.clear();
        break;
      }
      if ( displayedDataPushed == true ) // need to reset the LCD screen after printing the current highest water level
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("    Storing");
        lcd.setCursor(0,1);
        lcd.print("  Water Data...");
        displayedDataPushed == false;
      }
      Delay100ms(20);//delays TWO seconds - 3600 seconds in a minute. TWO second delay required i =1800 
    }
  }
  
  //now to display the highest water level object until the 'reset' button is pushed
  int indexOfHighestWaterLevel = 0;
  while(resetPushed == false) //continuously displays highest water level until reset button is pushed
  {
    indexOfHighestWaterLevel = findAndReturnHighestWaterLevelIDX();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Highest Water");
    lcd.setCursor(0,1);
    lcd.print("Level-3 days");
    Delay100ms(30);
    if (resetPushed == false)
    {
      lcd.clear();
      arrayOfObjectsToStoreWaterLevel[indexOfHighestWaterLevel].printAllData();
    }
  }
}
  resetPushed = false; //resets the variable to capture water level again
  displayedDataPushed = false; //need to make sure to be able to push the 'display data' 
}



int loopCounter=0;
void loop() 
{
  resetArrayOfObjects();
  
  resetPushed = false; 
  displayedDataPushed = false; 
  
  checkIfWaterEnteredHouse();
  
//if code made it here, then water has entered the house
  storeDataInArrayUntilThreeDaysLater();

}




  
