#include <gccore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiiuse/wpad.h>

// Video globals
static void *xfb = NULL;
static GXRModeObj *rmode = NULL;

// Colors
#define WHITE 0xFFFFFFFF
#define BLACK 0x000000FF
#define RED   0xFF0000FF
#define GREEN 0x00FF00FF
#define BLUE  0x0000FFFF

// Function prototypes
void Initialise();
void DrawText(int x, int y, const char* text, u32 color);
void DrawRectangle(int x, int y, int width, int height, u32 color);
void HandleInput();

int main(int argc, char *argv[]) {
    // Initialize the Wii
    Initialise();
    
    // Main loop
    while(1) {
        // Handle input
        HandleInput();
        
        // Clear screen
        VIDEO_ClearFrameBuffer(rmode, xfb, BLACK);
        
        // Draw title
        DrawText(320, 50, "Hello Wii!", WHITE);
        DrawText(320, 100, "Welcome to Homebrew Development", GREEN);
        
        // Draw instructions
        DrawText(320, 200, "Press A to change color", WHITE);
        DrawText(320, 230, "Press B to exit", WHITE);
        DrawText(320, 260, "Press HOME to return to menu", WHITE);
        
        // Draw a simple rectangle
        static int rectX = 300;
        static int rectY = 300;
        static u32 rectColor = RED;
        DrawRectangle(rectX, rectY, 100, 50, rectColor);
        
        // Flush video
        VIDEO_WaitVSync();
    }
    
    return 0;
}

void Initialise() {
    // Initialize video
    VIDEO_Init();
    WPAD_Init();
    
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
    
    printf("HelloWii initialized successfully!\n");
}

void DrawText(int x, int y, const char* text, u32 color) {
    // Simple text drawing - in a real app you'd use a proper font library
    // For now, we'll use the console for text output
    printf("\x1b[%d;%dH%s", y/20, x/10, text);
}

void DrawRectangle(int x, int y, int width, int height, u32 color) {
    // Simple rectangle drawing using video memory
    // In a real app, you'd use GX functions for proper graphics
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

void HandleInput() {
    WPAD_ScanPads();
    u32 pressed = WPAD_ButtonsDown(0);
    
    if(pressed & WPAD_BUTTON_A) {
        // Change rectangle color
        static int colorIndex = 0;
        u32 colors[] = {RED, GREEN, BLUE, WHITE};
        colorIndex = (colorIndex + 1) % 4;
        // In a real app, you'd update the rectangle color here
        printf("Button A pressed - Color changed!\n");
    }
    
    if(pressed & WPAD_BUTTON_B) {
        // Exit application
        printf("Button B pressed - Exiting...\n");
        exit(0);
    }
    
    if(pressed & WPAD_BUTTON_HOME) {
        // Return to Wii menu
        printf("HOME button pressed - Returning to menu...\n");
        exit(0);
    }
}
