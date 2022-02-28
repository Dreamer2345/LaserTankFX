#pragma once

const uint8_t Max_Sliding_Objects = 16;
const uint8_t NO_SPACE = 0xff;
const uint8_t Active_Mask = 0x4;
const uint8_t Direction_Mask = 0x3;

struct TSlidingObject{
  uint8_t Position;
  uint8_t Data; //2 bits direction 1 bit active
};

TSlidingObject slidingObjects[Max_Sliding_Objects];


uint8_t contains_Position(uint8_t Position){
  for(uint8_t i=0; i<Max_Sliding_Objects;i++){
    if((slidingObjects[i].Data & Active_Mask)&&(slidingObjects[i].Position == Position))
      return i;
  }
  return NO_SPACE;  
}

uint8_t get_unused(){
  uint8_t i = NO_SPACE;
  for(i=0; i<Max_Sliding_Objects;i++){
    if(!(slidingObjects[i].Data & Active_Mask))
      break;
  }
  return i;
}

uint8_t add_sliding_object(uint8_t Position,uint8_t Direction){
  uint8_t index = get_unused();
  if(index != NO_SPACE){
    slidingObjects[index].Position = Position;
    slidingObjects[index].Data = (Direction & Direction_Mask) | (Active_Mask);   
  }
  return index;
}


void remove_sliding_object(uint8_t index){
  if(index != NO_SPACE){
    slidingObjects[index].Data = 0;   
  }
}

void update_sliding_object(uint8_t index,uint8_t Position,uint8_t Direction){
  slidingObjects[index].Position = Position;
  slidingObjects[index].Data = (Direction & Direction_Mask) | (Active_Mask);   
}
