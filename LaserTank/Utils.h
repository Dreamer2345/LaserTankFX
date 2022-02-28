#pragma once

void getNibblesfromPacked(const uint8_t v,uint8_t& x,uint8_t& y){
  x = (v & 0xf0) >> 4;
  y = (v & 0xf);
}

uint8_t getPackedfromNibble(const uint8_t x, const uint8_t y){
  return ((x & 0xf) << 4) | (y & 0xf);
}

void getBytesfromPacked(const uint16_t v, uint8_t& x, uint8_t& y){
  x = (uint8_t)((v & 0xff00) >> 8);
  y = (uint8_t)(v & 0xff);
}

uint16_t getPackedfromBytes(const uint8_t x, const uint8_t y){
  return (((uint16_t)(x & 0xff)) << 8) | ((uint16_t)y & 0xff);
}
