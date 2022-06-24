#include "BlynkGO_PCF8574_Button.h"

enum { BTN_ST_STANDBY, BTN_ST_PRESSED, BTN_ST_PRESSING, BTN_ST_RELEASED };

PCF8574_Button::PCF8574_Button(PCF8574& pcf8574,uint8_t pin, bool pressed)
: _pcf8574(&pcf8574), _pin(pin), _PRESSED(pressed), _state(BTN_ST_RELEASED)
{
}

void PCF8574_Button::init(){
  if(_inited) return;
  _inited = true;
  Serial.println("[PCF8574 Button] inited.");
}

void PCF8574_Button::loop(){
  switch(_state){
    case BTN_ST_STANDBY:
      if( millis() >= _timer ){
        _timer = millis() + _debouncing_ms;
        if(_pcf8574->digitalRead(_pin) == _PRESSED){
          _state = BTN_ST_PRESSED;
          _timer_pressed = millis();
          _is_longpressed=false;
          if(pressed_cb) pressed_cb(this);
        }
      }
      break;
    case BTN_ST_PRESSED:
      if( millis() >= _timer ){
        _timer = millis() + _debouncing_ms;
        if(_pcf8574->digitalRead(_pin) == _PRESSED){
          _state = BTN_ST_PRESSING;
          if(pressing_cb) pressing_cb(this);
        }else{
          _state = BTN_ST_RELEASED;   
          if(released_cb) released_cb(this);
          if(clicked_cb)  clicked_cb(this);
          _is_longpressed=false;
        }
      }    
      break;
    case BTN_ST_PRESSING:
      if( millis() >= _timer ){
        _timer = millis() + _debouncing_ms;
        if(_pcf8574->digitalRead(_pin) == _PRESSED){
          if(pressing_cb) pressing_cb(this);
          if(!_is_longpressed){
            if(_timer_pressed + _longpressed_ms <= millis()){
              if(long_pressed_cb) long_pressed_cb(this);
              _is_longpressed = true;
            }
          }
        }else{
          _state = BTN_ST_RELEASED;
          if(released_cb) released_cb(this);
          if(clicked_cb)  clicked_cb(this);
          _is_longpressed=false;
        }
      }
      break;
    case BTN_ST_RELEASED:
      _timer = millis() + _debouncing_ms;
      _state = BTN_ST_STANDBY;
      break;
  }
}
