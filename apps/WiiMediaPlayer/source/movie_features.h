#ifndef MOVIE_FEATURES_H
#define MOVIE_FEATURES_H

#include <gccore.h>

// Movie feature structures
typedef struct {
    float brightness;
    float contrast;
    float saturation;
    float hue;
    float gamma;
    int sharpness;
    int noise_reduction;
    int deinterlace;
    int aspect_ratio; // 0=auto, 1=4:3, 2=16:9, 3=stretch
} VideoFilter;

typedef struct {
    int slow_motion;
    int fast_forward;
    float playback_speed;
    int frame_step;
    int reverse_playback;
    int loop_mode; // 0=none, 1=single, 2=all
    int auto_play;
    int remember_position;
} PlaybackSettings;

typedef struct {
    int x, y, width, height;
    int enabled;
    char text[256];
    int font_size;
    int color;
    int outline;
} SubtitleOverlay;

typedef struct {
    char name[256];
    int start_time;
    int end_time;
    char description[512];
} Bookmark;

// Function prototypes
void ApplyVideoFilter(VideoFilter* filter, void* frameBuffer, int width, int height);
void SetBrightness(float brightness);
void SetContrast(float contrast);
void SetSaturation(float saturation);
void SetHue(float hue);
void SetGamma(float gamma);
void SetSharpness(int level);
void EnableNoiseReduction(int enable);
void EnableDeinterlace(int enable);
void SetAspectRatio(int ratio);
void SetPlaybackSpeed(float speed);
void EnableSlowMotion(int enable);
void EnableFastForward(int enable);
void EnableReversePlayback(int enable);
void SetLoopMode(int mode);
void EnableAutoPlay(int enable);
void EnableRememberPosition(int enable);
void AddBookmark(const char* name, int time, const char* description);
void RemoveBookmark(int index);
void JumpToBookmark(int index);
void SaveBookmarks(const char* filename);
void LoadBookmarks(const char* filename);
void DrawSubtitle(const char* text, int x, int y, int color);
void EnableSubtitleOverlay(int enable);
void SetSubtitlePosition(int x, int y);
void SetSubtitleStyle(int font_size, int color, int outline);
void TakeScreenshot(const char* filename);
void CreateThumbnail(const char* videoFile, const char* thumbnailFile, int time);
void ExtractAudioTrack(const char* videoFile, const char* audioFile);
void MergeSubtitles(const char* videoFile, const char* subtitleFile, const char* outputFile);

// Advanced video effects
void ApplySepiaEffect(void* frameBuffer, int width, int height);
void ApplyGrayscaleEffect(void* frameBuffer, int width, int height);
void ApplyInvertEffect(void* frameBuffer, int width, int height);
void ApplyBlurEffect(void* frameBuffer, int width, int height, int radius);

// Global variables (extern declarations)
extern VideoFilter currentFilter;
extern PlaybackSettings playbackSettings;
extern SubtitleOverlay subtitleOverlay;
extern Bookmark bookmarks[50];
extern int bookmarkCount;
extern int currentBookmark;

#endif // MOVIE_FEATURES_H
