#include <gccore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiiuse/wpad.h>
#include <fat.h>
#include <sys/dir.h>
#include <wchar.h>
#include <locale.h>
#include "nand.h"

// Video globals
static void *xfb = NULL;
static GXRModeObj *rmode = NULL;

// Colors
#define WHITE 0xFFFFFFFF
#define BLACK 0x000000FF
#define RED   0xFF0000FF
#define GREEN 0x00FF00FF
#define BLUE  0x0000FFFF
#define YELLOW 0xFFFF00FF
#define CYAN  0x00FFFFFF
#define MAGENTA 0xFF00FFFF
#define GRAY  0x808080FF
#define ORANGE 0xFF8000FF
#define PURPLE 0x8000FFFF
#define PINK  0xFF80FFFF
#define BROWN 0x804000FF
#define LIME  0x80FF00FF
#define TEAL  0x008080FF
#define NAVY  0x000080FF
#define MAROON 0x800000FF
#define OLIVE 0x808000FF

// Mii structure
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
    u8 pants_color;  // This is what we'll be changing
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
    u8 misc75;
    u8 misc76;
    u8 misc77;
    u8 misc78;
    u8 misc79;
    u8 misc80;
    u8 misc81;
    u8 misc82;
    u8 misc83;
    u8 misc84;
    u8 misc85;
    u8 misc86;
    u8 misc87;
    u8 misc88;
    u8 misc89;
    u8 misc90;
    u8 misc91;
    u8 misc92;
    u8 misc93;
    u8 misc94;
    u8 misc95;
    u8 misc96;
    u8 misc97;
    u8 misc98;
    u8 misc99;
    u8 misc100;
} MiiData;

// Application state
typedef enum {
    STATE_MENU,
    STATE_MII_SELECT,
    STATE_COLOR_SELECT,
    STATE_PREVIEW,
    STATE_SAVE,
    STATE_SUCCESS
} AppState;

// Global variables
AppState currentState = STATE_MENU;
int selectedMii = 0;
int selectedColor = 0;
int miiCount = 0;
MiiDataRaw* miis = NULL;
MiiDataRaw originalMii;
bool isJapaneseWii = false;

// Available pants colors
const char* colorNames[] = {
    "Red", "Orange", "Yellow", "Lime", "Green", "Teal", "Cyan", "Blue",
    "Navy", "Purple", "Magenta", "Pink", "Brown", "Maroon", "Olive", "Gray"
};

const u32 colorValues[] = {
    RED, ORANGE, YELLOW, LIME, GREEN, TEAL, CYAN, BLUE,
    NAVY, PURPLE, MAGENTA, PINK, BROWN, MAROON, OLIVE, GRAY
};

// Function prototypes
void Initialise();
void DrawText(int x, int y, const char* text, u32 color);
void DrawRectangle(int x, int y, int width, int height, u32 color);
void DrawCircle(int x, int y, int radius, u32 color);
void HandleInput();
void DrawMenu();
void DrawMiiSelect();
void DrawColorSelect();
void DrawPreview();
void DrawSave();
void DrawSuccess();
void LoadMiis();
void SaveMii(int index);
void ApplyColorToMii(int miiIndex, int colorIndex);
void DrawMiiPreview(int x, int y, MiiData* mii, int scale);

int main(int argc, char *argv[]) {
    // Initialize the Wii
    Initialise();
    
    // Load Mii data
    LoadMiis();
    
    // Main loop
    while(1) {
        // Handle input
        HandleInput();
        
        // Clear screen
        VIDEO_ClearFrameBuffer(rmode, xfb, BLACK);
        
        // Draw current state
        switch(currentState) {
            case STATE_MENU:
                DrawMenu();
                break;
            case STATE_MII_SELECT:
                DrawMiiSelect();
                break;
            case STATE_COLOR_SELECT:
                DrawColorSelect();
                break;
            case STATE_PREVIEW:
                DrawPreview();
                break;
            case STATE_SAVE:
                DrawSave();
                break;
            case STATE_SUCCESS:
                DrawSuccess();
                break;
        }
        
        // Flush video
        VIDEO_WaitVSync();
    }
    
    // Cleanup (this won't be reached in normal operation)
    CleanupNAND();
    return 0;
}

