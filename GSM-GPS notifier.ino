#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <SPI.h>

float lattitude,longitude; // create variable for latitude and longitude object 
String lati, longi, message;
    
SoftwareSerial gpsSerial(4,5);//rx,tx
TinyGPS gps; 
//Create software serial object to communicate with SIM800L
SoftwareSerial mySerial(3, 2); //SIM900 Tx & Rx is connected to Arduino #3 & #2


int button_pin = 13;
int val = 0;
void setup()
{
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  pinMode(13,INPUT);
  gpsSerial.begin(9600);
 
  
  //Begin serial communication with Arduino and SIM800L
  mySerial.begin(9600);
  
  Serial.println("Initializing..."); 
  delay(500);

  
  
}

void loop()
{
  val = digitalRead(button_pin);
  if(val == LOW)
  {
    getcoordinates();
   
  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();

  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  mySerial.println("AT+CMGS=\"+917219637336\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  updateSerial();
  mySerial.print(message); //text content
  updateSerial();
  mySerial.write(26);

   
  }
 
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}
void getcoordinates()
{
       
    gps.f_get_position(&lattitude, &longitude );   
    Serial.print("Latitude = ");
    Serial.print(lattitude, 2);
    Serial.print("Longitude = ");
    Serial.print(longitude, 2);
    lati = String(lattitude);
    longi = String(longitude);  
    message = "Help!!!  " + lati + "E  " + longi + "N "; 
}

  
