#include <gccore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiiuse/wpad.h>
#include <fat.h>
#include <sys/dir.h>
#include <asndlib.h>
#include <wchar.h>
#include <locale.h>
#include "playlist.h"
#include "movie_features.h"

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
#define GRAY  0x808080FF

// Media player states
typedef enum {
    STATE_MENU,
    STATE_FILE_BROWSER,
    STATE_PLAYING_VIDEO,
    STATE_PLAYING_AUDIO,
    STATE_PLAYLIST,
    STATE_SETTINGS,
    STATE_BOOKMARKS,
    STATE_EFFECTS
} PlayerState;

// Media file structure
typedef struct {
    char name[256];
    char path[512];
    int isVideo;
    int duration; // in seconds
} MediaFile;

// Global variables
static PlayerState currentState = STATE_MENU;
static MediaFile currentFile;
static int isPlaying = 0;
static int currentTime = 0;
static int totalTime = 0;
static int volume = 50;
static int selectedItem = 0;
static int scrollOffset = 0;
static MediaFile* fileList = NULL;
static int fileCount = 0;
static char currentPath[512] = "sd:/";
static int currentEffect = 0;
static int currentBookmark = 0;
static int settingsPage = 0;
static int isJapaneseWii = 0;  // Japanese Wii detection

// Function prototypes
void Initialise();
void DrawText(int x, int y, const char* text, u32 color);
void DrawRectangle(int x, int y, int width, int height, u32 color);
void HandleInput();
void DrawMenu();
void DrawFileBrowser();
void DrawPlayer();
void DrawSettings();
void DrawBookmarks();
void DrawEffects();
void LoadFileList();
void PlayMedia(const char* path, int isVideo);
void StopMedia();
void UpdatePlayback();
void DrawProgressBar(int x, int y, int width, int height, float progress, u32 color);
void InitializePlaylists();

int main(int argc, char *argv[]) {
    // Initialize the Wii
    Initialise();
    
    // Initialize playlists
    InitializePlaylists();
    
    // Load initial file list
    LoadFileList();
    
    // Main loop
    while(1) {
        // Handle input
        HandleInput();
        
        // Clear screen
        VIDEO_ClearFrameBuffer(rmode, xfb, BLACK);
        
        // Draw based on current state
        switch(currentState) {
            case STATE_MENU:
                DrawMenu();
                break;
            case STATE_FILE_BROWSER:
                DrawFileBrowser();
                break;
            case STATE_PLAYING_VIDEO:
            case STATE_PLAYING_AUDIO:
                DrawPlayer();
                UpdatePlayback();
                break;
            case STATE_PLAYLIST:
                DrawFileBrowser(); // Reuse file browser for playlist
                break;
            case STATE_SETTINGS:
                DrawSettings();
                break;
            case STATE_BOOKMARKS:
                DrawBookmarks();
                break;
            case STATE_EFFECTS:
                DrawEffects();
                break;
        }
        
        // Flush video
        VIDEO_WaitVSync();
    }
    
    return 0;
}

void Initialise() {
    // Initialize video
    VIDEO_Init();
    WPAD_Init();
    
    // Initialize FAT filesystem
    fatInitDefault();
    
    // Initialize audio
    ASND_Init();
    
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
        printf("Wii Media Player が正常に初期化されました！\n");
    } else {
        printf("WiiMediaPlayer initialized successfully!\n");
    }
}

void DrawText(int x, int y, const char* text, u32 color) {
    // Simple text drawing using console positioning
    printf("\x1b[%d;%dH%s", y/20, x/10, text);
}

void DrawRectangle(int x, int y, int width, int height, u32 color) {
    // Simple rectangle drawing using video memory
    u32* fb = (u32*)xfb;
    int fbWidth = rmode->fbWidth;
    
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            int pixelX = x + j;
            int pixelY = y + i;
            if(pixelX >= 0 && pixelX < fbWidth && pixelY >= 0 && pixelY < rmode->xfbHeight) {
                fb[pixelY * fbWidth + pixelX] = color;
            }
        }
    }
}

