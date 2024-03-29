# BlynkGO_PCF8574_Button
 ไลบรารี่สำหรับ ทำขา PCF8574 I/O expander I2C  
ให้มาทำเป็นปุ่มกด โดยยกระดับ code ให้กลายเป็นระบบ event  
ซึ่งจะช่วยให้ code สั้น กระชับ ยิ่งขึ้น
  
<p align="left">
  <img src="PCF8574_RefrigButton_Wiring.png" alt="image"/>
</p>  
  
  
<p align="left">
  <img src="PCF8574_RefrigButton_Wiring_MEGA.png" alt="image"/>
</p>  


## PCF8574 I2C Address
  
<p align="left">
  <img src="PCF8574_address.png" alt="image"/>
</p>  


## Example

```cpp
#include <PCF8574.h>                       // https://github.com/xreef/PCF8574_library
#include "BlynkGO_PCF8574_Button.h"

#define PCF8574_ADDR      0x20
#define PCF8574_PIN       P0

PCF8574 pcf8574(PCF8574_ADDR);
PCF8574_Button button(pcf8574, PCF8574_PIN);
//PCF8574_Button button(pcf8574, PCF8574_PIN, LOW); // หาก ปุ่มกด เมื่อมีการกดมีสถานะเป็น LOW

void setup() {
  Serial.begin(115200); Serial.println();
  pcf8574.pinMode(PCF8574_PIN, INPUT);
  if (!pcf8574.begin()){
    Serial.println("[PCF8574] failed");
    return;
  }
  
  button.onPressed([](PCF8574_Button* btn){
    Serial.println("[Button] Pressed");
  });

  button.onPressing([](PCF8574_Button* btn){
    Serial.println("[Button] Pressing");
  });

  button.onLongPressed(1200,[](PCF8574_Button* btn){
    Serial.println("[Button] Long Pressed");
  });

  button.onReleased([](PCF8574_Button* btn){
    Serial.println("[Button] Released");
  });
  
  button.onClicked([](PCF8574_Button* btn){
    Serial.println("[Button] Clicked");
  });
}

void loop() {
  button.loop();
}

```
  
  
Friday 24/06/2022  
BlynkGO  
