#include "Playlist.h"

void PrintMenu(string playlist) { // prints a menu of options with implementations of each option
    PlaylistNode *head = nullptr; // holds top of playlist
    PlaylistNode *curr = nullptr; // changes to song needed
    PlaylistNode *succNode = nullptr; // changes to hold the next of a curr song
    PlaylistNode *prev = nullptr; // changes to hold the prev of a curr song
    PlaylistNode *tail = nullptr; // holds bottom of playlist
    char choice = ' '; // used to get the user's choice from menu
    string id; // unique id for song
    string song; // song name
    string artist; // artist of song
    int time; // how long the song is
    int currPosition; // holds the curr position the user wants to use for the change function
    int newPosition; // holds the new position the user wants to move to in the change function
    int countdown; // used to keep track of certain conditions in functions

    while (choice != 'q') { // while loop for menu to keep outputting until choice == q
        cout << endl; 
        cout << playlist << " PLAYLIST MENU" << endl;
        cout << "a - Add song" << endl; 
        cout << "d - Remove song" << endl;
        cout << "c - Change position of song" << endl; 
        cout << "s - Output songs by specific artist" << endl; 
        cout << "t - Output total time of playlist (in seconds)" << endl; 
        cout << "o - Output full playlist" << endl; 
        cout << "q - Quit" << endl; 
        cout << endl; 
        cout << "Choose an option:" << endl; 
        cin >> choice; 

        if (choice == 'a') { // adds a song to the linked list
            cout << "ADD SONG" << endl; 
            cout << "Enter song's unique ID:" << endl;
            cin >> id;   
            cout << "Enter song's name:" << endl; 
            getline(cin >> ws, song);
            cout << "Enter artist's name:" << endl; 
            getline(cin >> ws, artist);
            cout << "Enter song's length (in seconds):" << endl; 
            cin >> time; 

            PlaylistNode *newSong = new PlaylistNode(id,song, artist, time); // creates new song to insert to list

            if (head == nullptr) {
                head = newSong;
                tail = newSong;
            }

            else {
                curr = tail; 
                tail = newSong; 
                curr->SetNext(tail);
                tail->SetNext(nullptr);
            }
        } 

        else if (choice == 'd') { // removes song from playlist
            cout << "REMOVE SONG" << endl; 
            cout << "Enter song's unique ID:" << endl;
            cin >> id; // used to search for specific song

            if (head == nullptr && tail == nullptr) {
                cout << "Playlist is empty." << endl; 
            }

            else if (head == tail) {
                delete head;
                head = nullptr;
                tail = nullptr;
            }

            else {
                if (head->GetID() == id) { // case made specifically for if head is the id
                    succNode = head->GetNext();
                    cout << "\"" << head->GetSongName() << "\" removed." << endl;

                    delete head; 
                    head = succNode;
                }

                else if (tail->GetID() == id) { // case for if tail is the id
                    for (PlaylistNode *i = head; i != nullptr; i = i->GetNext()) {
                        if (i->GetNext()->GetID() == tail->GetID()) {
                            succNode = i;
                            cout << "\"" << tail->GetSongName() << "\" removed." << endl;

                            delete tail; 
                            tail = succNode; 
                            tail->SetNext(nullptr);
                            break;
                        }
                    }
                }

                else { // code for all other cases
                    for (PlaylistNode* i = head; i != nullptr; i = i->GetNext()) {
                        if (i->GetNext()->GetID() == id) {
                            prev = i;
                        }

                        if (i->GetID() == id) {
                            succNode = i->GetNext();
                            cout << "\"" << i->GetSongName() << "\" removed." << endl;

                            prev->SetNext(succNode);
                            delete i;
                            break;
                        }
                    }
                } 
            }   
        }

        else if (choice == 'c') { // changes the position of the song to a new position
            cout << "CHANGE POSITION OF SONG" << endl;
            cout << "Enter song's current position:" << endl; 
            cin >> currPosition; // current position the song is at
            cout << "Enter new position for song:" << endl;
            cin >> newPosition; // new position the song is going to move to 

            int numOfNodes = 0; 
            for (PlaylistNode *i = head; i != nullptr; i = i->GetNext()) { // gets the number of nodes in the list
                ++numOfNodes;
            }

            if (head == nullptr && tail == nullptr && numOfNodes == 0) {
                cout << "Playlist is empty." << endl; 
            }

            else if (numOfNodes == 1) { // if playlist only has one song, no moving necessary
                cout << "\"" << head->GetSongName() << "\" moved to position " << newPosition << endl;
            }

            else {
                curr = head;
                countdown = currPosition;
                while (countdown > 1) { // gets the song that needs to be moved
                    curr = curr->GetNext();
                    --countdown;
                }

                if (currPosition == newPosition) { // case for if the moving position is the same as the current position, no moving necessary
                    cout << "\"" << curr->GetSongName() << "\" moved to position " << newPosition << endl;
                }

                else {
                    if (newPosition >= numOfNodes) { // if position entered is greater than tail, make succNode tail
                        succNode = tail; 
                    }

                    else {
                        succNode = head;
                        countdown = newPosition;
                        while (countdown > 1) { // finds the designated position for the current song
                            succNode = succNode->GetNext();
                            --countdown;
                        }
                    }

                    if (succNode == head) { // case for if position to move to is head
                        for (PlaylistNode *i = head; i != nullptr; i = i->GetNext()) { // makes sure there's no dangling pointers
                            if (i->GetNext() == curr) {
                                prev = i; 
                            }

                            if (i == curr) {
                                if (tail == curr) {
                                    tail = prev;
                                    tail->SetNext(nullptr);
                                    break;
                                }

                                else {
                                    PlaylistNode *nodeHolder = i->GetNext();
                                    prev->SetNext(nodeHolder);
                                    break;
                                }
                            }
                        }
                        prev = head;
                        head = curr;
                        head->SetNext(prev);
                    }

                    else if (succNode == tail) { // case for if position to move to is tail
                        for (PlaylistNode *i = head; i != nullptr; i = i->GetNext()) { // makes sure there's no dangling pointers in any case
                            if (i->GetNext() == curr) {
                                prev = i;
                            }

                            if (i == curr) {
                                if (head == curr) {
                                    head = head->GetNext();
                                    break;
                                }

                                else {
                                    PlaylistNode *nodeHolder = i->GetNext();
                                    prev->SetNext(nodeHolder);
                                    break;
                                }
                            }
                            
                        }
                        prev = tail;
                        tail = curr;
                        prev->SetNext(tail);
                        tail->SetNext(nullptr);
                    }

                    else { // case for if succNode is not head or tail
                        for (PlaylistNode *i = head; i != nullptr; i = i->GetNext()) { // points everything accordingly 
                            if (i->GetNext() == curr) {
                                prev = i;
                            }

                            if (i == curr) {
                                if (head == curr) {
                                    head = head->GetNext();
                                    break;
                                }

                                else if (tail == curr) {
                                    tail = prev;
                                    tail->SetNext(nullptr);
                                    break;
                                }

                                else {
                                    PlaylistNode *nodeHolder = i->GetNext();
                                    prev->SetNext(nodeHolder);
                                    break;
                                }
                            }
                        }

                        if (currPosition < newPosition) {
                            succNode->InsertAfter(curr);
                        }

                        else {
                            for (PlaylistNode *i = head; i != nullptr; i = i->GetNext()) {
                                if (i->GetNext() == succNode) {
                                    prev = i; 
                                    break;
                                }
                            }
                            prev->InsertAfter(curr);
                        }
                    }
                    cout << "\"" << curr->GetSongName() << "\" moved to position " << newPosition << endl; 
                }
            }
        }

        else if (choice == 's') { // outputs songs by the specific artist inputted
            cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl; 
            cout << "Enter artist's name:" << endl; 
            getline(cin >> ws, artist); 
            cout << endl; 

            if (head == nullptr && tail == nullptr) {
                cout << "Playlist is empty." << endl;
            }
            
            else {
                int numOfSongs = 0;
                int currCount = 0;
                curr = head; 
                countdown = 1;

                for (PlaylistNode *i = head; i != nullptr; i = i->GetNext()) { // needed to see if we needed an extra endl in later code
                    if (i->GetArtistName() == artist) {
                        ++numOfSongs;
                    }
                }

                while (curr != nullptr) {
                    if (curr->GetArtistName() == artist) {
                        cout << countdown << "." << endl;
                        curr->PrintPlaylistNode();
                        ++currCount;

                        if (currCount < numOfSongs) { // codes for extra endl for whitespace
                            cout << endl; 
                        }
                    }
                    
                    ++countdown;
                    curr = curr->GetNext();
                }
            }
        }

        else if (choice == 't') { // outputs the total time of the playlist in seconds
            cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;

            int totalTime = 0;
            for (PlaylistNode *i = head; i != nullptr; i = i->GetNext()) { // adds all songs in the playlist
                totalTime += i->GetSongLength();
            }

            cout << "Total time: " << totalTime << " seconds" << endl; 
        }

        else if (choice == 'o') { // outputs the whole playlist 
            cout << playlist << " - OUTPUT FULL PLAYLIST" << endl; 

            if (head == nullptr && tail == nullptr) { // if the playlist is empty case
                cout << "Playlist is empty" << endl; 
            }
            
            else {
                int songPosition = 1; 
                for (PlaylistNode *i = head; i != tail; i = i->GetNext()) { 
                    cout << songPosition << "." << endl;
                    i->PrintPlaylistNode();
                    cout << endl; 
                    ++songPosition;
                }

                cout << songPosition << "." << endl; 
                tail->PrintPlaylistNode();
            }
        }
    }
}

int main () {
    string playlistName; 

    cout << "Enter playlist's title:" << endl;
    getline(cin >> ws, playlistName);
    PrintMenu(playlistName); // calls menu to display

    return 0;
}