void Initialise() {
    // Initialize video
    VIDEO_Init();
    WPAD_Init();
    
    // Initialize FAT filesystem
    fatInitDefault();
    
    // Detect Japanese Wii
    u32 region = CONF_GetRegion();
    isJapaneseWii = (region == CONF_REGION_JPN);
    
    // Set locale for Japanese text support
    if(isJapaneseWii) {
        setlocale(LC_ALL, "ja_JP.UTF-8");
    }
    
    // Get the preferred video mode
    rmode = VIDEO_GetPreferredMode(NULL);
    
    // Allocate memory for the frame buffer
    xfb = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));
    
    // Initialize the console
    console_init(xfb, 20, 20, rmode->fbWidth, rmode->xfbHeight, rmode->fbWidth * VI_DISPLAY_PIX_SZ);
    
    // Set up the video registers with the chosen mode
    VIDEO_Configure(rmode);
    
    // Tell the video hardware where our display memory is
    VIDEO_SetNextFramebuffer(xfb);
    
    // Make the display visible
    VIDEO_SetBlack(FALSE);
    
    // Flush the video register changes to the hardware
    VIDEO_Flush();
    
    // Wait for Video setup to complete
    VIDEO_WaitVSync();
    if(rmode->viTVMode & VI_NON_INTERLACE) VIDEO_WaitVSync();
    
    if(isJapaneseWii) {
        printf("WiiMPCが初期化されました！\n");
    } else {
        printf("WiiMPC initialized successfully!\n");
    }
}

void DrawText(int x, int y, const char* text, u32 color) {
    // Simple text drawing function
    // In a real implementation, you'd use a proper font rendering system
    printf("\x1b[%d;%dH%s", y/20, x/10, text);
}

void DrawRectangle(int x, int y, int width, int height, u32 color) {
    // Simple rectangle drawing
    // In a real implementation, you'd use GX functions
    printf("\x1b[%d;%dH", y/20, x/10);
    for(int i = 0; i < height/20; i++) {
        for(int j = 0; j < width/10; j++) {
            printf("█");
        }
        printf("\n");
    }
}

void DrawCircle(int x, int y, int radius, u32 color) {
    // Simple circle drawing
    // In a real implementation, you'd use GX functions
    printf("\x1b[%d;%dH●", y/20, x/10);
}

void LoadMiis() {
    // Load Mii data from NAND using the NAND module
    printf("Loading Miis from NAND...\n");
    
    if(LoadMiiData()) {
        miis = GetMiiData();
        miiCount = GetMiiCount();
        printf("Successfully loaded %d Miis from NAND\n", miiCount);
    } else {
        printf("Failed to load Miis from NAND, using dummy data\n");
        
        // Fallback to dummy data
        miiCount = 3;
        miis = malloc(miiCount * sizeof(MiiDataRaw));
        
        for(int i = 0; i < miiCount; i++) {
            sprintf((char*)miis[i].name, "Mii %d", i + 1);
            miis[i].pants_color = i % 8; // Different default colors
            miis[i].shirt_color = (i + 2) % 8;
            miis[i].shoes_color = (i + 4) % 8;
        }
    }
}

void SaveMii(int index) {
    // Save modified Mii data back to NAND using the NAND module
    printf("Saving Mii %d to NAND...\n", index + 1);
    
    if(SaveMiiData()) {
        printf("Mii data saved successfully to NAND!\n");
    } else {
        printf("Failed to save Mii data to NAND\n");
    }
}

void ApplyColorToMii(int miiIndex, int colorIndex) {
    if(SetMiiPantsColor(miiIndex, colorIndex)) {
        printf("Successfully applied color %d to Mii %d\n", colorIndex, miiIndex);
    } else {
        printf("Failed to apply color to Mii\n");
    }
}

void DrawMiiPreview(int x, int y, MiiDataRaw* mii, int scale) {
    // Draw a simple Mii preview
    // In a real implementation, you'd render the actual Mii model
    
    // Draw head
    DrawCircle(x + 50, y + 30, 20, WHITE);
    
    // Draw body
    DrawRectangle(x + 35, y + 50, 30, 40, WHITE);
    
    // Draw pants with selected color
    u32 pantsColor = colorValues[mii->pants_color];
    DrawRectangle(x + 35, y + 90, 30, 20, pantsColor);
    
    // Draw name
    char name[21];
    strncpy(name, (char*)mii->name, 20);
    name[20] = '\0';
    DrawText(x + 20, y + 120, name, WHITE);
}

