#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <DallasTemperature.h>
#include <OneWire.h>
#include <RTClib.h>
#include <Servo.h>

int SENSOR = 2, TEMPERATURA, TEMPERATURA_AGUA, HUMEDAD;
int LedRojo = 8;
int LedVerde = 9;
int LedAzul = 10;
int LedRojo2 = 11;
int LedVerde2 = 12;
int LedAzul2 = 13;
Servo servo1;
RTC_DS3231 rtc;
const byte PinSensorTAgua = 3;

LiquidCrystal_I2C lcd (0x27, 2, 1, 0, 4, 5, 6, 7); // DIR, E, RW, RS, D4, D5, D6, D7
DHT dht (SENSOR, DHT11);
OneWire ourWire(PinSensorTAgua);
DallasTemperature sensors(&ourWire);

void setup()
{
    dht.begin();
    lcd.setBacklightPin(3,POSITIVE);
    lcd.setBacklight(HIGH);
    lcd.begin(20, 4);
    lcd.clear();
    sensors.begin();
    pinMode(LedRojo, OUTPUT);
    pinMode(LedVerde, OUTPUT);
    pinMode(LedAzul, OUTPUT);

    pinMode(LedRojo2, OUTPUT);
    pinMode(LedVerde2, OUTPUT);
    pinMode(LedAzul2, OUTPUT);

    if(!rtc.begin())
    {
      lcd.print("                    ");
      lcd.setCursor(0, 3);
      lcd.print("Modulo RCT no Existe");
      while(1);
    }
    //rtc.adjust(DateTime(__DATE__, __TIME__));

    servo1.attach(4);
    servo1.write(0);
}

void loop()
{
    TEMPERATURA = dht.readTemperature();
    HUMEDAD = dht.readHumidity();
    sensors.requestTemperatures();
    TEMPERATURA_AGUA = sensors.getTempCByIndex(0);

    if(TEMPERATURA > 25)
    {
      analogWrite(LedRojo, 255);
      analogWrite(LedVerde, 0);
      analogWrite(LedAzul, 0);
    }
    else if(TEMPERATURA <= 25 && TEMPERATURA >= 20)
    {
      analogWrite(LedRojo, 0);
      analogWrite(LedVerde, 255);
      analogWrite(LedAzul, 0);
    }
    else
    {
      analogWrite(LedRojo, 0);
      analogWrite(LedVerde, 0);
      analogWrite(LedAzul, 255);
    }

    if(TEMPERATURA_AGUA >= 30)
    {
      analogWrite(LedRojo2, 255);
      analogWrite(LedVerde2, 0);
      analogWrite(LedAzul2, 0);
    }
    else if(TEMPERATURA_AGUA <=29 && TEMPERATURA_AGUA >= 24)
    {
      analogWrite(LedRojo2, 0);
      analogWrite(LedVerde2, 255);
      analogWrite(LedAzul2, 0);
    }
    else
    {
      analogWrite(LedRojo2, 0);
      analogWrite(LedVerde2, 0);
      analogWrite(LedAzul2, 255);
    }

    lcd.setCursor(0, 0);
    lcd.print("T");
    lcd.print((char)223);
    lcd.print(" Agua: ");
    lcd.print(TEMPERATURA_AGUA);
    lcd.print((char)223);
    lcd.setCursor(0, 1);
    lcd.print("T");
    lcd.print((char)223);
    lcd.print(" ambiente: ");
    lcd.print(TEMPERATURA);
    lcd.print((char)223);
    lcd.setCursor(0, 2);
    lcd.print("Humedad: ");
    lcd.print(HUMEDAD);
    lcd.print("%");


    DateTime fecha = rtc.now();

    int dia = fecha.day();
    int mes = fecha.month();
    int anio = fecha.year();
    int hora = fecha.hour();
    int minuto = fecha.minute();
    int segundo = fecha.second();
    
    lcd.setCursor(0, 3);
    lcd.print("                    ");
    
    lcd.setCursor(0, 3);
    
    if(dia < 10)
    {
      lcd.print("0");
      lcd.print(dia);
    }
    else
    {
      lcd.print(dia);
    }

    lcd.print("/");

    if(mes < 10)
    {
      lcd.print("0");
      lcd.print(mes);
    }
    else
    {
      lcd.print(mes);
    }
    
    lcd.print("/");

    lcd.print(fecha.year());
    lcd.print(" ");

    if(hora < 10)
    {
      lcd.print("0");
      lcd.print(hora);
    }
    else
    {
      lcd.print(hora);
    }
    
    lcd.print(":");


    if(minuto < 10)
    {
      lcd.print("0");
      lcd.print(minuto);
    }
    else
    {
      lcd.print(minuto);
    }
    
    lcd.print(":");


    if(segundo < 10)
    {
      lcd.print("0");
      lcd.print(segundo);
    }
    else
    {
      lcd.print(segundo);
    }

    if(hora == 22 && minuto == 25 && segundo == 00.00)
    {
      moverServo();
    }
    else if(hora == 22 && minuto == 25 && segundo == 30.00)
    {
      moverServo();
    }
    else if(hora == 22 && minuto == 26 && segundo == 00.00)
    {
      moverServo();
    }
   
    delay(500);
}

void moverServo()
{
  int i;
  for(i=0; i<50; i++)
  {
    servo1.write(i);
    delay(5);
  }
  
  delay(100);

  for(i=50; i>0; i--)
  {
    servo1.write(i);
    delay(5);
  }
}

/* TRIG = 3;
int ECO = 4;
long DURACION;
long DISTANCIA;*/
//en setup
/*pinMode(TRIG, OUTPUT);
    pinMode(ECO, INPUT);*/

//en loop
/*digitalWrite(TRIG, LOW);
delayMicroseconds(4);
digitalWrite(TRIG, HIGH);
delayMicroseconds(10);
digitalWrite(TRIG, LOW);

DURACION = pulseIn(ECO, HIGH);
DURACION = DURACION/2;

DISTANCIA = DURACION / 29;*/

/*lcd.setCursor(0, 3);
lcd.print("Distancia : ");
lcd.print(DISTANCIA);
lcd.print(" cms");*/
