#include <SPI.h> 

#include <MFRC522.h>

#include <Wire.h> 

#include <LiquidCrystal_I2C.h>



#define SS_PIN 10 

#define RST_PIN 9 




LiquidCrystal_I2C lcd(0x27,16,2);

MFRC522 mfrc522(SS_PIN, RST_PIN); // Instance of the class



int SID[2][4] = {{214, 248, 28, 240}, {37, 223, 35, 0}}; //To stored UID (Cards have access), a 2D matrix, (card 3[test tag]: 34, 228, 143, 30): didn’t add in code

int codeRead = 0;

String uidString;


void setup() {

   Serial.begin(9600); 

   SPI.begin();       // Init SPI bus

   mfrc522.PCD_Init(); // Init MFRC522 

   Serial.println("Arduino RFID reading UID");





   lcd.init();

  // Print a message to the LCD.

  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("Show your SID");
  lcd.setCursor(0, 1);
  lcd.print("card");

}

void loop() { // a loop to read the card

  

if ( mfrc522.PICC_IsNewCardPresent())

    {

        if ( mfrc522.PICC_ReadCardSerial())

        {

           lcd.clear();

           Serial.print("Tag UID:");    // Print a message to the LCD

           lcd.setCursor(0,0);

           lcd.print("Tag UID:");

           lcd.setCursor(0,1);

           for (byte i = 0; i < mfrc522.uid.size; i++) {    // a for loop to read UID

                  Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "); 

                  Serial.print(mfrc522.uid.uidByte[i], HEX);

                  

                  lcd.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");

                  lcd.print(mfrc522.uid.uidByte[i], HEX);

                //  lcd.print(" ");

            }

            

            Serial.println();



            

            
            boolean match = true;
            int tmp;
            for (int j = 0; j<2; j++)  // to read the 2D matrix of the stored UID

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

           

           
  
           if(match)  // if the UID is match with the card id which stored in SID 

           {
             lcd.print("valid SID card");
             switch (tmp)

             {
              case 0:   //if read the card of James’s one, print his name, student ID in the serial monitor. Show his name and welcome on LCD
              {
                Serial.println("\nStudent: Ng Tsz Chiu \nSID: 20178374");
                delay(3000);
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("Welcome!");
                lcd.setCursor(0,1);
                lcd.print("Ng Tsz Chiu");
                break;
              }
              case 1:   //if read the UID of the test card, assume it is Chim ID card, print his name, student ID in the serial monitor. Show his name and welcome on LCD
              {
                Serial.println("\nStudent: Chim \nSID: 00000000");
                delay(3000);
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("Welcome!");
                lcd.setCursor(0,1);
                lcd.print("Chim");
                break;
              }
  
             }

              

           

    

           }else{ //if the UID read from the nfc reader in not stored in SID, print the following messages

     

              lcd.print("invalid SID card"); 

             Serial.println("\nUnknown SID Card");

           }

             

             Serial.println("============================");

            

             mfrc522.PICC_HaltA();



             delay(3000); 

             reset_state();

        }

}

}

void reset_state() //reset every things after read a card

{

    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print("Show your SID");
    lcd.setCursor(0, 1);
    lcd.print("card");

    


}
