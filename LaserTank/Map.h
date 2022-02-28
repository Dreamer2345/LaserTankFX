#pragma once

const bool UPPER = true;
const bool LOWER = false;
const uint8_t max_map_size = 0xff;
const uint8_t max_name_size = 20;


uint16_t map_values[max_map_size];
char mapName[max_name_size];

uint8_t getTopTile(uint8_t position){
  uint16_t block = map_values[position];
  return (uint8_t)((block & 0xff00) >> 8);  
}

uint8_t getLowerTile(uint8_t position){
  uint16_t block = map_values[position];
  return (uint8_t)(block & 0xff);  
}

void setTile(const uint8_t position,const uint8_t tile,const bool layer){
  if(layer){
    map_values[position] = ((map_values[position] & 0xff00) | tile);
  }
  else{
    map_values[position] = ((map_values[position] & 0xff) | ((uint16_t)tile << 8));
  }
}

inline void setUpperTile(const uint8_t position,const uint8_t tile){
  setTile(position,tile,UPPER);
}

inline void setLowerTile(const uint8_t position,const uint8_t tile){
  setTile(position,tile,LOWER);
}
