#include <gccore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fat.h>

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

// Global playlists
static Playlist* currentPlaylist = NULL;
static Playlist* playlists[10];
static int playlistCount = 0;

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

Playlist* CreatePlaylist(const char* name) {
    Playlist* playlist = malloc(sizeof(Playlist));
    if(!playlist) return NULL;
    
    strcpy(playlist->name, name);
    sprintf(playlist->filename, "sd:/playlists/%s.m3u", name);
    playlist->itemCount = 0;
    playlist->currentIndex = 0;
    playlist->head = NULL;
    playlist->current = NULL;
    
    return playlist;
}

void AddToPlaylist(Playlist* playlist, const char* name, const char* path, int isVideo) {
    if(!playlist) return;
    
    PlaylistItem* item = malloc(sizeof(PlaylistItem));
    if(!item) return;
    
    strcpy(item->name, name);
    strcpy(item->path, path);
    item->isVideo = isVideo;
    item->duration = 0; // Will be updated when file is loaded
    item->next = NULL;
    
    if(!playlist->head) {
        playlist->head = item;
        playlist->current = item;
    } else {
        PlaylistItem* current = playlist->head;
        while(current->next) {
            current = current->next;
        }
        current->next = item;
    }
    
    playlist->itemCount++;
}

void SavePlaylist(Playlist* playlist) {
    if(!playlist) return;
    
    // Create playlists directory if it doesn't exist
    mkdir("sd:/playlists", 0777);
    
    FILE* file = fopen(playlist->filename, "w");
    if(!file) return;
    
    // Write M3U header
    fprintf(file, "#EXTM3U\n");
    fprintf(file, "# Playlist: %s\n", playlist->name);
    fprintf(file, "# Items: %d\n", playlist->itemCount);
    
    PlaylistItem* item = playlist->head;
    while(item) {
        // Write extended info
        fprintf(file, "#EXTINF:%d,%s\n", item->duration, item->name);
        fprintf(file, "%s\n", item->path);
        item = item->next;
    }
    
    fclose(file);
}

Playlist* LoadPlaylist(const char* filename) {
    if(strstr(filename, ".m3u") || strstr(filename, ".m3u8")) {
        LoadM3UPlaylist(filename);
        return currentPlaylist;
    }
    return NULL;
}

void LoadM3UPlaylist(const char* filename) {
    FILE* file = fopen(filename, "r");
    if(!file) return;
    
    // Extract playlist name from filename
    char* name = strrchr(filename, '/');
    if(name) name++;
    else name = (char*)filename;
    
    // Remove extension
    char* ext = strrchr(name, '.');
    if(ext) *ext = '\0';
    
    Playlist* playlist = CreatePlaylist(name);
    if(!playlist) {
        fclose(file);
        return;
    }
    
    char line[512];
    char currentName[256] = "";
    int currentDuration = 0;
    
    while(fgets(line, sizeof(line), file)) {
        // Remove newline
        line[strcspn(line, "\r\n")] = 0;
        
        if(strlen(line) == 0) continue;
        
        if(line[0] == '#') {
            // Comment or extended info
            if(strncmp(line, "#EXTINF:", 8) == 0) {
                // Parse duration and name
                char* comma = strchr(line, ',');
                if(comma) {
                    *comma = '\0';
                    currentDuration = atoi(line + 8);
                    strcpy(currentName, comma + 1);
                }
            }
        } else {
            // File path
            if(strlen(line) > 0) {
                char* filename = strrchr(line, '/');
                if(!filename) filename = strrchr(line, '\\');
                if(!filename) filename = (char*)line;
                else filename++;
                
                int isVideo = (strstr(filename, ".mp4") || strstr(filename, ".avi") || 
                              strstr(filename, ".mkv") || strstr(filename, ".mov"));
                
                AddToPlaylist(playlist, currentName[0] ? currentName : filename, line, isVideo);
                
                // Update duration if we parsed it
                if(currentDuration > 0 && playlist->head) {
                    PlaylistItem* item = playlist->head;
                    while(item->next) item = item->next;
                    item->duration = currentDuration;
                }
                
                currentName[0] = '\0';
                currentDuration = 0;
            }
        }
    }
    
    fclose(file);
    currentPlaylist = playlist;
}

void FreePlaylist(Playlist* playlist) {
    if(!playlist) return;
    
    PlaylistItem* item = playlist->head;
    while(item) {
        PlaylistItem* next = item->next;
        free(item);
        item = next;
    }
    
    free(playlist);
}

PlaylistItem* GetCurrentItem(Playlist* playlist) {
    if(!playlist) return NULL;
    return playlist->current;
}

PlaylistItem* GetNextItem(Playlist* playlist) {
    if(!playlist || !playlist->current) return NULL;
    
    playlist->current = playlist->current->next;
    if(playlist->current) {
        playlist->currentIndex++;
    } else {
        // Loop to beginning
        playlist->current = playlist->head;
        playlist->currentIndex = 0;
    }
    
    return playlist->current;
}

