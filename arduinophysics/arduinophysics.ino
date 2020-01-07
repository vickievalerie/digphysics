// for temp sensor
#include <OneWire.h>

// for SD card
#include <SPI.h>
#include <SD.h>

// for pressure sensor
#include <Wire.h>
#include <Adafruit_BMP085.h>

#include "DHT.h"

const int PIN_CHIP_SELECT = 4;
const int PIN_TEMP_SENSOR = 2;
const int PIN_DHT = 3;

bool use_sd = true;

int frame_delay=500;

char filename[] = "phyzlo00.csv"; // filename template

OneWire ds(PIN_TEMP_SENSOR); // Создаем объект OneWire для шины 1-Wire, с помощью которого будет осуществляться работа с датчиком
Adafruit_BMP085 bmp;

DHT dht(PIN_DHT, DHT22);

int frame = 0;

void setup(){
  Serial.begin(9600);
  init_filesystem();
  bmp.begin();
  dht.begin();
  output("frame,time,temp,a1,temp_pres,pressure,altitude,humidity,temp_hum");
}

void loop(){
  output(String(frame)+","+String(millis())+","+String(get_temp())+","+String(analogRead(1))+","+String(bmp.readTemperature())+","+String(bmp.readPressure())+","+String(bmp.readAltitude())+","+String(dht.readHumidity())+","+String(dht.readTemperature()));
  delay(frame_delay);
  frame++;
}

void init_filesystem()
{
  // setup SD card
  if (!SD.begin(PIN_CHIP_SELECT)) {
    Serial.println("# No SD card");
    use_sd = false;
  }
  else
  {
    Serial.println("# SD Card initialized");
    use_sd = true;
    for (uint8_t i = 0; i < 100; i++) {
       filename[6] = i / 10 + '0';
       filename[7] = i % 10 + '0';
       if (! SD.exists(filename)) { // Проверяем наличие
         break;  // Дальше продолжать смысла нет
       }
    }
    Serial.print("# Using log file = ");
    Serial.println(filename);
  }
}

void output(String s)
{
  Serial.println(s);
  if (use_sd)
  {
     File dataFile = SD.open(filename, FILE_WRITE);
     if (dataFile) {
        dataFile.println(s);
        dataFile.close();
     }
     else {
        Serial.println("# error opening data file");
     }
  }
}

// Определяем температуру от датчика DS18b20
float get_temp(){  
  byte data[2]; // Место для значения температуры
  
  ds.reset(); // Начинаем взаимодействие со сброса всех предыдущих команд и параметров
  ds.write(0xCC); // Даем датчику DS18b20 команду пропустить поиск по адресу. В нашем случае только одно устрйоство 
  ds.write(0x44); // Даем датчику DS18b20 команду измерить температуру. Само значение температуры мы еще не получаем - датчик его положит во внутреннюю память
  
  delay(10); // Микросхема измеряет температуру, а мы ждем.  
  
  ds.reset(); // Теперь готовимся получить значение измеренной температуры
  ds.write(0xCC); 
  ds.write(0xBE); // Просим передать нам значение регистров со значением температуры

  // Получаем и считываем ответ
  data[0] = ds.read(); // Читаем младший байт значения температуры
  data[1] = ds.read(); // А теперь старший

  // Формируем итоговое значение: 
  //    - сперва "склеиваем" значение, 
  //    - затем умножаем его на коэффициент, соответсвующий разрешающей способности (для 12 бит по умолчанию - это 0,0625)
  return ((data[1] << 8) | data[0]) * 0.0625;
}
