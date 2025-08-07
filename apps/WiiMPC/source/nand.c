#include <gccore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fat.h>
#include "nand.h"

// NAND file paths for Mii data
#define MII_DATA_PATH "/title/00010002/484e4145/data/miidata.bin"
#define MII_BACKUP_PATH "sd:/mii_backup.bin"

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

// Global variables
MiiDataRaw* miiData = NULL;
int miiCount = 0;
bool nandInitialized = false;

// Function prototypes
bool InitializeNAND();
bool LoadMiiData();
bool SaveMiiData();
bool BackupMiiData();
bool RestoreMiiData();
bool ValidateMiiData(MiiDataRaw* mii);
void UpdateMiiChecksum(MiiDataRaw* mii);

bool InitializeNAND() {
    if(nandInitialized) return true;
    
    printf("Initializing NAND access...\n");
    
    // Initialize FAT filesystem for SD card access
    if(!fatInitDefault()) {
        printf("Failed to initialize FAT filesystem\n");
        return false;
    }
    
    // Initialize NAND filesystem
    if(ISFS_Initialize() < 0) {
        printf("Failed to initialize NAND filesystem\n");
        return false;
    }
    
    nandInitialized = true;
    printf("NAND access initialized successfully\n");
    return true;
}

bool LoadMiiData() {
    if(!nandInitialized) {
        if(!InitializeNAND()) return false;
    }
    
    printf("Loading Mii data from NAND...\n");
    
    // Open Mii data file
    s32 fd = ISFS_Open(MII_DATA_PATH, ISFS_OPEN_READ);
    if(fd < 0) {
        printf("Failed to open Mii data file: %d\n", fd);
        return false;
    }
    
    // Get file size
    fstats stats;
    if(ISFS_GetFileStats(fd, &stats) < 0) {
        printf("Failed to get file stats\n");
        ISFS_Close(fd);
        return false;
    }
    
    // Allocate memory for Mii data
    miiData = malloc(stats.file_length);
    if(!miiData) {
        printf("Failed to allocate memory for Mii data\n");
        ISFS_Close(fd);
        return false;
    }
    
    // Read Mii data
    s32 bytesRead = ISFS_Read(fd, miiData, stats.file_length);
    ISFS_Close(fd);
    
    if(bytesRead != stats.file_length) {
        printf("Failed to read Mii data: %d bytes read, %d expected\n", bytesRead, stats.file_length);
        free(miiData);
        miiData = NULL;
        return false;
    }
    
    // Calculate number of Miis (each Mii is 74 bytes)
    miiCount = stats.file_length / sizeof(MiiDataRaw);
    
    printf("Loaded %d Miis from NAND\n", miiCount);
    return true;
}

bool SaveMiiData() {
    if(!nandInitialized || !miiData) {
        printf("No Mii data loaded\n");
        return false;
    }
    
    printf("Saving Mii data to NAND...\n");
    
    // Create backup first
    if(!BackupMiiData()) {
        printf("Failed to create backup\n");
        return false;
    }
    
    // Open Mii data file for writing
    s32 fd = ISFS_Open(MII_DATA_PATH, ISFS_OPEN_WRITE);
    if(fd < 0) {
        printf("Failed to open Mii data file for writing: %d\n", fd);
        return false;
    }
    
    // Update checksums for all Miis
    for(int i = 0; i < miiCount; i++) {
        UpdateMiiChecksum(&miiData[i]);
    }
    
    // Write Mii data
    s32 bytesWritten = ISFS_Write(fd, miiData, miiCount * sizeof(MiiDataRaw));
    ISFS_Close(fd);
    
    if(bytesWritten != miiCount * sizeof(MiiDataRaw)) {
        printf("Failed to write Mii data: %d bytes written, %d expected\n", 
               bytesWritten, miiCount * sizeof(MiiDataRaw));
        return false;
    }
    
    printf("Mii data saved successfully\n");
    return true;
}

bool BackupMiiData() {
    if(!miiData) return false;
    
    printf("Creating backup of Mii data...\n");
    
    // Create backup file on SD card
    FILE* backupFile = fopen(MII_BACKUP_PATH, "wb");
    if(!backupFile) {
        printf("Failed to create backup file\n");
        return false;
    }
    
    // Write backup data
    size_t bytesWritten = fwrite(miiData, 1, miiCount * sizeof(MiiDataRaw), backupFile);
    fclose(backupFile);
    
    if(bytesWritten != miiCount * sizeof(MiiDataRaw)) {
        printf("Failed to write backup data\n");
        return false;
    }
    
    printf("Backup created successfully\n");
    return true;
}

bool RestoreMiiData() {
    printf("Restoring Mii data from backup...\n");
    
    // Open backup file
    FILE* backupFile = fopen(MII_BACKUP_PATH, "rb");
    if(!backupFile) {
        printf("Backup file not found\n");
        return false;
    }
    
    // Get file size
    fseek(backupFile, 0, SEEK_END);
    long fileSize = ftell(backupFile);
    fseek(backupFile, 0, SEEK_SET);
    
    // Allocate memory
    MiiDataRaw* backupData = malloc(fileSize);
    if(!backupData) {
        printf("Failed to allocate memory for backup data\n");
        fclose(backupFile);
        return false;
    }
    
    // Read backup data
    size_t bytesRead = fread(backupData, 1, fileSize, backupFile);
    fclose(backupFile);
    
    if(bytesRead != fileSize) {
        printf("Failed to read backup data\n");
        free(backupData);
        return false;
    }
    
    // Replace current data
    if(miiData) free(miiData);
    miiData = backupData;
    miiCount = fileSize / sizeof(MiiDataRaw);
    
    printf("Mii data restored from backup\n");
    return true;
}

bool ValidateMiiData(MiiDataRaw* mii) {
    if(!mii) return false;
    
    // Basic validation checks
    if(mii->pants_color > 15) return false;  // Invalid color
    if(mii->shirt_color > 15) return false;  // Invalid color
    if(mii->shoes_color > 15) return false;  // Invalid color
    
    // Check name length
    int nameLen = strlen((char*)mii->name);
    if(nameLen > 20) return false;
    
    return true;
}

void UpdateMiiChecksum(MiiDataRaw* mii) {
    // Simple checksum calculation
    // In a real implementation, you'd use the actual Wii checksum algorithm
    
    u8 checksum = 0;
    u8* data = (u8*)mii;
    
    // Calculate checksum for first 73 bytes (excluding checksum byte)
    for(int i = 0; i < 73; i++) {
        checksum ^= data[i];
    }
    
    // Store checksum in the last byte
    data[73] = checksum;
}

// Public interface functions
int GetMiiCount() {
    return miiCount;
}

MiiDataRaw* GetMiiData() {
    return miiData;
}

bool SetMiiPantsColor(int miiIndex, int colorIndex) {
    if(!miiData || miiIndex < 0 || miiIndex >= miiCount) {
        return false;
    }
    
    if(colorIndex < 0 || colorIndex > 15) {
        return false;
    }
    
    // Validate the Mii data
    if(!ValidateMiiData(&miiData[miiIndex])) {
        printf("Invalid Mii data for index %d\n", miiIndex);
        return false;
    }
    
    // Change the pants color
    miiData[miiIndex].pants_color = colorIndex;
    
    printf("Changed Mii %d pants color to %d\n", miiIndex, colorIndex);
    return true;
}

void CleanupNAND() {
    if(miiData) {
        free(miiData);
        miiData = NULL;
    }
    
    if(nandInitialized) {
        ISFS_Deinitialize();
        nandInitialized = false;
    }
    
    printf("NAND access cleaned up\n");
}
