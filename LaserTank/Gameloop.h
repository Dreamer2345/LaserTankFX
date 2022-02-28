#pragma once
#include "Utils.h"
#include "Tiles.h"

enum class GameState 
{
  MainMenu,LoadLevel,PlayerInput,SimulateLevel,
};

GameState gamestate = GameState::MainMenu;
const uint16_t maxLevelNumber = 10;
uint16_t g_level_number = 0;
uint16_t g_player_data = 0;

const uint8_t shown_width = 5;
const uint8_t shown_height = 5;

const uint8_t laser_Direction_Mask = 0b1100000000;
const uint8_t laser_Active_Mask = 0b10000000000;
uint16_t g_laser_data = 0;


void FireLaser(uint8_t x, uint8_t y, uint8_t d){
  if(g_laser_data & laser_Active_Mask) return;
  uint8_t packed = getPackedfromNibble(x,y);
  g_laser_data = 0;
  g_laser_data = (((uint16_t)d)<<8)|laser_Active_Mask;
  g_laser_data |= packed;
}

bool checkPosition(uint8_t x, uint8_t y){
  if((x > 15)||(y > 15)) return false;
  switch((TileType)getLowerTile(getPackedfromNibble(x,y))){
    case TileType::Empty: 
    case TileType::Floor: return true;
    case TileType::Solid_Block: 
    case TileType::Glass_Block: 
    case TileType::Breakable_Block:
    case TileType::Movable_Block: return false;
    case TileType::Movable_Block_Sunk: 
    case TileType::Water: 
    case TileType::Ice: 
    case TileType::Breakable_Ice: 
    case TileType::Conveyer_Belt_Up: 
    case TileType::Conveyer_Belt_Down: 
    case TileType::Conveyer_Belt_Left: 
    case TileType::Conveyer_Belt_Right: return true;
    case TileType::Mirror_Up_Left: 
    case TileType::Mirror_Up_Right: 
    case TileType::Mirror_Down_Left: 
    case TileType::Mirror_Down_Right: 
    case TileType::Mirror_Rotate_Clockwise_Up_Left: 
    case TileType::Mirror_Rotate_Clockwise_Up_Right:
    case TileType::Mirror_Rotate_Clockwise_Down_Left:
    case TileType::Mirror_Rotate_Clockwise_Down_Right:
    case TileType::Mirror_Rotate_Anticlockwise_Up_Left:
    case TileType::Mirror_Rotate_Anticlockwise_Up_Right:
    case TileType::Mirror_Rotate_Anticlockwise_Down_Left:
    case TileType::Mirror_Rotate_Anticlockwise_Down_Right:
    case TileType::Enemy_Up:
    case TileType::Enemy_Down:
    case TileType::Enemy_Left:
    case TileType::Enemy_Right:
    case TileType::Broken_Enemy_Up:
    case TileType::Broken_Enemy_Down:
    case TileType::Broken_Enemy_Left:
    case TileType::Broken_Enemy_Right: return false;
    case TileType::Teleporter_0:
    case TileType::Teleporter_1:
    case TileType::Teleporter_2:
    case TileType::Teleporter_3:
    case TileType::Teleporter_4:
    case TileType::Teleporter_5:
    case TileType::Teleporter_6:
    case TileType::Teleporter_7:
    case TileType::Teleporter_8:
    case TileType::Teleporter_9:
    case TileType::Teleporter_10:
    case TileType::Teleporter_11:
    case TileType::Teleporter_12:
    case TileType::Teleporter_13:
    case TileType::Teleporter_14:
    case TileType::Teleporter_15: return true;
    default: return false;
  }
}

