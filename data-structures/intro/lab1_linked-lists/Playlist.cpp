#include "Playlist.h"

void PlaylistNode::InsertAfter(PlaylistNode *nodeLoc) { // code for inserting an element after one element. 
    PlaylistNode *nodeHolder = nullptr;

    nodeHolder = this->nextNodePtr;
    this->nextNodePtr = nodeLoc;
    nodeLoc->nextNodePtr = nodeHolder; 
}

void PlaylistNode::PrintPlaylistNode() { // prints all the info for one song
    cout << "Unique ID: " << this->uniqueID << endl; 
    cout << "Song Name: " << this->songName << endl;
    cout << "Artist Name: " << this->artistName << endl;
    cout << "Song Length (in seconds): " << this->songLength << endl;
}