#include <Wire.h>
#include "customChar.h"

LiquidCrystal_I2C lcd(0x27, 16, 2); 
//Input I2C address after check address at the first parameter

void setup() {
  lcd.init();
  lcd.backlight();
}

void loop() { 
  LCD_Cursor();
  delay(1000); lcd.clear(); delay(1000);

  LCD_Scroll();
  delay(1000); lcd.clear(); delay(1000);

  LCD_Align();
  delay(1000); lcd.clear(); delay(1000);

  LCD_Custom();
  delay(1000); lcd.clear(); delay(1000);
}

void LCD_Cursor(void)
{
  char temp[16] = "01234567abcdef";
  int Interval = 500;
  //lcd.noCursor();
  lcd.cursor();
  //lcd.noBlink();
  lcd.blink();
  
  for (int i=0; i<8 ; i++)
  {
    lcd.setCursor(2*i,0);
    delay(Interval);
    lcd.print(temp[i]);
  }

  for (int i=0; i<8 ; i++)
  {
    lcd.setCursor(2*i+1,1);
    delay(Interval);
    lcd.print(temp[i+8]);
  }
}

void LCD_Scroll(void)
{
  lcd.noCursor();
  lcd.noBlink();
  lcd.setCursor(0,0);
  lcd.print("hello");
  delay(500);
  for (int i=0 ; i<11 ; i++)
  {
    lcd.scrollDisplayRight();
    delay(500);
  }

  for (int i=0 ; i<11 ; i++)
  {
    lcd.scrollDisplayLeft();
    delay(500);
  }
}

void LCD_Align(void)
{
  lcd.leftToRight();
  lcd.setCursor(0,0);
  lcd.print("  Hello World!  ");
  delay(500);

  lcd.rightToLeft();
  lcd.setCursor(15,1);
  lcd.print("  Hello World!  ");
  delay(500);
}

void LCD_Custom(void)
{
  lcd.createChar(0, CC1);
  lcd.createChar(1, CC2);
  lcd.createChar(2, CC3);
  lcd.createChar(3, CC4);
  lcd.createChar(4, CC5);
  lcd.createChar(5, CC6);
  lcd.createChar(6, CC7);
  lcd.createChar(7, CC8);

  for(int i=0 ; i<4 ; i++)
  {
    lcd.setCursor(4*i,0);
    lcd.write(i);
    delay(500);

    lcd.setCursor(4*i+2,1);
    lcd.write(i+4);
    delay(500);
  }
}
