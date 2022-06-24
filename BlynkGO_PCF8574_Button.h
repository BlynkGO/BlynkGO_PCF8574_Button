#ifndef __BLYNKGO_PCF8574_BUTTON_H__
#define __BLYNKGO_PCF8574_BUTTON_H__

#include <Arduino.h>
#include <PCF8574.h>

class PCF8574_Button {
  public:
    PCF8574_Button(PCF8574& pcf8574,uint8_t pin, bool pressed=HIGH);

    typedef void (*PCF8574_btn_cb) (PCF8574_Button* );

    void init();
    void loop();
    inline void run() { loop(); }

    inline void onPressed(PCF8574_btn_cb fn)      { if(!_inited) init(); pressed_cb = fn;       }
    inline void onPressing(PCF8574_btn_cb fn)     { if(!_inited) init(); pressing_cb = fn;      }
    inline void onLongPressed(PCF8574_btn_cb fn)  { if(!_inited) init(); long_pressed_cb = fn;  }
    inline void onLongPressed(uint32_t longpressed_ms, PCF8574_btn_cb fn)  { this->onLongPressed(fn); _longpressed_ms = longpressed_ms; }
    inline void onReleased(PCF8574_btn_cb fn)     { if(!_inited) init(); released_cb = fn;      }
    inline void onClicked(PCF8574_btn_cb fn)      { if(!_inited) init(); clicked_cb = fn;       }
    inline void debouncing_time(uint32_t debouncing_ms)     { _debouncing_ms = debouncing_ms;   }
    inline void longpressed_time(uint32_t longpressed_ms)   { _longpressed_ms = longpressed_ms; }

    PCF8574_btn_cb pressed_cb=NULL;
    PCF8574_btn_cb pressing_cb=NULL;
    PCF8574_btn_cb long_pressed_cb=NULL;
    PCF8574_btn_cb released_cb=NULL;
    PCF8574_btn_cb clicked_cb=NULL;
    
  private:
    bool      _inited = false;
    bool      _PRESSED = HIGH;
    uint8_t   _pin;
    uint32_t  _debouncing_ms = 80;
    uint32_t  _longpressed_ms = 1500;
    bool      _is_longpressed=false;
    uint32_t  _timer_pressed;
    uint32_t  _timer;
    PCF8574   *_pcf8574=NULL;
    uint8_t   _state;
};

#endif //__BLYNKGO_PCF8574_BUTTON_H__