void DrawProgressBar(int x, int y, int width, int height, float progress, u32 color) {
    // Draw background
    DrawRectangle(x, y, width, height, GRAY);
    
    // Draw progress
    int progressWidth = (int)(width * progress);
    if(progressWidth > 0) {
        DrawRectangle(x, y, progressWidth, height, color);
    }
}

void DrawMenu() {
    // Draw title
    if(isJapaneseWii) {
        DrawText(320, 30, "Wii メディアプレイヤー", WHITE);
        DrawText(320, 60, "=================", WHITE);
        
        // Draw menu options in Japanese
        DrawText(320, 120, "ファイルブラウザ", selectedItem == 0 ? YELLOW : WHITE);
        DrawText(320, 150, "プレイリスト", selectedItem == 1 ? YELLOW : WHITE);
        DrawText(320, 180, "設定", selectedItem == 2 ? YELLOW : WHITE);
        DrawText(320, 210, "ブックマーク", selectedItem == 3 ? YELLOW : WHITE);
        DrawText(320, 240, "ビデオエフェクト", selectedItem == 4 ? YELLOW : WHITE);
        DrawText(320, 270, "終了", selectedItem == 5 ? YELLOW : WHITE);
        
        // Draw instructions in Japanese
        DrawText(320, 350, "D-Padで移動、Aで選択", GRAY);
        DrawText(320, 380, "HOMEでWiiメニューに戻る", GRAY);
    } else {
        DrawText(320, 30, "Wii Media Player", WHITE);
        DrawText(320, 60, "=================", WHITE);
        
        // Draw menu options
        DrawText(320, 120, "File Browser", selectedItem == 0 ? YELLOW : WHITE);
        DrawText(320, 150, "Playlist", selectedItem == 1 ? YELLOW : WHITE);
        DrawText(320, 180, "Settings", selectedItem == 2 ? YELLOW : WHITE);
        DrawText(320, 210, "Bookmarks", selectedItem == 3 ? YELLOW : WHITE);
        DrawText(320, 240, "Video Effects", selectedItem == 4 ? YELLOW : WHITE);
        DrawText(320, 270, "Exit", selectedItem == 5 ? YELLOW : WHITE);
        
        // Draw instructions
        DrawText(320, 350, "Use D-Pad to navigate, A to select", GRAY);
        DrawText(320, 380, "HOME to return to Wii menu", GRAY);
    }
}

void DrawFileBrowser() {
    // Draw header
    DrawText(320, 20, "File Browser", WHITE);
    DrawText(320, 50, currentPath, GRAY);
    
    // Draw file list
    int startY = 80;
    int itemsPerPage = 15;
    int startIndex = scrollOffset;
    int endIndex = startIndex + itemsPerPage;
    
    if(endIndex > fileCount) endIndex = fileCount;
    
    for(int i = startIndex; i < endIndex; i++) {
        int y = startY + (i - startIndex) * 20;
        u32 color = (i == selectedItem) ? YELLOW : WHITE;
        
        if(fileList[i].isVideo) {
            DrawText(50, y, "[VIDEO]", GREEN);
        } else {
            DrawText(50, y, "[AUDIO]", BLUE);
        }
        
        DrawText(150, y, fileList[i].name, color);
    }
    
    // Draw scroll indicator
    if(scrollOffset > 0) {
        DrawText(320, 60, "^", WHITE);
    }
    if(endIndex < fileCount) {
        DrawText(320, 380, "v", WHITE);
    }
    
    // Draw instructions
    DrawText(320, 420, "A: Play  B: Back  D-Pad: Navigate  HOME: Exit", GRAY);
}

