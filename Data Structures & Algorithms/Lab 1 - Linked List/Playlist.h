#ifndef PLAYLIST_H
#define PLAYLIST_H
#include <iostream>
#include <string>
using namespace std; 

class PlaylistNode {
    public: 
        PlaylistNode() : uniqueID("none"), songName("none"), artistName("none"), songLength(0), nextNodePtr(nullptr) {} // constructs the empty nodes
        PlaylistNode(string ID, string song, string artist, int length) : uniqueID(ID), songName(song), artistName(artist), songLength(length) {} // constructs the nodes with song info
        void InsertAfter (PlaylistNode *nodeLoc);
        void SetNext(PlaylistNode *nodeLoc) {nextNodePtr = nodeLoc;} // sets the nextptr to the next node passed in 
        string GetID() {return this->uniqueID;} // returns the id of the song
        string GetSongName() {return this->songName;} // returns song name
        string GetArtistName() {return this->artistName;} // returns artist of specific song
        int GetSongLength() {return this->songLength;} // returns the length of the song
        PlaylistNode* GetNext() {return this->nextNodePtr;} // returns the next song in the linked list or playlist
        void PrintPlaylistNode(); 
    private:
        string uniqueID;
        string songName;
        string artistName; 
        int songLength;
        PlaylistNode *nextNodePtr;
};

#endif