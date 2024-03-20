// Библиотека работы с DS18b20
#include <OneWire.h> 
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 12
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
// Библиотека для датчика AM2320
#include <AM2320.h>
#include <Wire.h>
// Глобальные переменные
float po;
float ap_raw;
float an_raw;

void setup() {               
  ADCSRA &= B11111000;
  ADCSRA |= B00000100;
  Serial.begin(9600);
  Wire.begin();
}


void loop() {
int d1,d2,a1,tr;
long n;
float x,x0,x1,x2,ec,ec0,ec1,ec2,t,tk,k,l,lev;
String gp;


String tstring = "tparse="; // Метка начала строки для парсинга
String tstring_end = "="; // Метка окончания строки
String pstring = ""; // Метка строки вывода колонку  
//////////////////////////////////////////////////////////////////////////
// Общая температура и влажность воздуха с AM2320 через i2c
AM2320 th;
th.Read();
// Заполнение строкового вывода для машинного парсинга
  tstring +=fFTS(th.t,1) + ";" + fFTS(th.h,1) + ";" + fFTS(fAbsoluteHumidity(th.t,th.h),1) + ";"; 
// Человекочитаемый вывод
  pstring += "Air temperature=";
  pstring += fFTS(th.t,2);
  pstring += "\n";
  pstring += "Relative humidity=";  
  pstring += fFTS(th.h,2);
  pstring += "\n";
  pstring += "Absolute air humidity=";
  pstring += fFTS(fAbsoluteHumidity(th.t,th.h),2);
  pstring += "\n";


/////////////////////////////     Раствор 1   ////////////////////////////////////////////
gp="container 1"; // Номер группы измерения

// Измеритель ЕС1
//  Схема подключения
//  d1----a1----->
//  d2----------->
d1=10;  // Цифровой порт соединенный с аналоговым портом и электродом измерения
d2=11;  // Цифровой порт соединенный с электродом противофазы
a1=0;   // Аналоговый порт измерения
n=50000;// Колличество измерений для усреднения
// Калибровка ЕС
ec1= 0.01;    // Фактическое значение ЕС при нижнем пределе
x1=16;        // Показания АЦП при нижнем значении ЕС
ec2= 3;     // Фактическое значение ЕС при верхнем пределе
x2=160;        // Показания АЦП при верхнем значении ЕС
// Температура раствора
tr=0;    // Порядковый номер датчика 18b20 в растворе
tk=0.02; // Коэффициент влияния температуры на проводимость раствора

// Измерение температуры
sensors.requestTemperatures(); 
t=sensors.getTempCByIndex(tr);
// Измерение RAW проводимости
x=fConductivity(d1,d2,a1,n);

  pstring += gp +" RAW Solution polarization ADC = ";
  pstring += fFTS(po,2);
  pstring += "\n";
// Расчет ЕС
ec0=fCalibration(x1,ec1,x2,ec2,x);
// Термокомпенсация ЕС
ec=fECTemp(tk,ec0,t);

// Измеритель уровня 1
d1=9;   // Цифровой порт соединенный с аналоговым портом и электродом измерения
d2=11;  // Цифровой порт соединенный с электродом противофазы
a1=0;   // Аналоговый порт измерения
n=500; // Колличество измерений для усреднения
k=0.835; // Коэффициент компенсации электропроводности
// Измерение проводимости
l=fConductivity(d1,d2,a1,n);  
lev=x/pow(l,k);
// Заполнение строкового вывода для машинного парсинга
  tstring +=fFTS(t,2) + ";" + fFTS(x,4) + ";" + fFTS(l,2) + ";"+ fFTS(ec0,4) + ";"; 
// Человекочитаемый вывод  
  pstring += gp +" Solution temperature = ";
  pstring += fFTS(t,2);
  pstring += "\n";
  pstring += gp +" RAW EC ADC = ";
  pstring += fFTS(x,4);
  pstring += "\n"; 
  pstring += gp +" RAW Level ADC = ";
  pstring += fFTS(l,2);
  pstring += "\n";   
  pstring += gp +" EC = ";
  pstring += fFTS(ec0,4);
  pstring += "\n";
    pstring += gp +" Level = ";
  pstring += fFTS(lev,4);
  pstring += "\n";
/////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////     Раствор 2   ////////////////////////////////////////////
gp="container 2"; // Номер группы измерения

// Измеритель ЕС1
//  Схема подключения
//  d1----a1----->
//  d2----------->
d1=7;  // Цифровой порт соединенный с аналоговым портом и электродом измерения
d2=8;  // Цифровой порт соединенный с электродом противофазы
a1=1;   // Аналоговый порт измерения
n=50000;// Колличество измерений для усреднения
// Калибровка ЕС
ec1= 0.01;    // Фактическое значение ЕС при нижнем пределе
x1=16;        // Показания АЦП при нижнем значении ЕС
ec2= 3;     // Фактическое значение ЕС при верхнем пределе
x2=160;        // Показания АЦП при верхнем значении ЕС
// Температура раствора
tr=1;    // Порядковый номер датчика 18b20 в растворе
tk=0.02; // Коэффициент влияния температуры на проводимость раствора

// Измерение температуры
sensors.requestTemperatures(); 
t=sensors.getTempCByIndex(tr);
// Измерение RAW проводимости
x=fConductivity(d1,d2,a1,n);

  pstring += gp +" RAW Solution polarization ADC = ";
  pstring += fFTS(po,2);
  pstring += "\n";
// Расчет ЕС
ec0=fCalibration(x1,ec1,x2,ec2,x);
// Термокомпенсация ЕС
ec=fECTemp(tk,ec0,t);

// Измеритель уровня 1
d1=6;   // Цифровой порт соединенный с аналоговым портом и электродом измерения
d2=8;  // Цифровой порт соединенный с электродом противофазы
a1=1;   // Аналоговый порт измерения
n=500; // Колличество измерений для усреднения
k=0.835; // Коэффициент компенсации электропроводности
// Измерение проводимости
l=fConductivity(d1,d2,a1,n);  
lev=x/pow(l,k);
// Заполнение строкового вывода для машинного парсинга
  tstring +=fFTS(t,2) + ";" + fFTS(x,4) + ";" + fFTS(l,2) + ";"+ fFTS(ec0,4) + ";"; 
// Человекочитаемый вывод  
  pstring += gp +" Solution temperature = ";
  pstring += fFTS(t,2);
  pstring += "\n";
  pstring += gp +" RAW EC ADC = ";
  pstring += fFTS(x,4);
  pstring += "\n"; 
  pstring += gp +" RAW Level ADC = ";
  pstring += fFTS(l,2);
  pstring += "\n";   
  pstring += gp +" EC = ";
  pstring += fFTS(ec0,4);
  pstring += "\n";
    pstring += gp +" Level = ";
  pstring += fFTS(lev,4);
  pstring += "\n";
/////////////////////////////////////////////////////////////////////////////////////

// Передача в терминал
  tstring += tstring_end;
  Serial.println(tstring);
  Serial.print("\n");
  Serial.print(pstring);
  Serial.print("\n   --------\n");
}

