#include <LiquidCrystal.h> //тук включваме нужната библиотека
LiquidCrystal lcd(12, 8, 11, 4, 3, 2); //тук създаваме обект от тип лц

int trigPin = 7; //пиновете за ултразвуковия сензор се инициализират тук
int echoPin = 6;
long duration; 
int distanceCm, distanceInch;

int buzzerPin = 13; //пина за говорителчето 

int bluePin=10; //пиновете за rgb лампичката
int greenPin=9;
int redPin=5;

int dt = 500; //времето, през което се изпълнява един цикъл
//създадохме променливи за пиновете, за да може в случай че трябва някой пин да се промени
//да го променим един оът тук, а не 100 пъти в кода

void setup() { 
  lcd.begin(16, 2); //lcd-то започва с 2 реда и 16 колони (при други екрани това може да е различно)
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  pinMode(buzzerPin, OUTPUT);
  
  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
  Serial.begin(9600); //за да имаме опцията да гледаме разстоянието и в serial monitor-а 
}

void loop()
{       
      
      digitalWrite(trigPin, LOW); 
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW); //тук се изпраща ултразвук от трансмитера
      
      duration = pulseIn(echoPin, HIGH); //след като този ултразвук достигне до конктерния обект той се връща и бива приет от приемникът
      distanceCm= duration*0.034/2;      // разстоянието = времето в микросекунди * скоростта на звука в сантиметри в микросекунда / 2 
      distanceInch = distanceCm*0.3944444444444444; //(2 защото звуковата вълна пътува до обекта 2 пъти)
      
      lcd.setCursor(0, 0);
      lcd.print("Distance: "); 
      lcd.print(distanceCm); 
      lcd.print(" ");
      lcd.print("cm");
      
      lcd.setCursor(0,1);
      lcd.print("Distance: ");
      lcd.print(distanceInch);
      lcd.print(" ");
      lcd.print("inch"); //тук се изписва дистанцията в сантиметри и в инчове
      

      if(distanceCm<15 && distanceCm>=10)
      {
        tone (buzzerPin, 256, 500);      //тук говорителят издава звук, след което led-то се включва и светва зелено най-дивият цвят
        analogWrite(redPin, 0);       //след паузата се изключва светлината, за да може когато цикълът започне отново
        analogWrite(greenPin, 254);   //тя да светне пак
        analogWrite(bluePin, 0);
        delay(600);
        analogWrite(greenPin, 0);             
      }
      
      else if(distanceCm<10 && distanceCm>=5) 
      {
        tone(buzzerPin, 600, 500);       //аналогично на горният if но този път цветът е оранжев, също мн див
        analogWrite(redPin, 253); 
        analogWrite(greenPin, 165); 
        analogWrite(bluePin, 0);   
        delay(300);
        analogWrite(redPin, 0);
        analogWrite(greenPin, 0);
      }
      
      else if(distanceCm < 5)
      {
        tone(buzzerPin, 1000, 500);       
        analogWrite(greenPin, 0);
        analogWrite(redPin, 255); 
        analogWrite(bluePin, 0);
        delay(10);
        analogWrite(redPin, 0);
      }

      Serial.print("Distance: "); //разстоянието се изписва на serial монитора
      Serial.println(distanceCm);
      Serial.print(" cm");
      
      Serial.print("Distance: ");
      Serial.println(distanceInch);
      Serial.print(" in");
      
      delay(dt); //за да не тече светкавично бързо цикъла е сложен delay time(dt)
}