bool checkLaserPosition(uint8_t x, uint8_t y){
  if((x > 15)||(y > 15)) return false;
  switch((TileType)getLowerTile(getPackedfromNibble(x,y))){
    case TileType::Empty: 
    case TileType::Floor: return true;
    case TileType::Solid_Block: return false;
    case TileType::Glass_Block:  
    case TileType::Breakable_Block:
    case TileType::Movable_Block: 
    case TileType::Movable_Block_Sunk: 
    case TileType::Water: 
    case TileType::Ice: 
    case TileType::Breakable_Ice: 
    case TileType::Conveyer_Belt_Up: 
    case TileType::Conveyer_Belt_Down: 
    case TileType::Conveyer_Belt_Left: 
    case TileType::Conveyer_Belt_Right: 
    case TileType::Mirror_Up_Left: 
    case TileType::Mirror_Up_Right: 
    case TileType::Mirror_Down_Left: 
    case TileType::Mirror_Down_Right: 
    case TileType::Mirror_Rotate_Clockwise_Up_Left: 
    case TileType::Mirror_Rotate_Clockwise_Up_Right:
    case TileType::Mirror_Rotate_Clockwise_Down_Left:
    case TileType::Mirror_Rotate_Clockwise_Down_Right:
    case TileType::Mirror_Rotate_Anticlockwise_Up_Left:
    case TileType::Mirror_Rotate_Anticlockwise_Up_Right:
    case TileType::Mirror_Rotate_Anticlockwise_Down_Left:
    case TileType::Mirror_Rotate_Anticlockwise_Down_Right:return true;
    case TileType::Enemy_Up:
    case TileType::Enemy_Down:
    case TileType::Enemy_Left:
    case TileType::Enemy_Right:
    case TileType::Broken_Enemy_Up:
    case TileType::Broken_Enemy_Down:
    case TileType::Broken_Enemy_Left:
    case TileType::Broken_Enemy_Right: return false;
    case TileType::Teleporter_0:
    case TileType::Teleporter_1:
    case TileType::Teleporter_2:
    case TileType::Teleporter_3:
    case TileType::Teleporter_4:
    case TileType::Teleporter_5:
    case TileType::Teleporter_6:
    case TileType::Teleporter_7:
    case TileType::Teleporter_8:
    case TileType::Teleporter_9:
    case TileType::Teleporter_10:
    case TileType::Teleporter_11:
    case TileType::Teleporter_12:
    case TileType::Teleporter_13:
    case TileType::Teleporter_14:
    case TileType::Teleporter_15: return true;
    default: return false;
  }
}

bool isAntitank(TileType a){
   switch(a){
    case Enemy_Up:
    case Enemy_Down:
    case Enemy_Left:
    case Enemy_Right: return true;
   }
   return false;
}

void UpdateAntitank(){
  uint8_t player_x;
  uint8_t player_y;
  uint8_t player_direction;
  uint8_t player_position;
  getBytesfromPacked(g_player_data,player_position,player_direction);
  getNibblesfromPacked(player_position,player_x,player_y);

  uint8_t x = player_x;
  uint8_t y = player_y;
  while(x < 15){
    if(getLowerTile(getPackedfromNibble(x,y)) == )
    x++;  
  }

  
}

void updateMainMenu(){
  arduboy.clear();
  arduboy.println("Temp Main Menu: press any button");
  arduboy.print("Level number:");
  arduboy.print(g_level_number);
  arduboy.display();

  if(arduboy.pressed(A_BUTTON) || arduboy.pressed(B_BUTTON)){
    gamestate = GameState::LoadLevel;
  }

  if(arduboy.justPressed(UP_BUTTON)){
    if(g_level_number < maxLevelNumber)
      g_level_number++;
  }
  if(arduboy.justPressed(DOWN_BUTTON)){
    if(g_level_number > 0)
      g_level_number--;
  }
}


void drawLevel(){
  uint8_t player_x;
  uint8_t player_y;
  uint8_t player_direction;
  uint8_t player_position;
  getBytesfromPacked(g_player_data,player_position,player_direction);
  getNibblesfromPacked(player_position,player_x,player_y);

  for(int i=-shown_width; i < shown_width; i++)
    for(int j=-shown_height; j < shown_height; j++){
      int8_t xvalue = i + player_x;
      int8_t yvalue = j + player_y;
    }
}

void loadLevel(){
  //TODO:
  //Load using the FX chip compressed data
  //header
  //map_name null terminated string (uint8_t) * 21
  //player_start (uint8_t)
  //compressed_map_data UPPER LAYER run length encoding for map (uint8_t size)(uint8_t tile)
  //compressed_map_data LOWER LAYER (uint8_t size)(uint8_t tile)
}


void updateGame(){
  arduboy.pollButtons();
  switch(gamestate){
    case GameState::MainMenu: updateMainMenu(); break;
    case GameState::LoadLevel: break;
    case GameState::PlayerInput: break;
    case GameState::SimulateLevel: break;
  }
}
