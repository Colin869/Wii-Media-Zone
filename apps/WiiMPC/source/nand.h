#ifndef NAND_H
#define NAND_H

#include <gccore.h>

// Mii data structure (74 bytes)
typedef struct {
    u8 name[20];
    u8 creator[20];
    u8 month;
    u8 day;
    u8 favorite_color;
    u8 favorite_mii;
    u8 gender;
    u8 birthday_month;
    u8 birthday_day;
    u8 height;
    u8 build;
    u8 face_shape;
    u8 face_color;
    u8 hair_style;
    u8 hair_color;
    u8 eye_style;
    u8 eye_color;
    u8 eye_scale;
    u8 eye_rotation;
    u8 eye_x;
    u8 eye_y;
    u8 eyebrow_style;
    u8 eyebrow_color;
    u8 eyebrow_scale;
    u8 eyebrow_rotation;
    u8 eyebrow_x;
    u8 eyebrow_y;
    u8 nose_style;
    u8 nose_scale;
    u8 nose_y;
    u8 mouth_style;
    u8 mouth_color;
    u8 mouth_scale;
    u8 mouth_y;
    u8 mustache_style;
    u8 beard_style;
    u8 beard_color;
    u8 beard_scale;
    u8 beard_y;
    u8 glasses_style;
    u8 glasses_color;
    u8 glasses_scale;
    u8 glasses_y;
    u8 mole_enabled;
    u8 mole_scale;
    u8 mole_x;
    u8 mole_y;
    u8 shirt_color;
    u8 pants_color;  // This is what we modify
    u8 shoes_color;
    u8 hat_style;
    u8 hat_color;
    u8 hat_scale;
    u8 hat_y;
    u8 misc1;
    u8 misc2;
    u8 misc3;
    u8 misc4;
    u8 misc5;
    u8 misc6;
    u8 misc7;
    u8 misc8;
    u8 misc9;
    u8 misc10;
    u8 misc11;
    u8 misc12;
    u8 misc13;
    u8 misc14;
    u8 misc15;
    u8 misc16;
    u8 misc17;
    u8 misc18;
    u8 misc19;
    u8 misc20;
    u8 misc21;
    u8 misc22;
    u8 misc23;
    u8 misc24;
    u8 misc25;
    u8 misc26;
    u8 misc27;
    u8 misc28;
    u8 misc29;
    u8 misc30;
    u8 misc31;
    u8 misc32;
    u8 misc33;
    u8 misc34;
    u8 misc35;
    u8 misc36;
    u8 misc37;
    u8 misc38;
    u8 misc39;
    u8 misc40;
    u8 misc41;
    u8 misc42;
    u8 misc43;
    u8 misc44;
    u8 misc45;
    u8 misc46;
    u8 misc47;
    u8 misc48;
    u8 misc49;
    u8 misc50;
    u8 misc51;
    u8 misc52;
    u8 misc53;
    u8 misc54;
    u8 misc55;
    u8 misc56;
    u8 misc57;
    u8 misc58;
    u8 misc59;
    u8 misc60;
    u8 misc61;
    u8 misc62;
    u8 misc63;
    u8 misc64;
    u8 misc65;
    u8 misc66;
    u8 misc67;
    u8 misc68;
    u8 misc69;
    u8 misc70;
    u8 misc71;
    u8 misc72;
    u8 misc73;
    u8 misc74;
} MiiDataRaw;

// Function prototypes

// NAND initialization and cleanup
bool InitializeNAND();
void CleanupNAND();

// Mii data operations
bool LoadMiiData();
bool SaveMiiData();
bool BackupMiiData();
bool RestoreMiiData();

// Mii data access
int GetMiiCount();
MiiDataRaw* GetMiiData();

// Mii modification
bool SetMiiPantsColor(int miiIndex, int colorIndex);

// Data validation
bool ValidateMiiData(MiiDataRaw* mii);
void UpdateMiiChecksum(MiiDataRaw* mii);

#endif // NAND_H
