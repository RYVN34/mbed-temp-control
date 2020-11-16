#include "mbed.h"
#include "TextLCD.h"
TextLCD lcd(p19, p20, p21, p22, p23, p24);                                      // LCD Display
DigitalIn OnButton(p8);                                                         // Switch Button
AnalogIn Ain(p15);                                                              // Temperature Sensor
DigitalOut b_LED(p5);                                                           // Blue LED
DigitalOut y_LED(p6);                                                           // Yellow LED
DigitalOut g_LED(p7);                                                           // Green LED
PwmOut PWM1 (p25);                                                              // Pulse Width Modulation

float ADCdata;
float FanSpeed;
float i;
`
int main() {
    
  while(1) {      
        ADCdata = Ain*3.3*100;                                                  // F to C conversion
        FanSpeed = PWM1*100;                                                    // Get fan speed percentage
        lcd.printf("Temp: %1.1fC\n", ADCdata);                                  // Temperature value displayed in LCD 
      if (OnButton==1){                                                         // Fan speed displayed in LCD
        lcd.printf("Fan Speed: %1.0f%%%", FanSpeed); 
        } 
      if (OnButton==0){                                                         // Display SYSTEM OFF in LCD
        lcd.printf("   SYSTEM OFF"); 
        }
        wait(0.5);
        lcd.cls();
        
   if (OnButton==1){                                                            // System ON
      if (ADCdata <=26){                                                        // Low Rom Temperature (Cold)
         b_LED = 1;                                                             // Blue LED on
         y_LED = 0;
         g_LED = 0;
         PWM1.period(0.010); 
         PWM1 = 0.2;                                                            // Fan @ Low Speed
         }    
      if (ADCdata >=26 && ADCdata <= 29){                                       // Medium Room Temperature (Moderate)
         b_LED = 0;
         y_LED = 1;                                                             // Yellow LED on
         g_LED = 0;
         PWM1.period(0.010);
         PWM1 = 0.5;                                                            // Fan @ Half Speed 
         }  
      if (ADCdata >=29){                                                        // High Room Temperature (Hot)
         b_LED = 0;
         y_LED = 0;
         g_LED = 1;                                                             // Green LED on
         PWM1.period(0.010);
         PWM1 = 1;                                                              // Fan @ Full Speed
         } 
    }   
    
   else {                                                                       // System Off
         b_LED = 0;                                                             // All LEDs Off
         y_LED = 0;
         g_LED = 0;
         PWM1 = 0;                                                              // Fan Off
         }  
    }
}
