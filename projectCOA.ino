#include<Keypad.h>
#include<string.h>
#include<LiquidCrystal.h>
char keys [4][4] = {
  {'1' , '2', '3', 'A'},
  {'4' , '5', '6', 'B'},
  {'7' , '8', '9', 'C'},
  {'.' , '0', '#', 'D'}
};
LiquidCrystal lcd(8,9,10,11,12,13);
byte rowPins[4] = {19, 18, 2, 3};
byte colPins[4] = {4, 5, 6, 7};

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, 4, 4);

char sendToPy[150] = "";
int countPy = 0;
char displayToScreen[150] = "";
int countScreen = 0;
char answerToDisplay[150] = "";
int answerCount = 0;
int flag = 0;
int cont = 0;
void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Calculator");
  delay(1000);
  lcd.clear();
  lcd.print("Ready");
  delay(500);
  lcd.clear();
}

void loop()
{
  lcd.cursor();
  char key = kpd.waitForKey();
  if(key != NO_KEY)//If key is pressed
  {
    if(key!='A'&& key!='B'&&key!='C'&&key!='D'&&key!='#')
    {
    sendToPy[countPy++] = key;
    displayToScreen[countScreen++] = key;
    }
    else
    {
      if(key =='A'){
      sendToPy[countPy++] = '+';
      displayToScreen[countScreen++] = '+';
      }
      else
      if(key =='B')
      {
      sendToPy[countPy++] = '-';
      displayToScreen[countScreen++] = '-';
      }
      else
      if(key =='C')
      {
      sendToPy[countPy++] = '*';
      displayToScreen[countScreen++] = '*';
      //displayonScreen();
      }
      else
      if(key =='D'){
      sendToPy[countPy++] = '/';
      displayToScreen[countScreen++] = '/';
      }
      else{
      shift();
      
    }
  }
  if(!flag)
  displayonScreen();
  flag = 0;
}
}
void shift()
{
  char key = kpd.waitForKey();
  if(key!= NO_KEY)//Check if key is pressed
  {
      if(key == '1')
      {
        lcd.scrollDisplayLeft();
        flag++;
        return;
      }
      else
      if(key == '3')
      {
        lcd.scrollDisplayRight();
        flag++;
        return;
      }
      else
      if(key == '4')
      {
      sendToPy[countPy++] = '(';
      displayToScreen[countScreen++] = '(';
      return;
      }
      else
      if(key == '6')
      {
      sendToPy[countPy++] = ')';
      displayToScreen[countScreen++] = ')';
      return;
      }
      else
      if(key =='A'){
      sendToPy[countPy++] = '*';
      sendToPy[countPy++] = '*';
      displayToScreen[countScreen++] = '^';
      return;
      }
      else
      if(key =='B'){
      trigo();
      return;
      }
      else
      if(key =='C'){
      sendToPy[countPy++] = 'l';
      sendToPy[countPy++] = 'o';
      sendToPy[countPy++] = 'g';
      sendToPy[countPy++] = '(';
      displayToScreen[countScreen++] = 'l';
      displayToScreen[countScreen++] = 'o';
      displayToScreen[countScreen++] = 'g';
      displayToScreen[countScreen++] = '(';
      return;
      }
      else
      if(key =='D')
      {
        Serial.println(sendToPy);
        delay(500);
        displayAnswer();
        if(!cont)
        reset();
        cont = 0;
      }
      else
      if(key == '0'){
      lcd.clear();
      lcd.print("**CLEAR SCREEN**");
      delay(1000);
      reset();
      lcd.clear();
      lcd.print("");
      }
      else
      if(key == '.'){
        deletech();
      }
      return;
  }
  return;
}

void trigo()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("1.sin A 2.cos A");
  lcd.setCursor(0,1);
  lcd.print("3.tan A");
  char key = kpd.waitForKey();
  if(key!= NO_KEY)
  {
    if(key=='1')
    {
      sendToPy[countPy++] = 's';
      sendToPy[countPy++] = 'i';
      sendToPy[countPy++] = 'n';
      sendToPy[countPy++] = '(';
      displayToScreen[countScreen++] = 's';
      displayToScreen[countScreen++] = 'i';
      displayToScreen[countScreen++] = 'n';
      displayToScreen[countScreen++] = '(';
      return;
    }
    else
    if(key=='2')
    {
      sendToPy[countPy++] = 'c';
      sendToPy[countPy++] = 'o';
      sendToPy[countPy++] = 's';
      sendToPy[countPy++] = '(';
      displayToScreen[countScreen++] = 'c';
      displayToScreen[countScreen++] = 'o';
      displayToScreen[countScreen++] = 's';
      displayToScreen[countScreen++] = '(';
      return;
    }
    
    else
    if(key =='3')
    {
      sendToPy[countPy++] = 't';
      sendToPy[countPy++] = 'a';
      sendToPy[countPy++] = 'n';
      sendToPy[countPy++] = '(';
      displayToScreen[countScreen++] = 't';
      displayToScreen[countScreen++] = 'a';
      displayToScreen[countScreen++] = 'n';
      displayToScreen[countScreen++] = '(';
      return;
    }
    else
    return;
  }
  return;
}

void displayAnswer()
{
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.noCursor();
  while(Serial.available())
  {
    char ch = char(Serial.read());
    if(ch!='\n')
    {
      lcd.print(ch);
    }
    else
    {
      answerToDisplay[answerCount] = '\0';
    }
  }
  lcd.setCursor(0,0);
  lcd.print(displayToScreen);
  char key = kpd.waitForKey();
  if(key!= NO_KEY)
  {
    if(key=='D')
    cont++;
  }
  return;
}
void displayonScreen()
{
  lcd.clear();
  if(countScreen>=16)
  {
    int temp = countScreen - 15;
    while(temp != 0)
    {
      lcd.scrollDisplayLeft();
      temp--;
    }
  }
  lcd.print(displayToScreen);
}

void deletech()
{
  if(countScreen==0) return;
  displayToScreen[--countScreen] = '\0';
  sendToPy[--countPy] = '\0';
  displayonScreen();
  char key = kpd.waitForKey();
  if(key!= NO_KEY)
  {
    while(key=='.'&&countScreen)
    {
      displayToScreen[--countScreen] = '\0';
      sendToPy[--countPy] = '\0';
      displayonScreen();
      if(countScreen)
      key = kpd.waitForKey();
      else return;
    }
    return;
    
  }
  }
void reset()
{
  lcd.clear();
  lcd.setCursor(0,0);
  memset(sendToPy,0,sizeof(sendToPy));
  countPy = 0;
  memset(displayToScreen,0,sizeof(displayToScreen));
  countScreen = 0;
  memset(answerToDisplay,0,sizeof(answerToDisplay));
  answerCount = 0;
}



