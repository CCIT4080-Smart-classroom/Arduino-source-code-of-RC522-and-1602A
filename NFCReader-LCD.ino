#include <SPI.h> 

#include <MFRC522.h>

#include <Wire.h> 

#include <LiquidCrystal_I2C.h>

#define SS_PIN 10 

#define RST_PIN 9 

LiquidCrystal_I2C lcd(0x27,16,2);

MFRC522 mfrc522(SS_PIN, RST_PIN); // Instance of the class

int SID[2][4] = {{214, 248, 28, 240}, {37, 223, 35, 0}}; //This is the stored UID (Unlock Card) (card 3: 34, 228, 143, 30): didnt add in code

int codeRead = 0;

String uidString;




void setup() {
  Serial.begin(9600); 
  SPI.begin();       // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522 
  lcd.init(); // Print a message to the LCD
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Show your SID");
  lcd.setCursor(0, 1);
  lcd.print("card");
}




void loop() {
if ( mfrc522.PICC_IsNewCardPresent())
    {
        if ( mfrc522.PICC_ReadCardSerial())
        {

           lcd.clear();

           //Serial.print("Tag UID:");
           lcd.setCursor(0,0);
           lcd.print("Tag UID:");
           lcd.setCursor(0,1);


           for (byte i = 0; i < mfrc522.uid.size; i++) {  
                  lcd.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
                  lcd.print(mfrc522.uid.uidByte[i], HEX);
            }
            boolean match = true;
            int tmp;
            for (int j = 0; j<2; j++) 
            {
              match = true;
              for(int i= 0; i < 4; i++)
              {

               if(!(int(mfrc522.uid.uidByte[i]) == int(SID[j][i]))) 
                {
                  match = false;
                }
               }
               if (match == true)
               {
                 tmp=j;
                 break;
               }
            }



          delay(3000);

           lcd.clear();

           lcd.setCursor(0,0);


           if(match)
           {
             lcd.print("valid SID card");
             switch (tmp)
             {
              case 0:
              {
                Serial.println("20178374"); //Student: Ng Tsz Chiu 
                delay(3000);
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("Welcome!");
                lcd.setCursor(0,1);
                lcd.print("Ng Tsz Chiu");
                break;
              }
              case 1:
              {
                Serial.println("12345678"); //Student: Chim 
                delay(3000);
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("Welcome!");
                lcd.setCursor(0,1);
                lcd.print("Chim");
                break;
              }
  
             }
           }else{
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("Unknow SID Card");
              delay(3000);
              lcd.setCursor(0,0);
              lcd.print("Please try again");
           }
             mfrc522.PICC_HaltA();
             delay(3000); 
             reset_state();
        }
}
}
void reset_state()
{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Show your SID");
    lcd.setCursor(0, 1);
    lcd.print("card");
}