void DrawPlayer() {
    // Draw title
    DrawText(320, 30, currentFile.name, WHITE);
    
    // Draw media type indicator
    if(currentFile.isVideo) {
        DrawText(320, 60, "VIDEO PLAYER", GREEN);
    } else {
        DrawText(320, 60, "AUDIO PLAYER", BLUE);
    }
    
    // Draw progress bar
    float progress = (totalTime > 0) ? (float)currentTime / totalTime : 0.0f;
    DrawProgressBar(100, 150, 500, 20, progress, GREEN);
    
    // Draw time info
    char timeStr[64];
    sprintf(timeStr, "%02d:%02d / %02d:%02d", 
            currentTime / 60, currentTime % 60,
            totalTime / 60, totalTime % 60);
    DrawText(320, 180, timeStr, WHITE);
    
    // Draw volume
    sprintf(timeStr, "Volume: %d%%", volume);
    DrawText(320, 220, timeStr, WHITE);
    
    // Draw play/pause indicator
    DrawText(320, 260, isPlaying ? "PAUSED" : "PLAYING", isPlaying ? RED : GREEN);
    
    // Draw controls
    DrawText(320, 320, "A: Play/Pause  B: Stop  +/-: Volume  HOME: Exit", GRAY);
    DrawText(320, 350, "Left/Right: Seek  Up/Down: Volume", GRAY);
}

void LoadFileList() {
    // Free existing list
    if(fileList) {
        free(fileList);
        fileList = NULL;
    }
    
    fileCount = 0;
    
    // Open directory
    DIR_ITER* dir = diropen(currentPath);
    if(!dir) return;
    
    // Count files
    char filename[256];
    struct stat st;
    while(dirnext(dir, filename, &st) == 0) {
        if(!(st.st_mode & S_IFDIR)) { // Not a directory
            char* ext = strrchr(filename, '.');
            if(ext) {
                ext++; // Skip the dot
                if(strcasecmp(ext, "mp4") == 0 || strcasecmp(ext, "avi") == 0 ||
                   strcasecmp(ext, "mkv") == 0 || strcasecmp(ext, "mp3") == 0 ||
                   strcasecmp(ext, "wav") == 0 || strcasecmp(ext, "ogg") == 0) {
                    fileCount++;
                }
            }
        }
    }
    
    // Allocate memory
    if(fileCount > 0) {
        fileList = malloc(fileCount * sizeof(MediaFile));
        
        // Reset directory
        dirclose(dir);
        dir = diropen(currentPath);
        
        // Load files
        int index = 0;
        while(dirnext(dir, filename, &st) == 0 && index < fileCount) {
            if(!(st.st_mode & S_IFDIR)) {
                char* ext = strrchr(filename, '.');
                if(ext) {
                    ext++;
                    int isVideo = (strcasecmp(ext, "mp4") == 0 || 
                                  strcasecmp(ext, "avi") == 0 || 
                                  strcasecmp(ext, "mkv") == 0);
                    
                    if(isVideo || strcasecmp(ext, "mp3") == 0 || 
                       strcasecmp(ext, "wav") == 0 || strcasecmp(ext, "ogg") == 0) {
                        
                        strcpy(fileList[index].name, filename);
                        sprintf(fileList[index].path, "%s%s", currentPath, filename);
                        fileList[index].isVideo = isVideo;
                        fileList[index].duration = 0; // Would need to parse file for this
                        index++;
                    }
                }
            }
        }
    }
    
    dirclose(dir);
}

void PlayMedia(const char* path, int isVideo) {
    strcpy(currentFile.path, path);
    strcpy(currentFile.name, strrchr(path, '/') ? strrchr(path, '/') + 1 : path);
    currentFile.isVideo = isVideo;
    
    // Reset playback state
    currentTime = 0;
    totalTime = 300; // Default 5 minutes, would parse from file
    isPlaying = 1;
    
    if(isVideo) {
        currentState = STATE_PLAYING_VIDEO;
        printf("Starting video playback: %s\n", path);
        // Here you would initialize video decoder
    } else {
        currentState = STATE_PLAYING_AUDIO;
        printf("Starting audio playback: %s\n", path);
        // Here you would initialize audio decoder
    }
}

