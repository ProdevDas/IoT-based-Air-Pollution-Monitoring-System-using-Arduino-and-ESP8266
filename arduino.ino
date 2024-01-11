  #include "MQ135.h"

  const int sensorPin= 0;

  int air_quality;

  #include <LiquidCrystal_I2C.h>

  LiquidCrystal_I2C lcd(0x27,16,2); 


  void setup() {

  pinMode(8, OUTPUT);

  Serial.begin(9600);

  lcd.begin(16,2);

  lcd.init();
          
  lcd.backlight(); 

  lcd.setCursor (0,0);

  lcd.print ("Air Pollution ");

  lcd.setCursor (0,1);

  lcd.print ("Monitoring System");

  delay(2000);

  pinMode(sensorPin, INPUT);        //Gas sensor will be an input to the arduino

  lcd.clear();

  }


  void loop() {


  MQ135 gasSensor = MQ135(A0);

  float air_quality = gasSensor.getPPM();

  Serial.println(air_quality);


  lcd.setCursor (0, 0);

  lcd.print ("Air Quality is ");

  lcd.print (air_quality);

  lcd.print (" PPM ");

  lcd.setCursor (0,1);

  if (air_quality<=1000)

  {

  lcd.print("Fresh Air");

  digitalWrite(8, LOW);

  }

  else if( air_quality>=1000 && air_quality<=2000 )

  {

  lcd.print("Poor Air, Open Windows");

  digitalWrite(8, HIGH );

  }

  else if (air_quality>=2000 )

  {

  lcd.print("Danger! Move to Fresh Air");

  digitalWrite(8, HIGH);   // turn the LED on

  }

  lcd.scrollDisplayLeft();
  delay(500);




  }

  // String sendData(String command, const int timeout, boolean debug) //send and show the data on the webpage. The data we stored in string named ‘webpage’ will be saved in string named ‘command’. The ESP will then read the character one by one from the ‘command’ and will print it on the webpage.

  // {

  //     String response = ""; 

  //     esp8266.print(command); // send the read character to the esp8266

  //     long int time = millis();

  //     while( (time+timeout) > millis())

  //     {

  //       while(esp8266.available())

  //       {

  //         // The esp has data so display its output to the serial window 

  //         char c = esp8266.read(); // read the next character.

  //         response+=c;

  //       }  

  //     }

  //     if(debug)

  //     {

  //       Serial.print(response);

  //     }

  //     return response;

  // }

