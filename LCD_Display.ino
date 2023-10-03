#include<LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

#include <SoftwareSerial.h>
SoftwareSerial Serial1(9, 10); // RX, TX

char str[70];
char *test="$GPRMC";
int temp,i,count=0;

void setup() 
{
  lcd.begin(16,2);
  Serial1.begin(9600);
  lcd.setCursor(0,0);
  lcd.print("Sivagopal");
  lcd.setCursor(0,1);
  lcd.print(" Jyothi Sri");
  delay(300);
}

void loop()
{
  serial1Event();
  if (temp) 
  {
    lcd.clear();
    int str_lenth=i;
    int x=0,comma=0;
    String UTC_hour="";
    String UTC_minut="";
    String UTC_second="";
    String UTC_date="";
    String UTC_month="";
    String UTC_year="";
    String str1="";
    String Latitude_Deg="";
    String Latitude="";
    String Longitude_Deg="";
    String Longitude="";
    //String Speed = "";
    //String Course ="";
    
    while(x<str_lenth)
    {
     if(str[x]==',')
     comma++;
      if(comma==1)
      {
        x++;
        UTC_hour+=str[x++];
        UTC_hour+=str[x++];
        UTC_minut+=str[x++];
        UTC_minut+=str[x++];
        UTC_second+=str[x++];
        UTC_second+=str[x];
        comma=2;
      }

      else if(comma==4)
      {
        x++;
        Latitude_Deg+=str[x++];
        Latitude_Deg+=str[x++];
        Latitude_Deg+=str[x++];
        Latitude_Deg+=str[x];
        
        comma=5;
      }

       /*else if(comma==4)
      {
        x++;
        Latitude=str[x++];
       
        
        //comma=2;
      }*/

       else if(comma==7)
      {
        x++;
        Longitude_Deg+=str[x++];
        Longitude_Deg+=str[x++];
        Longitude_Deg+=str[x++];
        Longitude_Deg+=str[x++];
        Longitude_Deg+=str[x];
        
        comma=8;
      }

     /*  else if(comma==6)
      {
        x++;
        Longitude=str[x++];
       
        
        //comma=2;
      } */

      else if(comma==12)
      {
        x++;
          UTC_date+=str[x++];
          UTC_date+=str[x++];
          UTC_month+=str[x++];
          UTC_month+=str[x++];
          UTC_year+=str[x++];
          UTC_year+=str[x];
      } 
      else { 
      x++;
      }
    }

    int UTC_hourDec=UTC_hour.toInt();
    int UTC_minutDec=UTC_minut.toInt();
    int Second=UTC_second.toInt();
    int Date=UTC_date.toInt();
    int Month=UTC_month.toInt();
    int Year=UTC_year.toInt();
    //int LatitudeDec=Latitude_Deg.toInt();
    //int LongitudeDec=Longitude_Deg.toInt();

    int Hour=UTC_hourDec+5;
    if(Hour>23)
    {
     Hour-=24;
     Date+=1;
    }
    int Minut=UTC_minutDec+30;
    if(Minut>59)
    Minut-=60;
    
    if(count){
      lcd.clear();
      lcd.print("Latitude: ");
      lcd.print(Latitude_Deg);
      
     
      lcd.setCursor(0,1);
      lcd.print("Longitude: ");
      lcd.print(Longitude_Deg);

      temp=0;
      i=0;
      x=0;
      str_lenth=0;
      count++;
    }

    else {
   // UTC_ind_zone_time
    lcd.clear();
    lcd.print("Date: ");
    lcd.print(Date);
    lcd.print("/");
    lcd.print(Month);
    lcd.print("/");
    lcd.print("20");
    lcd.print(Year);
     
    lcd.setCursor(0,1);
    lcd.print("Time: ");
    lcd.print(Hour);
    lcd.print(":");
    lcd.print(Minut);
    lcd.print(":");
    lcd.print(Second);
    temp=0;
    i=0;
    x=0;
    str_lenth=0;
    count--;

  }
}
}

void serial1Event()
{
  while(1)
  {
   while (Serial1.available())            //checking serial data from GPS
   {
    char inChar = (char)Serial1.read();
     str[i]= inChar;                    //store data from GPS into str[]
     i++;
     if (i < 7)                      
     {
      if(str[i-1] != test[i-1])         //checking for $GPRMC sentence
      {
        i=0;
      }
     }
    if(i>65)
    {
     temp=1;
     break;
    }
  }
   if(temp)
    break;
  }
}