void StopMedia() {
    isPlaying = 0;
    currentTime = 0;
    printf("Media playback stopped\n");
    // Here you would stop decoders and free resources
}

void UpdatePlayback() {
    if(isPlaying && currentTime < totalTime) {
        currentTime++;
        // Here you would update actual media playback
    }
}

void HandleInput() {
    WPAD_ScanPads();
    u32 pressed = WPAD_ButtonsDown(0);
    u32 held = WPAD_ButtonsHeld(0);
    
    switch(currentState) {
        case STATE_MENU:
            if(pressed & WPAD_BUTTON_UP) {
                if(selectedItem > 0) selectedItem--;
            }
            if(pressed & WPAD_BUTTON_DOWN) {
                if(selectedItem < 5) selectedItem++;
            }
            if(pressed & WPAD_BUTTON_A) {
                switch(selectedItem) {
                    case 0: // File Browser
                        currentState = STATE_FILE_BROWSER;
                        selectedItem = 0;
                        LoadFileList();
                        break;
                    case 1: // Playlist
                        currentState = STATE_PLAYLIST;
                        selectedItem = 0;
                        LoadFileList();
                        break;
                    case 2: // Settings
                        currentState = STATE_SETTINGS;
                        selectedItem = 0;
                        settingsPage = 0;
                        break;
                    case 3: // Bookmarks
                        currentState = STATE_BOOKMARKS;
                        selectedItem = 0;
                        scrollOffset = 0;
                        break;
                    case 4: // Video Effects
                        currentState = STATE_EFFECTS;
                        selectedItem = 0;
                        break;
                    case 5: // Exit
                        exit(0);
                        break;
                }
            }
            break;
            
        case STATE_FILE_BROWSER:
        case STATE_PLAYLIST:
            if(pressed & WPAD_BUTTON_UP) {
                if(selectedItem > 0) {
                    selectedItem--;
                    if(selectedItem < scrollOffset) {
                        scrollOffset = selectedItem;
                    }
                }
            }
            if(pressed & WPAD_BUTTON_DOWN) {
                if(selectedItem < fileCount - 1) {
                    selectedItem++;
                    if(selectedItem >= scrollOffset + 15) {
                        scrollOffset = selectedItem - 14;
                    }
                }
            }
            if(pressed & WPAD_BUTTON_A) {
                if(selectedItem < fileCount) {
                    PlayMedia(fileList[selectedItem].path, fileList[selectedItem].isVideo);
                }
            }
            if(pressed & WPAD_BUTTON_B) {
                currentState = STATE_MENU;
                selectedItem = 0;
            }
            break;
            
        case STATE_SETTINGS:
            if(pressed & WPAD_BUTTON_UP) {
                if(selectedItem > 0) selectedItem--;
            }
            if(pressed & WPAD_BUTTON_DOWN) {
                if(selectedItem < 3) selectedItem++;
            }
            if(pressed & WPAD_BUTTON_LEFT) {
                if(settingsPage > 0) {
                    settingsPage--;
                    selectedItem = 0;
                }
            }
            if(pressed & WPAD_BUTTON_RIGHT) {
                if(settingsPage < 2) {
                    settingsPage++;
                    selectedItem = 0;
                }
            }
            if(pressed & WPAD_BUTTON_A) {
                // Toggle settings based on page and selection
                switch(settingsPage) {
                    case 0: // Playback settings
                        switch(selectedItem) {
                            case 0: // Auto Play
                                playbackSettings.auto_play = !playbackSettings.auto_play;
                                break;
                            case 1: // Remember Position
                                playbackSettings.remember_position = !playbackSettings.remember_position;
                                break;
                            case 2: // Loop Mode
                                playbackSettings.loop_mode = (playbackSettings.loop_mode + 1) % 3;
                                break;
                            case 3: // Subtitle Overlay
                                EnableSubtitleOverlay(!subtitleOverlay.enabled);
                                break;
                        }
                        break;
                }
            }
            if(pressed & WPAD_BUTTON_B) {
                currentState = STATE_MENU;
                selectedItem = 2;
            }
            break;
            
        case STATE_BOOKMARKS:
            if(pressed & WPAD_BUTTON_UP) {
                if(selectedItem > 0) {
                    selectedItem--;
                    if(selectedItem < scrollOffset) {
                        scrollOffset = selectedItem;
                    }
                }
            }
            if(pressed & WPAD_BUTTON_DOWN) {
                if(selectedItem < bookmarkCount - 1) {
                    selectedItem++;
                    if(selectedItem >= scrollOffset + 10) {
                        scrollOffset = selectedItem - 9;
                    }
                }
            }
            if(pressed & WPAD_BUTTON_A) {
                if(selectedItem < bookmarkCount) {
                    JumpToBookmark(selectedItem);
                }
            }
            if(pressed & WPAD_BUTTON_1) {
                // Add bookmark at current time
                if(currentState == STATE_PLAYING_VIDEO || currentState == STATE_PLAYING_AUDIO) {
                    char name[256];
                    sprintf(name, "Bookmark %d", bookmarkCount + 1);
                    AddBookmark(name, currentTime, "Auto-generated bookmark");
                }
            }
            if(pressed & WPAD_BUTTON_2) {
                if(selectedItem < bookmarkCount) {
                    RemoveBookmark(selectedItem);
                }
            }
            if(pressed & WPAD_BUTTON_B) {
                currentState = STATE_MENU;
                selectedItem = 3;
            }
            break;
            
        case STATE_EFFECTS:
            if(pressed & WPAD_BUTTON_UP) {
                if(selectedItem > 0) selectedItem--;
            }
            if(pressed & WPAD_BUTTON_DOWN) {
                if(selectedItem < 8) selectedItem++;
            }
            if(pressed & WPAD_BUTTON_PLUS) {
                // Increase effect value
                switch(selectedItem) {
                    case 0: // Brightness
                        SetBrightness(currentFilter.brightness + 0.1f);
                        break;
                    case 1: // Contrast
                        SetContrast(currentFilter.contrast + 0.1f);
                        break;
                    case 2: // Saturation
                        SetSaturation(currentFilter.saturation + 0.1f);
                        break;
                    case 3: // Gamma
                        SetGamma(currentFilter.gamma + 0.1f);
                        break;
                    case 4: // Sharpness
                        SetSharpness(currentFilter.sharpness + 1);
                        break;
                }
            }
            if(pressed & WPAD_BUTTON_MINUS) {
                // Decrease effect value
                switch(selectedItem) {
                    case 0: // Brightness
                        SetBrightness(currentFilter.brightness - 0.1f);
                        break;
                    case 1: // Contrast
                        SetContrast(currentFilter.contrast - 0.1f);
                        break;
                    case 2: // Saturation
                        SetSaturation(currentFilter.saturation - 0.1f);
                        break;
                    case 3: // Gamma
                        SetGamma(currentFilter.gamma - 0.1f);
                        break;
                    case 4: // Sharpness
                        SetSharpness(currentFilter.sharpness - 1);
                        break;
                }
            }
            if(pressed & WPAD_BUTTON_A) {
                // Apply effect
                if(currentState == STATE_PLAYING_VIDEO) {
                    // Apply video filter to current frame
                    ApplyVideoFilter(&currentFilter, xfb, rmode->fbWidth, rmode->xfbHeight);
                }
            }
            if(pressed & WPAD_BUTTON_B) {
                currentState = STATE_MENU;
                selectedItem = 4;
            }
            break;
            
        case STATE_PLAYING_VIDEO:
        case STATE_PLAYING_AUDIO:
            if(pressed & WPAD_BUTTON_A) {
                isPlaying = !isPlaying;
            }
            if(pressed & WPAD_BUTTON_B) {
                StopMedia();
                currentState = STATE_MENU;
            }
            if(held & WPAD_BUTTON_LEFT) {
                if(currentTime > 10) currentTime -= 10;
            }
            if(held & WPAD_BUTTON_RIGHT) {
                if(currentTime < totalTime - 10) currentTime += 10;
            }
            if(pressed & WPAD_BUTTON_PLUS) {
                if(volume < 100) volume += 10;
            }
            if(pressed & WPAD_BUTTON_MINUS) {
                if(volume > 0) volume -= 10;
            }
            // Enhanced playback controls
            if(pressed & WPAD_BUTTON_1) {
                // Add bookmark
                char name[256];
                sprintf(name, "Bookmark %d", bookmarkCount + 1);
                AddBookmark(name, currentTime, "Auto-generated bookmark");
            }
            if(pressed & WPAD_BUTTON_2) {
                // Take screenshot
                char filename[256];
                sprintf(filename, "sd:/screenshots/screenshot_%d.png", (int)time(NULL));
                TakeScreenshot(filename);
            }
            if(pressed & WPAD_BUTTON_Z) {
                // Toggle slow motion
                EnableSlowMotion(!playbackSettings.slow_motion);
            }
            if(pressed & WPAD_BUTTON_C) {
                // Toggle fast forward
                EnableFastForward(!playbackSettings.fast_forward);
            }
            break;
    }
    
    if(pressed & WPAD_BUTTON_HOME) {
        StopMedia();
        exit(0);
    }
}

