#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//#include "TimerOne.h"

#define IN1 11
#define IN2 7
#define IN3 A5
#define IN4 A4
#define IN5 A3
#define IN6 A2
#define IN7 A1
#define IN8 A0

#define O1 4
#define O2 12
#define O3 6
#define O4 8
#define O5 9
#define O6 10
#define O7 5  // PWM trans
#define O8 13 // PWM trans

#define b1 SCK
#define b2 MOSI
#define b3 MISO

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET 3
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#if (SSD1306_LCDHEIGHT != 64)
#endif

bool blinknow = 0, page = 0, but1 = 0, but2 = 0, but3 = 0;

bool in[8] = {};
bool out[8] = {};
bool confirmed = 0;

byte pwm1 = 0, pwm2 = 0;

int8_t selec = 0;

void inputCheck()
{
    Serial.print("Inputs: ");
    Serial.print(digitalRead(IN1));
    Serial.print(digitalRead(IN2));
    Serial.print(digitalRead(IN3));
    Serial.print(digitalRead(IN4));
    Serial.print(digitalRead(IN5));
    Serial.print(digitalRead(IN6));
    Serial.print(digitalRead(IN7));
    Serial.println(digitalRead(IN8));

    Serial.print("buttons: ");
    Serial.print(digitalRead(b1));
    Serial.print(digitalRead(b2));
    Serial.print(digitalRead(b3));
}

void callFunc()
{
    blinknow = blinknow ^ 1;
}

void readBut()
{
    if (digitalRead(b1))
    {
        while (digitalRead(b1))
        {
            if (!page)
            {
                display1();
            }
            else
            {
                display2();
            }
        }
        but1 = 1;
        blinknow = 1;
    }
    else if (digitalRead(b2))
    {
        while (digitalRead(b2))
        {
            if (!page)
            {
                display1();
            }
            else
            {
                display2();
            }
        }
        but2 = 1;
        blinknow = 1;
    }
    else if (digitalRead(b3))
    {
        while (digitalRead(b3))
        {
            if (!page)
            {
                display1();
            }
            else
            {
                display2();
            }
        }
        but3 = 1;
        blinknow = 1;
    }
}

void readInput()
{
    in[0] = !digitalRead(IN1);
    in[1] = !digitalRead(IN2);
    in[2] = !digitalRead(IN3);
    in[3] = !digitalRead(IN4);
    in[4] = !digitalRead(IN5);
    in[5] = !digitalRead(IN6);
    in[6] = !digitalRead(IN7);
    in[7] = !digitalRead(IN8);
}

void display1()
{
    display.clearDisplay();
    display.setTextSize(0);
    display.setCursor(0, 0);
    display.print(" CEMA Test Program");
    display.setCursor(0, 15);
    display.print("   Inputs");
    display.setCursor(0, 25);
    display.print("I1: ");
    display.print((in[0]));
    display.print(" I2: ");
    display.print((in[1]));
    display.print(" I3: ");
    display.print((in[2]));
    display.setCursor(0, 35);
    display.print("I4: ");
    display.print((in[3]));
    display.print(" I5: ");
    display.print((in[4]));
    display.print(" I6: ");
    display.print((in[5]));
    display.setCursor(0, 45);
    display.print("I7: ");
    display.print((in[6]));
    display.print(" I8: ");
    display.print((in[7]));

    display.setCursor(0, 55);
    display.print("Menu = Next page");

    display.display();
}

void display2()
{
    display.clearDisplay();
    display.setTextSize(0);
    display.setCursor(0, 0);
    display.println(" Junior Test Program");
    display.setCursor(0, 15);
    display.print("   Outputs");

    display.setCursor(0, 25);
    display.print("O1: ");
    if (selec == 0 && blinknow)
    {
        display.print("_");
    }
    else
    {
        display.print(out[0]);
    }
    display.print(" O2: ");
    if (selec == 1 && blinknow)
    {
        display.print("_");
    }
    else
    {
        display.print(out[1]);
    }
    display.print(" O3: ");
    if (selec == 2 && blinknow)
    {
        display.print("_");
    }
    else
    {
        display.print(out[2]);
    }
    display.setCursor(0, 35);
    display.print("O4: ");
    if (selec == 3 && blinknow)
    {
        display.print("_");
    }
    else
    {
        display.print(out[3]);
    }
    display.print(" O5: ");
    if (selec == 4 && blinknow)
    {
        display.print("_");
    }
    else
    {
        display.print(out[4]);
    }
    display.print(" O6: ");
    if (selec == 5 && blinknow)
    {
        display.print("_");
    }
    else
    {
        display.print(out[5]);
    }
    display.setCursor(0, 45);
    display.print("T7: ");
    if (selec == 6 && blinknow)
    {
        display.print("_");
    }
    else
    {
        display.print(pwm1);
    }
    display.setCursor(60, 45);
    display.print(" T8: ");
    if (selec == 7 && blinknow)
    {
        display.print("_");
    }
    else
    {
        display.print(pwm2);
    }

    display.setCursor(0, 55);
    if (!confirmed)
    {
        if (selec == 8)
        {
            display.print("Menu = Next page");
        }
        else if (selec == 6 || selec == 7)
        {
            display.print("Menu = Edit");
        }
        else
        {
            display.print("Menu = On/Off");
        }
    }
    else
    {
        if (selec == 6 || selec == 7)
        {
            display.print("Menu = Confirm");
        }
    }

    digitalWrite(O1, out[0]);
    digitalWrite(O2, out[1]);
    digitalWrite(O3, out[2]);
    digitalWrite(O4, out[3]);
    digitalWrite(O5, out[4]);
    digitalWrite(O6, out[5]);
    analogWrite(O7, pwm1);
    analogWrite(O8, pwm2);

    display.display();
}

