#ifndef GBA_INPUT_H
#define GBA_INPUT_H

#include "../include/GBABase.h"
#include "../include/GBATypes.h"

#define REG_KEYINPUT        *(vu16*)(REG_BASE + 0x0130)
#define REG_KEYCNT          *(vu16*)(REG_BASE + 0x0132)
#define KEY_MASK            0x03FF

typedef enum KEYPAD_BITS
{
    key_A = 0, key_B,
    key_Right, key_Left, key_Up, key_Down,
    key_Shoulder_R, key_Shoulder_L,
    key_Select, key_Start
}KEYPAD_BITS;

//---Button Defines---

#define KEY_A  0x0001
#define KEY_B  0x0002
#define KEY_SL 0x0004
#define KEY_ST 0x0008
#define KEY_R  0x0010
#define KEY_L  0x0020
#define KEY_U  0x0040
#define KEY_D  0x0080
#define KEY_RB 0x0100
#define KEY_LB 0x0200

#define CURRENT_KEY_DOWN(key) (~(REG_KEYINPUT) &key)
#define CURRENT_KEY_UP(key) ((REG_KEYINPUT) &key)

extern u16 __current_key;
extern u16 __previous_key;

u32 GetKey(u32 key);
u32 GetKeyDown(u32 key);
u32 GetKeyDown(u32 key);

#endif