void DrawSettings() {
    // Draw title
    DrawText(320, 20, "Settings", WHITE);
    DrawText(320, 50, "=========", WHITE);
    
    // Draw settings options based on page
    switch(settingsPage) {
        case 0: // Playback settings
            DrawText(320, 100, "Playback Settings", YELLOW);
            DrawText(320, 130, "Auto Play", selectedItem == 0 ? GREEN : WHITE);
            DrawText(320, 160, "Remember Position", selectedItem == 1 ? GREEN : WHITE);
            DrawText(320, 190, "Loop Mode", selectedItem == 2 ? GREEN : WHITE);
            DrawText(320, 220, "Subtitle Overlay", selectedItem == 3 ? GREEN : WHITE);
            break;
        case 1: // Video settings
            DrawText(320, 100, "Video Settings", YELLOW);
            DrawText(320, 130, "Aspect Ratio", selectedItem == 0 ? GREEN : WHITE);
            DrawText(320, 160, "Deinterlace", selectedItem == 1 ? GREEN : WHITE);
            DrawText(320, 190, "Noise Reduction", selectedItem == 2 ? GREEN : WHITE);
            DrawText(320, 220, "Sharpness", selectedItem == 3 ? GREEN : WHITE);
            break;
        case 2: // Audio settings
            DrawText(320, 100, "Audio Settings", YELLOW);
            DrawText(320, 130, "Default Volume", selectedItem == 0 ? GREEN : WHITE);
            DrawText(320, 160, "Audio Sync", selectedItem == 1 ? GREEN : WHITE);
            DrawText(320, 190, "Equalizer", selectedItem == 2 ? GREEN : WHITE);
            break;
    }
    
    // Draw navigation
    DrawText(320, 300, "B: Back  Left/Right: Change Page", GRAY);
    DrawText(320, 330, "A: Toggle Setting  +/-: Adjust Value", GRAY);
}

