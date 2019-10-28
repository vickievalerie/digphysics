#include <OneWire.h>

OneWire ds(2); // Создаем объект OneWire для шины 1-Wire, с помощью которого будет осуществляться работа с датчиком

void setup(){
  Serial.begin(9600);
}

float get_temp(){  // Определяем температуру от датчика DS18b20
  byte data[2]; // Место для значения температуры
  
  ds.reset(); // Начинаем взаимодействие со сброса всех предыдущих команд и параметров
  ds.write(0xCC); // Даем датчику DS18b20 команду пропустить поиск по адресу. В нашем случае только одно устрйоство 
  ds.write(0x44); // Даем датчику DS18b20 команду измерить температуру. Само значение температуры мы еще не получаем - датчик его положит во внутреннюю память
  
  delay(1000); // Микросхема измеряет температуру, а мы ждем.  
  
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
  
void loop(){
  // Выводим полученное значение температуры в монитор порта
  Serial.println(get_temp());
   
}