//////////////////////////////////////////////////////////////////////
// ФУНКЦИИ
// Функция калибровки
float fCalibration(float x1, float ec1, float x2, float ec2, float x){
  float b=(-log(ec1/ec2))/log(x2/x1);
  float a=((pow(x1,-b))*ec1); 
  float ec0 = a * pow(x,b);
  return ec0;
}

// Функция термокомпенсации ЕС
float fECTemp(float k, float ec0, float t){
  return ec0/(1+k*(t-25));
}

//Функция замера электропроводности в RAW
float fConductivity(int d1, int d2, int a1, long cnt){

  pinMode(d1, OUTPUT);
  pinMode(d2, OUTPUT); 
  long var=1;
  unsigned long ap=0;
  unsigned long an=0;  
  while(var < cnt){

    digitalWrite(d2, HIGH);
    ap=0+analogRead(a1)+ap;
    digitalWrite(d2, LOW);
 
    digitalWrite(d1, HIGH);
    an=1023-analogRead(a1)+an;
    digitalWrite(d1, LOW); 
    var++;
  }
  pinMode(d1, INPUT);
  pinMode(d2, INPUT);
 // Усреднение АЦП при положительной фазе
 ap_raw=(float)ap/var;
 // Усреднение АЦП при отрицательной фазе
 an_raw=(float)an/var;
 // Расчет поляризации раствора 
 po = ap_raw-an_raw;
 // Исключение влияние поляризаци
 return (((float)ap+(float)an)/var/2);

}

// Функция преобразования чисел с плавающей запятой в текст  
String fFTS(float x, byte precision) {
  char tmp[50];
  dtostrf(x, 0, precision, tmp);
  return String(tmp);
}


// Функция конвертации относительной влажности в абсолютную
float fAbsoluteHumidity(float tt, float rh){
  return (4.579*pow(2.71828,((17.14*tt)/(235.3+tt))))*rh/100;
}