void DrawBookmarks() {
    // Draw title
    DrawText(320, 20, "Bookmarks", WHITE);
    DrawText(320, 50, "=========", WHITE);
    
    if(bookmarkCount == 0) {
        DrawText(320, 150, "No bookmarks found", GRAY);
        DrawText(320, 180, "Create bookmarks while playing media", GRAY);
    } else {
        // Draw bookmark list
        int startY = 100;
        int itemsPerPage = 10;
        int startIndex = scrollOffset;
        int endIndex = startIndex + itemsPerPage;
        
        if(endIndex > bookmarkCount) endIndex = bookmarkCount;
        
        for(int i = startIndex; i < endIndex; i++) {
            int y = startY + (i - startIndex) * 25;
            u32 color = (i == selectedItem) ? YELLOW : WHITE;
            
            char timeStr[32];
            sprintf(timeStr, "%02d:%02d", bookmarks[i].start_time / 60, bookmarks[i].start_time % 60);
            
            DrawText(50, y, timeStr, BLUE);
            DrawText(150, y, bookmarks[i].name, color);
        }
        
        // Draw scroll indicator
        if(scrollOffset > 0) {
            DrawText(320, 80, "^", WHITE);
        }
        if(endIndex < bookmarkCount) {
            DrawText(320, 350, "v", WHITE);
        }
    }
    
    // Draw instructions
    DrawText(320, 400, "A: Jump to bookmark  B: Back  D-Pad: Navigate", GRAY);
    DrawText(320, 430, "1: Add bookmark  2: Remove bookmark", GRAY);
}