void DrawMenu() {
    if(isJapaneseWii) {
        DrawText(320, 30, "WiiMPC", WHITE);
        DrawText(320, 60, "========================", WHITE);
        DrawText(320, 120, "Miiを選択", WHITE);
        DrawText(320, 150, "終了", WHITE);
        DrawText(320, 350, "D-Padで移動、Aで選択", GRAY);
        DrawText(320, 380, "HOMEでWiiメニューに戻る", GRAY);
    } else {
        DrawText(320, 30, "WiiMPC", WHITE);
        DrawText(320, 60, "========================", WHITE);
        DrawText(320, 120, "Select Mii", WHITE);
        DrawText(320, 150, "Exit", WHITE);
        DrawText(320, 350, "Use D-Pad to navigate, A to select", GRAY);
        DrawText(320, 380, "HOME to return to Wii menu", GRAY);
    }
}

void DrawMiiSelect() {
    if(isJapaneseWii) {
        DrawText(320, 30, "Miiを選択してください", WHITE);
        DrawText(320, 60, "========================", WHITE);
    } else {
        DrawText(320, 30, "Select a Mii", WHITE);
        DrawText(320, 60, "========================", WHITE);
    }
    
    // Draw Mii list
    for(int i = 0; i < miiCount && i < 10; i++) {
        int y = 100 + i * 25;
        u32 color = (i == selectedMii) ? YELLOW : WHITE;
        
        char miiName[50];
        sprintf(miiName, "%d. %s", i + 1, miis[i].name);
        DrawText(320, y, miiName, color);
        
        // Draw current pants color
        char colorName[20];
        sprintf(colorName, "(%s)", colorNames[miis[i].pants_color]);
        DrawText(450, y, colorName, colorValues[miis[i].pants_color]);
    }
    
    if(isJapaneseWii) {
        DrawText(320, 350, "D-Padで移動、Aで選択、Bで戻る", GRAY);
    } else {
        DrawText(320, 350, "D-Pad to move, A to select, B to go back", GRAY);
    }
}

void DrawColorSelect() {
    if(isJapaneseWii) {
        DrawText(320, 30, "パンツの色を選択してください", WHITE);
        DrawText(320, 60, "========================", WHITE);
    } else {
        DrawText(320, 30, "Select Pants Color", WHITE);
        DrawText(320, 60, "========================", WHITE);
    }
    
    // Draw color grid
    for(int i = 0; i < 16; i++) {
        int row = i / 4;
        int col = i % 4;
        int x = 200 + col * 80;
        int y = 120 + row * 60;
        
        u32 color = (i == selectedColor) ? YELLOW : WHITE;
        
        // Draw color swatch
        DrawRectangle(x, y, 60, 40, colorValues[i]);
        DrawText(x + 30, y + 50, colorNames[i], color);
    }
    
    if(isJapaneseWii) {
        DrawText(320, 350, "D-Padで移動、Aで選択、Bで戻る", GRAY);
    } else {
        DrawText(320, 350, "D-Pad to move, A to select, B to go back", GRAY);
    }
}

void DrawPreview() {
    if(isJapaneseWii) {
        DrawText(320, 30, "プレビュー", WHITE);
        DrawText(320, 60, "========================", WHITE);
    } else {
        DrawText(320, 30, "Preview", WHITE);
        DrawText(320, 60, "========================", WHITE);
    }
    
    // Draw original Mii
    DrawText(200, 100, "Original", WHITE);
    DrawMiiPreview(150, 120, &originalMii, 1);
    
    // Draw modified Mii
    DrawText(500, 100, "Modified", WHITE);
    DrawMiiPreview(450, 120, &miis[selectedMii], 1);
    
    if(isJapaneseWii) {
        DrawText(320, 350, "Aで保存、Bで戻る", GRAY);
    } else {
        DrawText(320, 350, "A to save, B to go back", GRAY);
    }
}