PlaylistItem* GetPreviousItem(Playlist* playlist) {
    if(!playlist || !playlist->current) return NULL;
    
    // Find previous item
    PlaylistItem* item = playlist->head;
    PlaylistItem* prev = NULL;
    
    while(item && item != playlist->current) {
        prev = item;
        item = item->next;
    }
    
    if(prev) {
        playlist->current = prev;
        playlist->currentIndex--;
    } else {
        // Loop to end
        item = playlist->head;
        while(item && item->next) {
            item = item->next;
        }
        playlist->current = item;
        playlist->currentIndex = playlist->itemCount - 1;
    }
    
    return playlist->current;
}

void ShufflePlaylist(Playlist* playlist) {
    if(!playlist || playlist->itemCount < 2) return;
    
    // Convert to array for shuffling
    PlaylistItem** items = malloc(playlist->itemCount * sizeof(PlaylistItem*));
    if(!items) return;
    
    PlaylistItem* item = playlist->head;
    int i = 0;
    while(item) {
        items[i++] = item;
        item = item->next;
    }
    
    // Fisher-Yates shuffle
    for(i = playlist->itemCount - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        PlaylistItem* temp = items[i];
        items[i] = items[j];
        items[j] = temp;
    }
    
    // Rebuild linked list
    playlist->head = items[0];
    for(i = 0; i < playlist->itemCount - 1; i++) {
        items[i]->next = items[i + 1];
    }
    items[playlist->itemCount - 1]->next = NULL;
    
    playlist->current = playlist->head;
    playlist->currentIndex = 0;
    
    free(items);
}

void SortPlaylistByName(Playlist* playlist) {
    if(!playlist || playlist->itemCount < 2) return;
    
    // Convert to array for sorting
    PlaylistItem** items = malloc(playlist->itemCount * sizeof(PlaylistItem*));
    if(!items) return;
    
    PlaylistItem* item = playlist->head;
    int i = 0;
    while(item) {
        items[i++] = item;
        item = item->next;
    }
    
    // Bubble sort by name
    for(i = 0; i < playlist->itemCount - 1; i++) {
        for(int j = 0; j < playlist->itemCount - i - 1; j++) {
            if(strcasecmp(items[j]->name, items[j + 1]->name) > 0) {
                PlaylistItem* temp = items[j];
                items[j] = items[j + 1];
                items[j + 1] = temp;
            }
        }
    }
    
    // Rebuild linked list
    playlist->head = items[0];
    for(i = 0; i < playlist->itemCount - 1; i++) {
        items[i]->next = items[i + 1];
    }
    items[playlist->itemCount - 1]->next = NULL;
    
    playlist->current = playlist->head;
    playlist->currentIndex = 0;
    
    free(items);
}

void SortPlaylistByDuration(Playlist* playlist) {
    if(!playlist || playlist->itemCount < 2) return;
    
    // Convert to array for sorting
    PlaylistItem** items = malloc(playlist->itemCount * sizeof(PlaylistItem*));
    if(!items) return;
    
    PlaylistItem* item = playlist->head;
    int i = 0;
    while(item) {
        items[i++] = item;
        item = item->next;
    }
    
    // Bubble sort by duration
    for(i = 0; i < playlist->itemCount - 1; i++) {
        for(int j = 0; j < playlist->itemCount - i - 1; j++) {
            if(items[j]->duration > items[j + 1]->duration) {
                PlaylistItem* temp = items[j];
                items[j] = items[j + 1];
                items[j + 1] = temp;
            }
        }
    }
    
    // Rebuild linked list
    playlist->head = items[0];
    for(i = 0; i < playlist->itemCount - 1; i++) {
        items[i]->next = items[i + 1];
    }
    items[playlist->itemCount - 1]->next = NULL;
    
    playlist->current = playlist->head;
    playlist->currentIndex = 0;
    
    free(items);
}

int GetPlaylistDuration(Playlist* playlist) {
    if(!playlist) return 0;
    
    int totalDuration = 0;
    PlaylistItem* item = playlist->head;
    
    while(item) {
        totalDuration += item->duration;
        item = item->next;
    }
    
    return totalDuration;
}

void CreateDefaultPlaylists() {
    // Create some default playlists
    Playlist* favorites = CreatePlaylist("Favorites");
    Playlist* recentlyPlayed = CreatePlaylist("Recently Played");
    Playlist* videos = CreatePlaylist("Videos");
    Playlist* music = CreatePlaylist("Music");
    
    if(favorites) {
        playlists[playlistCount++] = favorites;
        SavePlaylist(favorites);
    }
    if(recentlyPlayed) {
        playlists[playlistCount++] = recentlyPlayed;
        SavePlaylist(recentlyPlayed);
    }
    if(videos) {
        playlists[playlistCount++] = videos;
        SavePlaylist(videos);
    }
    if(music) {
        playlists[playlistCount++] = music;
        SavePlaylist(music);
    }
}