void DrawEffects() {
    // Draw title
    DrawText(320, 20, "Video Effects", WHITE);
    DrawText(320, 50, "=============", WHITE);
    
    // Draw effect options
    DrawText(320, 100, "Brightness", selectedItem == 0 ? YELLOW : WHITE);
    DrawText(320, 130, "Contrast", selectedItem == 1 ? YELLOW : WHITE);
    DrawText(320, 160, "Saturation", selectedItem == 2 ? YELLOW : WHITE);
    DrawText(320, 190, "Gamma", selectedItem == 3 ? YELLOW : WHITE);
    DrawText(320, 220, "Sharpness", selectedItem == 4 ? YELLOW : WHITE);
    DrawText(320, 250, "Sepia Effect", selectedItem == 5 ? YELLOW : WHITE);
    DrawText(320, 280, "Grayscale", selectedItem == 6 ? YELLOW : WHITE);
    DrawText(320, 310, "Invert Colors", selectedItem == 7 ? YELLOW : WHITE);
    DrawText(320, 340, "Blur Effect", selectedItem == 8 ? YELLOW : WHITE);
    
    // Draw current effect values
    char valueStr[64];
    sprintf(valueStr, "Brightness: %.1f", currentFilter.brightness);
    DrawText(500, 100, valueStr, GRAY);
    sprintf(valueStr, "Contrast: %.1f", currentFilter.contrast);
    DrawText(500, 130, valueStr, GRAY);
    sprintf(valueStr, "Saturation: %.1f", currentFilter.saturation);
    DrawText(500, 160, valueStr, GRAY);
    sprintf(valueStr, "Gamma: %.1f", currentFilter.gamma);
    DrawText(500, 190, valueStr, GRAY);
    sprintf(valueStr, "Sharpness: %d", currentFilter.sharpness);
    DrawText(500, 220, valueStr, GRAY);
    
    // Draw instructions
    DrawText(320, 400, "A: Apply effect  B: Back  +/-: Adjust value", GRAY);
    DrawText(320, 430, "D-Pad: Navigate  HOME: Reset to default", GRAY);
}

void InitializePlaylists() {
    // Create default playlists directory
    mkdir("sd:/playlists", 0777);
    
    // Create default playlists
    CreateDefaultPlaylists();
    
    // Load existing playlists from SD card
    DIR_ITER* dir = diropen("sd:/playlists");
    if(dir) {
        char filename[256];
        struct stat st;
        while(dirnext(dir, filename, &st) == 0) {
            if(!(st.st_mode & S_IFDIR)) { // Not a directory
                char* ext = strrchr(filename, '.');
                if(ext && (strcasecmp(ext, ".m3u") == 0 || strcasecmp(ext, ".m3u8") == 0)) {
                    char fullPath[512];
                    sprintf(fullPath, "sd:/playlists/%s", filename);
                    LoadPlaylist(fullPath);
                }
            }
        }
        dirclose(dir);
    }
}