void DrawSave() {
    if(isJapaneseWii) {
        DrawText(320, 30, "保存中...", WHITE);
        DrawText(320, 60, "========================", WHITE);
        DrawText(320, 200, "Miiデータを保存しています", WHITE);
        DrawText(320, 230, "しばらくお待ちください", WHITE);
    } else {
        DrawText(320, 30, "Saving...", WHITE);
        DrawText(320, 60, "========================", WHITE);
        DrawText(320, 200, "Saving Mii data", WHITE);
        DrawText(320, 230, "Please wait...", WHITE);
    }
    
    // Show progress
    static int progress = 0;
    progress = (progress + 1) % 100;
    
    char progressText[50];
    sprintf(progressText, "Progress: %d%%", progress);
    DrawText(320, 280, progressText, GREEN);
}

void DrawSuccess() {
    if(isJapaneseWii) {
        DrawText(320, 30, "保存完了！", GREEN);
        DrawText(320, 60, "========================", WHITE);
        DrawText(320, 200, "Miiのパンツの色が変更されました", WHITE);
        DrawText(320, 230, "Wiiメニューで確認してください", WHITE);
    } else {
        DrawText(320, 30, "Save Complete!", GREEN);
        DrawText(320, 60, "========================", WHITE);
        DrawText(320, 200, "Mii pants color has been changed", WHITE);
        DrawText(320, 230, "Check in the Wii Menu", WHITE);
    }
    
    if(isJapaneseWii) {
        DrawText(320, 350, "Aで続ける、HOMEで終了", GRAY);
    } else {
        DrawText(320, 350, "A to continue, HOME to exit", GRAY);
    }
}

void HandleInput() {
    WPAD_ScanPads();
    u32 pressed = WPAD_ButtonsDown(0);
    
    switch(currentState) {
        case STATE_MENU:
            if(pressed & WPAD_BUTTON_UP) {
                // Navigate menu
            } else if(pressed & WPAD_BUTTON_DOWN) {
                // Navigate menu
            } else if(pressed & WPAD_BUTTON_A) {
                currentState = STATE_MII_SELECT;
            } else if(pressed & WPAD_BUTTON_HOME) {
                exit(0);
            }
            break;
            
        case STATE_MII_SELECT:
            if(pressed & WPAD_BUTTON_UP) {
                if(selectedMii > 0) selectedMii--;
            } else if(pressed & WPAD_BUTTON_DOWN) {
                if(selectedMii < miiCount - 1) selectedMii++;
            } else if(pressed & WPAD_BUTTON_A) {
                // Store original Mii data
                originalMii = miis[selectedMii];
                currentState = STATE_COLOR_SELECT;
            } else if(pressed & WPAD_BUTTON_B) {
                currentState = STATE_MENU;
            }
            break;
            
        case STATE_COLOR_SELECT:
            if(pressed & WPAD_BUTTON_UP) {
                if(selectedColor >= 4) selectedColor -= 4;
            } else if(pressed & WPAD_BUTTON_DOWN) {
                if(selectedColor < 12) selectedColor += 4;
            } else if(pressed & WPAD_BUTTON_LEFT) {
                if(selectedColor > 0) selectedColor--;
            } else if(pressed & WPAD_BUTTON_RIGHT) {
                if(selectedColor < 15) selectedColor++;
            } else if(pressed & WPAD_BUTTON_A) {
                ApplyColorToMii(selectedMii, selectedColor);
                currentState = STATE_PREVIEW;
            } else if(pressed & WPAD_BUTTON_B) {
                currentState = STATE_MII_SELECT;
            }
            break;
            
        case STATE_PREVIEW:
            if(pressed & WPAD_BUTTON_A) {
                currentState = STATE_SAVE;
            } else if(pressed & WPAD_BUTTON_B) {
                // Restore original color
                miis[selectedMii] = originalMii;
                currentState = STATE_COLOR_SELECT;
            }
            break;
            
        case STATE_SAVE:
            // Save the Mii
            SaveMii(selectedMii);
            currentState = STATE_SUCCESS;
            break;
            
        case STATE_SUCCESS:
            if(pressed & WPAD_BUTTON_A) {
                currentState = STATE_MENU;
            } else if(pressed & WPAD_BUTTON_HOME) {
                exit(0);
            }
            break;
    }
}
