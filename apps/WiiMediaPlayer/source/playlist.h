#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <gccore.h>

// Playlist structures
typedef struct PlaylistItem {
    char name[256];
    char path[512];
    int isVideo;
    int duration;
    struct PlaylistItem* next;
} PlaylistItem;

typedef struct Playlist {
    char name[256];
    char filename[512];
    int itemCount;
    int currentIndex;
    PlaylistItem* head;
    PlaylistItem* current;
} Playlist;

// Function prototypes
Playlist* CreatePlaylist(const char* name);
void AddToPlaylist(Playlist* playlist, const char* name, const char* path, int isVideo);
void SavePlaylist(Playlist* playlist);
Playlist* LoadPlaylist(const char* filename);
void LoadM3UPlaylist(const char* filename);
void FreePlaylist(Playlist* playlist);
PlaylistItem* GetCurrentItem(Playlist* playlist);
PlaylistItem* GetNextItem(Playlist* playlist);
PlaylistItem* GetPreviousItem(Playlist* playlist);
void ShufflePlaylist(Playlist* playlist);
void SortPlaylistByName(Playlist* playlist);
void SortPlaylistByDuration(Playlist* playlist);
int GetPlaylistDuration(Playlist* playlist);
void CreateDefaultPlaylists();

// Global variables (extern declarations)
extern Playlist* currentPlaylist;
extern Playlist* playlists[10];
extern int playlistCount;

#endif // PLAYLIST_H
