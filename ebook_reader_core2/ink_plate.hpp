#pragma once

#include <M5Core2.h>
#include "simple_fat/SdFat.h"

enum pad_id {PAD1, PAD2, PAD3};

const int INKPLATE_1BIT = 0;

class ink_plate
{
  public:

    ink_plate()
    {
    }

    ink_plate(int mode)
    {
    }

    void begin()
    {
      M5.begin();
      define_gestures();
      sdCardInit();
    }
    
    bool sdCardInit()
    {
      const int m5core2_sd_card_spi_chip_select_pin     =  4;
      const int m5core2_sd_card_spi_clock_frequency_mhz = 25;
      return sd_card.begin(m5core2_sd_card_spi_chip_select_pin, SD_SCK_MHZ(m5core2_sd_card_spi_clock_frequency_mhz));
    }
    
    void display()
    {
    }
    
    void partialUpdate()
    {
    }

    void setTextSize(int text_size)
    {
      M5.Lcd.setTextSize(text_size);
    }
    
    void setTextColor(int text_colour, int background_colour)
    {
      M5.Lcd.setTextColor(text_colour, background_colour);
    }

    void setCursor(int x, int y)
    {
      M5.Lcd.setCursor(x, y);
    }

    int getCursorX()
    {
      return M5.Lcd.getCursorX();
    }

    int getCursorY()
    {
      return M5.Lcd.getCursorY();
    }

    void clearDisplay()
    {
      M5.Lcd.fillScreen(WHITE);
    }

    void println()
    {
      M5.Lcd.print('\n');
    }
    
    void print(const char* s)
    {
      M5.Lcd.print(s);
    }
    
    void println(const char* s)
    {
      M5.Lcd.print(s);
      M5.Lcd.print("\n");
    }

    void print(char c)
    {
      M5.Lcd.print(c);
    }

    void println(char c)
    {
      M5.Lcd.print(c);
      M5.Lcd.print("\n");
    }

    void print(int n)
    {
      M5.Lcd.print(n);
    }

    void println(int n)
    {
      M5.Lcd.print(n);
      M5.Lcd.print("\n");
    }
    
    void print(double x)
    {
      M5.Lcd.print(x);
    }
    
    void println(double x)
    {
      M5.Lcd.print(x);
      M5.Lcd.print("\n");
    }
    
    int width()
    {
      return M5.Lcd.width();
    }
    
    int height()
    {
      const int printed_button_bar_height = 15;
      return M5.Lcd.height() - printed_button_bar_height;
    }
     
    void setRotation(int rotation)
    {
      switch (rotation)
      {
        case 1: M5.Lcd.setRotation(1); break;
        case 2: M5.Lcd.setRotation(0); break;
        case 3: M5.Lcd.setRotation(2); break;
        case 4: M5.Lcd.setRotation(3); break;
      }
    }
    
    void getTextBounds(const char *s, int16_t x0, int16_t y0, int16_t *x, int16_t *y, uint16_t *dx, uint16_t *dy)
    {
      *x = x0;
      *y = y0;
      *dx = (unsigned short)M5.Lcd.textWidth(s);
      *dy = (unsigned short)M5.Lcd.fontHeight(); 
    }
    
    void setTextWrap(bool on)
    {
      M5.Lcd.setTextWrap(on, false);
    }
    
    void fillCircle(int xc, int yc, int r, int colour)
    {
      M5.Lcd.fillCircle(xc, yc, r, colour);
    }
    
    void drawCircle(int xc, int yc, int r, int colour)
    {
      M5.Lcd.drawCircle(xc, yc, r, colour);
    } 
    
    bool readTouchpad(int pad)
    {
      M5.update();
      switch (pad)
      {
        case PAD1: if (button_a_pressed) { button_a_pressed = false; return true; } else return false;
        case PAD2: if (button_b_pressed) { button_b_pressed = false; return true; } else return false;
        case PAD3: if (button_c_pressed) { button_c_pressed = false; return true; } else return false;
      }
    }

    double readBattery()
    {
      return M5.Axp.GetBatVoltage();
    }

    double readTemperature()
    {
      return M5.Axp.GetTempInAXP192();
    }
    
    void setFont()
    {
      M5.Lcd.setFont(nullptr);
    }
    
    void setFont(const GFXfont* font)
    {
      M5.Lcd.setFont(font);
    }
    
    void einkOff()
    {
    }
    
    void einkOn()
    {
    }

  private:

    SdFat       sd_card;

    static Gesture     swipe_down;
    static Gesture     swipe_up;
    static Gesture     swipe_left;
    static Gesture     swipe_right;

    static bool button_a_pressed;
    static bool button_b_pressed;
    static bool button_c_pressed;

    void define_gestures()
    {
      const int zone_size  = 100;
      const int x_boundary = M5.Lcd.width()  - zone_size;
      const int y_boundary = M5.Lcd.height() - zone_size;

      swipe_down .fromZone.set(0,          0,          M5.Lcd.width(), zone_size      );
      swipe_down .toZone  .set(0,          y_boundary, M5.Lcd.width(), zone_size      );
      
      swipe_up   .fromZone.set(0,          y_boundary, M5.Lcd.width(), zone_size      );
      swipe_up   .toZone  .set(0,          0,          M5.Lcd.width(), zone_size      );
      
      swipe_left .fromZone.set(x_boundary, 0,          zone_size,      M5.Lcd.height());
      swipe_left .toZone  .set(0,          0,          zone_size,      M5.Lcd.height());
      
      swipe_right.fromZone.set(0,          0,          zone_size,      M5.Lcd.height());
      swipe_right.toZone  .set(x_boundary, 0,          zone_size,      M5.Lcd.height());
      
      swipe_down .addHandler(handle_gesture);
      swipe_up   .addHandler(handle_gesture);
      swipe_left .addHandler(handle_gesture);
      swipe_right.addHandler(handle_gesture);
      
      M5.Buttons .addHandler(button_pressed, E_PRESSED);
    }

    static void button_pressed(Event& e)
    {
      Button& button = *e.button;
      if      (button == &M5.BtnA) button_a_pressed = true;
      else if (button == &M5.BtnB) button_b_pressed = true;
      else if (button == &M5.BtnC) button_c_pressed = true;
    }

    static void handle_gesture(Event& e)
    {
      if      (*e.gesture == swipe_up   ) button_c_pressed = true;
      else if (*e.gesture == swipe_down ) button_c_pressed = true;
      else if (*e.gesture == swipe_left ) button_b_pressed = true;
      else if (*e.gesture == swipe_right) button_a_pressed = true;
    }
      
};
