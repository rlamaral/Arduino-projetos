#include <LiquidCrystal.h>

#define VITESSE_PAC 150
#define VITESSE_FANT 2000
#define MAXX 15
#define MAXY 1

#define btnRight 0
#define btnUp 1
#define btnDown 2
#define btnLeft 3
#define btnSelect 4
#define btnNone 5

#define PV 28;
#define SP 22;

long keystruck = 0;  //dernier appui sur un bouton
long poursuite = 0;  //dernier movement du fantome
byte level = 0;      // niveau

int setPoint = SP;
int VarProcesso = PV;

void (*resetFunc)(void) = 0;
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);


void setup() {
  Serial.begin(9600);
  lcd.clear();
  delay(1000);

  // put your setup code here, to run once:
  lcd.begin(16, 2);
  lcd.print("***BRTEC  V01***");  // texto fixo inicial

  for (int positionCounter = 0; positionCounter < 16; positionCounter++) {
    // scroll one position left:
    lcd.scrollDisplayLeft();
    // wait a bit:
    delay(150);
  }

  // scroll 29 positions (string length + display length) to the right
  // to move it offscreen right:
  for (int positionCounter = 0; positionCounter < 32; positionCounter++) {
    // scroll one position right:
    lcd.scrollDisplayRight();
    // wait a bit:
    delay(150);
  }

  // scroll 16 positions (display length + string length) to the left
  // to move it back to center:
  for (int positionCounter = 0; positionCounter < 16; positionCounter++) {
    // scroll one position left:
    lcd.scrollDisplayLeft();
    // wait a bit:
    delay(150);
  }


delay(1000);


  lcd.setCursor(0, 1);            // on se place  caractere)
  lcd.print("SP: ");
  //lcd.setCursor(0, 1);
  lcd.print(setPoint);
  lcd.setCursor(10, 1);  // on se place caractere)
  lcd.print("PV: ");
  lcd.print(VarProcesso);
}

void loop() {
  // put your main code here, to run repeatedly:
  int thisChar = Serial.read();
  switch (thisChar) {
    case 'r':
      lcd.scrollDisplayRight();
      break;
    case 'l':
      lcd.scrollDisplayLeft();
      break;
  }
  if ((thisChar > 'a') & (thisChar < 'z')) {
    lcd.setCursor(1, 1);
    lcd.write(thisChar);
  }
  if (millis() - keystruck > VITESSE_PAC)  // Si plus de 200ms depuis le dernier mouvement de joystick
  {
    int joy = getKey();
    switch (joy) {
      case btnNone:
        break;
      case btnLeft:
        Serial.print("Pacman bouge à gauche.\n");  // envoi de controle sur liaison série
        Serial.print(keystruck);

        keystruck = millis();  // remise à zero du timer de mouvement
        break;
      case btnRight:
        Serial.print("Pacman bouge à droite\n");  // envoi de controle sur liaison série

        keystruck = millis();  // remise à zero du timer de mouvement
        break;
      case btnUp:

        setPoint += 1;
        Serial.println(setPoint);
        lcd.setCursor(0, 1);  // on se place  caractere)
        lcd.print("SP: ");
        //lcd.setCursor(0, 1);
        lcd.print(setPoint);

        keystruck = millis();  // remise à zero du timer de mouvement
        break;
      case btnDown:
        setPoint -= 1;
        Serial.println(setPoint);
        lcd.setCursor(0, 1);  // on se place  caractere)
        lcd.print("SP: ");
        //lcd.setCursor(0, 1);
        lcd.print(setPoint);

        keystruck = millis();  // remise à zero du timer de mouvement
        break;
        /*case 4:
       Serial.print("centre\n");
       light=!light; //On inverse le statut d'allumage
       lcd.backLight(light); // on applique
       keystruck=millis(); // remise à zero du timer de mouvement
       break;*/
      default:
        Serial.print(joy);     //au cas ou...
        keystruck = millis();  // remise à zero du timer de mouvement
    };
  };
  if (millis() - poursuite > VITESSE_FANT / (level + 1) + 10) {
    //poursuis();
    poursuite = millis();
  }
}




int getKey() {
  int b = analogRead(A0);
  delay(350);
  if (b > 1000) return btnNone;
  delay(8);
  if (b < 50) return btnRight;
  if (b < 180) return btnUp;
  if (b < 330) return btnDown;
  if (b < 520) return btnLeft;
  if (b < 700) return btnSelect;
}
