/*
   ****************************** TSC-Lab *******************************

   ***************************** PRACTICE 2 *****************************
   This practice is about USB DATA ACQUISITION and have 4 different cases:

    • Case 1: Ambient temperature reading using sensor 1 and 2
    • Case 2: Activation of Transistor 1 and Reading of temperature sensor 1 and 2
    • Case 3: Activation of Transistor 2 and Reading of temperature sensor 1 and 2
    • Case 4: Activation of Transistor 1 and 2, also Reading of temperature sensor 1 and 2

   By: Kevin E. Chica O
   More information: https://tsc-lab.blogspot.com/
*/

#include <OneWire.h>
#include <DallasTemperature.h>

//GPIO pin 5 is set as OneWire bus
OneWire ourWire1(5);
//GPIO pin 4 is set as OneWire bus
OneWire ourWire2(4);

//A variable or object is declared for our sensor 1
DallasTemperature sensors1(&ourWire1);
//A variable or object is declared for our sensor 2
DallasTemperature sensors2(&ourWire2);

//Status of transistors
int t1 = 0;
int t2 = 0;

void setup() {
  delay(1000);
  Serial.begin(115200);
  sensors1.begin();   //Sensor 1 starts
  sensors2.begin();   //Sensor 2 starts

  //transistor 1
  pinMode(16, OUTPUT);
  //transitor 2
  pinMode(17, OUTPUT);
}

void loop() {
  Serial.println("Choose any case: ");
  if (Serial.available())
  {
    String string = Serial.readStringUntil('\n');

    if (string == "case_1") {
      Serial.println("Case 1 started");
      for (int i = 1; i <= 10; i++) {
        //transistor 1 deactivate
        t1 = 0;
        //transistor 2 deactivate
        t2 = 0;
        readData();
        readData();
      }
      Serial.println("Case 1 finished");

    }
    if (string == "case_2") {
      Serial.println("Case 2 started");

      for (int i = 1; i <= 10; i++) {
        //transistor 1 activate
        digitalWrite(16, HIGH);
        t1 = 1;
        readData();
        //transistor 1 deactivate
        t1 = 0;
        digitalWrite(16, LOW);
        readData();
      }
      Serial.println("Case 2 finished");
    }
    if (string == "case_3") {
      Serial.println("Case 3 started");

      for (int i = 1; i <= 10; i++) {
        //transistor 2 activate
        digitalWrite(17, HIGH);
        t2 = 1;
        readData();
        //transistor 2 deactivate
        t2 = 0;
        digitalWrite(17, LOW);
        readData();
      }
      Serial.println("Case 3 finished");
    }
    if (string == "case_4") {
      Serial.println("Case 4 started");

      for (int i = 1; i <= 10; i++) {
        //transistor 1 activate
        digitalWrite(16, HIGH);
        t1 = 1;
        //transistor 2 activate
        digitalWrite(17, HIGH);
        t2 = 1;
        readData();
        //transistor 1 deactivate
        t1 = 0;
        digitalWrite(16, LOW);
        //transistor 2 deactivate
        t2 = 0;
        digitalWrite(17, LOW);
        readData();
      }
      Serial.println("Case 4 finished");
    }

  }

}


//method to read data for 12 minute
void readData() {

  uint32_t period = 12 * 60000L;       // 12 minutes

  for ( uint32_t tStart = millis();  (millis() - tStart) < period;  ) {
    //The command is sent to read the temperature
    sensors1.requestTemperatures();
    //Obtain the temperature in ºC of sensor 1
    float temp1 = sensors1.getTempCByIndex(0);

    //The command is sent to read the temperature
    sensors2.requestTemperatures();
    //Obtain the temperature in ºC of sensor 2
    float temp2 = sensors2.getTempCByIndex(0);

    //print to display the temperature change
    Serial.print(temp1);
    Serial.print(",");
    Serial.print(temp2);
    Serial.print(",");
    Serial.print(t1);
    Serial.print(",");
    Serial.println(t2);
    delay(100);
  }

}
