
/*
 * Velleman VMA 437 OLED Graphics Test
 * 
 * Gnd -> Gnd
 * Vcc -> 5V 
 * CLK -> D8
 * MOSI -> D9
 * Res -> Reset
 * CS -> D6
 * DC -> D7
 */

#include "U8glib.h"

const int clkPin = 8;
const int mosiPin = 9;
const int csPin = 6;
const int dcPin = 7;
U8GLIB_SH1106_128X64 u8g(clkPin, mosiPin, csPin, dcPin);

uint8_t draw_state = 0;

void setup(void) {
  u8g.setRot180(); // flip screen, if required
}

void loop(void) {
  
  // picture loop  
  u8g.firstPage();  
  do {
    draw();
  } while(u8g.nextPage());
  
  // Increase the state. We will iterate over 9 demos for 8 counts each.
  draw_state++;
  if (draw_state >= 9*8) draw_state = 0;
  
  delay(150);
}

void draw(void) {
  u8g_prepare();
  switch(draw_state >> 3) {
    case 0: u8g_box_frame(draw_state&7); break;
    case 1: u8g_disc_circle(draw_state&7); break;
    case 2: u8g_r_frame(draw_state&7); break;
    case 3: u8g_string(draw_state&7); break;
    case 4: u8g_line(draw_state&7); break;
    case 5: u8g_triangle(draw_state&7); break;
    case 6: u8g_ascii_1(); break;
    case 7: u8g_ascii_2(); break;
    case 8: u8g_extra_page(draw_state&7); break;
  }
}

void u8g_prepare(void) {
  u8g.setFont(u8g_font_6x10);
  u8g.setFontRefHeightExtendedText();
  u8g.setDefaultForegroundColor();
  u8g.setFontPosTop();
}

void u8g_box_frame(uint8_t a) {
  u8g.drawStr(0, 0, "drawBox");
  u8g.drawBox(5, 10, 20, 10);
  u8g.drawBox(10 + a, 15, 30, 7);
  u8g.drawStr(0, 30, "drawFrame");
  u8g.drawFrame(5, 10 + 30, 20, 10);
  u8g.drawFrame(10 + a, 15 + 30, 30, 7);
}

void u8g_disc_circle(uint8_t a) {
  u8g.drawStr(0, 0, "drawDisc");
  u8g.drawDisc(10, 18, 9);
  u8g.drawDisc(24 + a, 16, 7);
  u8g.drawStr(0, 30, "drawCircle");
  u8g.drawCircle(10, 18 + 30, 9);
  u8g.drawCircle(24 + a, 16 + 30, 7);
}

void u8g_r_frame(uint8_t a) {
  u8g.drawStr(0, 0, "drawRFrame/Box");
  u8g.drawRFrame(5, 10, 40, 30, a + 1);
  u8g.drawRBox(50, 10, 25, 40, a + 1);
}

void u8g_string(uint8_t a) {
  u8g.drawStr(30 + a, 31, " 0");
  u8g.drawStr90(30, 31 + a, " 90");
  u8g.drawStr180(30 - a, 31, " 180");
  u8g.drawStr270(30, 31 - a, " 270");
}

void u8g_line(uint8_t a) {
  u8g.drawStr(0, 0, "drawLine");
  u8g.drawLine(7 + a, 10, 40, 55);
  u8g.drawLine(7 + a*2, 10, 60, 55);
  u8g.drawLine(7 + a*3, 10, 80, 55);
  u8g.drawLine(7 + a*4, 10, 100, 55);
}

void u8g_triangle(uint8_t a) {
  uint16_t offset = a;
  u8g.drawStr(0, 0, "drawTriangle");
  u8g.drawTriangle(14, 7, 45,30, 10,40);
  u8g.drawTriangle(14 + offset, 7 - offset, 45 + offset, 30 - offset, 57 + offset, 10 - offset);
  u8g.drawTriangle(57 + offset*2, 10, 45 + offset*2, 30, 86 + offset*2, 53);
  u8g.drawTriangle(10 + offset, 40 + offset, 45 + offset, 30 + offset, 86 + offset, 53 + offset);
}

void u8g_ascii_1() {
  char s[2] = " ";
  uint8_t x, y;
  u8g.drawStr(0, 0, "ASCII page 1");
  for(y = 0; y < 6; y++) {
    for(x = 0; x < 16; x++) {
      s[0] = y*16 + x + 32;
      u8g.drawStr(x*7, y*10 + 10, s);
    }
  }
}

void u8g_ascii_2() {
  char s[2] = " ";
  uint8_t x, y;
  u8g.drawStr(0, 0, "ASCII page 2");
  for(y = 0; y < 6; y++ ) {
    for(x = 0; x < 16; x++ ) {
      s[0] = y*16 + x + 160;
      u8g.drawStr(x*7, y*10 + 10, s);
    }
  }
}

void u8g_extra_page(uint8_t a) {
  u8g.drawStr(0, 12, "setScale1x1");
  u8g.setScale2x2();
  u8g.drawStr(0, 6 + a, "setScale2x2");
  u8g.undoScale();
}