void runCheck()
{
  readBut();
  
  if(page)
  {
    readBut();
    if(but1 && !but2 && !but3)
    {
      if(confirmed)
      {
        if(selec==6) { pwm1++; } else { pwm2++; }
      }
      else
      {
        selec++; 
        if(selec > 8) { selec = 0; }
      }
      but1 = 0;
    }
    else if(!but1 && but2 && !but3)
    {
      if(confirmed)
      {
        if(selec==6) { pwm1--; } else { pwm2--; }
      }
      else
      {
        selec--;
        if(selec < 0) { selec = 8; }
      }
      but2 = 0;
    }
    else if(!but1 && !but2 && but3)
    {
      if(selec == 8) { page = 0; selec = 0; }
      else if(selec == 6 || selec == 7) { confirmed = confirmed^1; }
      else
      {
        out[selec] = out[selec]^1;
      }
      but3 = 0;
    }
  }
  else
  {
    readInput();
    readBut();
    if(!but1 && !but2 && but3)
    {
      page = 1; selec = 0;
      but3 = 0;
    }
    else 
    {
      but1 = 0; but2 = 0;
    }
  }
  if(!page)
  {
    display1();
  }
  else if(page)
  {
    display2();
  }
  
}




void setup() 
{
  pinMode(IN1, INPUT);  pinMode(IN2, INPUT);  pinMode(IN3, INPUT);  pinMode(IN4, INPUT);
  pinMode(IN5, INPUT);  pinMode(IN6, INPUT);  pinMode(IN7, INPUT);  pinMode(IN8, INPUT);

  pinMode(O1, OUTPUT);  pinMode(O2, OUTPUT);  pinMode(O3, OUTPUT);  pinMode(O4, OUTPUT);
  pinMode(O5, OUTPUT);  pinMode(O6, OUTPUT);  pinMode(O7, OUTPUT);  pinMode(O8, OUTPUT);

  digitalWrite(O1, LOW);  digitalWrite(O2, LOW);  digitalWrite(O3, LOW);  digitalWrite(O4, LOW);
  digitalWrite(O5, LOW);  digitalWrite(O6, LOW);  digitalWrite(O7, LOW);  digitalWrite(O8, LOW);

  pinMode(b1, INPUT); pinMode(b2, INPUT); pinMode(b3, INPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  display.clearDisplay();
  // dispaly logo
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,1);
  display.print("ICONIC");
  display.setCursor(0,25);
  display.setTextSize(1);
  display.println("NORVI CONTROLLER");
  display.setCursor(0,35); display.println("CEMA V1.0");
  display.setCursor(0,45); display.println("TEST PROGRAM");
  display.setCursor(0,55); display.println("8 DI / 6 RL / 2 TR");
  display.display();
  // Clear the buffer.
  display.clearDisplay();
  display.setTextSize(0);

  delay(2000); 

  Serial.begin(9600);

  //set timer1 interrupt at 1Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 15624;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12 and CS10 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  
}

void loop() 
{
//  digitalWrite(O1, HIGH);  digitalWrite(O2, HIGH);  digitalWrite(O3, HIGH);  digitalWrite(O4, HIGH);
//  digitalWrite(O5, HIGH);  digitalWrite(O6, HIGH);  digitalWrite(O7, HIGH);  digitalWrite(O8, HIGH);
//
//  delay(5000);
//  digitalWrite(O1, LOW);  digitalWrite(O2, LOW);  digitalWrite(O3, LOW);  digitalWrite(O4, LOW);
//  digitalWrite(O5, LOW);  digitalWrite(O6, LOW);  digitalWrite(O7, LOW);  digitalWrite(O8, LOW);
//
//  delay(5000);

//  display1();
  
  runCheck();
  
  
}

ISR(TIMER1_COMPA_vect){//timer1 interrupt 1Hz toggles pin 13 (LED)
//generates pulse wave of frequency 1Hz/2 = 0.5kHz (takes two cycles for full wave- toggle high then toggle low)
  blinknow = blinknow^1;
}
