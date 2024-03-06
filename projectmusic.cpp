#include <iostream>
#include <cstring>

using namespace std;

class Node
{
public:
    char *artist;
    char *songName;
    char *genre;
    Node *prev;
    Node *next;

    Node(const char *artist, const char *songName, const char *genre)
    {
        this->artist = strdup(artist);
        this->songName = strdup(songName);
        this->genre = strdup(genre);
    }

    ~Node()
    {
        free(artist);
        free(songName);
        free(genre);
    }
};

class MusicPlaylist
{
private:
    Node *head;
    Node *tail;
    Node *currentsong;
public:
    MusicPlaylist()
    {
        head = NULL;
        tail = NULL;
        currentsong=NULL;
    }

    void insert(const char *art, const char *song, const char *gen)
    {
        Node *newNode = new Node(art, song, gen);
        if (head == NULL)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        if (!currentsong) 
        {
            currentsong = head;
        }
    }

    void display() const
    {
        Node *current = head;
        while (current != NULL)
        {
            cout << "Song: " << current->songName << ", Artist: " << current->artist << ", Genre: " << current->genre << endl;
            current = current->next;
        }
    }

    void search(const char *song) const
    {
        Node *current = head;
        while (current != NULL)
        {
            if (strcmp(current->songName, song) == 0)
            {
                cout << "Song found:" << endl;
                cout << "Song: " << current->songName << ", Artist: " << current->artist << ", Genre: " << current->genre << endl;
                return;
            }
            current = current->next;
        }
        cout << "Song not found." << endl;
    }


    void deleted(const char *song)
    {
        if (head == NULL)
        {    
            cout << "Playlist is empty." << endl;
            return;
        }

        Node *current = head;
        while (current != NULL && strcmp(current->songName, song) != 0)
        {
            current = current->next;
        }

        if (current != NULL)
        {
            if (current->prev != NULL)
            {
                current->prev->next = current->next;
            }
            else
            {
                head = current->next;
            }

            if (current->next != NULL)
            {
                current->next->prev = current->prev;
            }
            else
            {
                tail = current->prev;
            }

            delete current;
            cout << "Song deleted." << endl;
        }
        else
        {
            cout << "Song not found." << endl;
        }
    }

        void playCurrentSong() const {
        if (currentsong) {
            cout << "Playing: " << currentsong->songName << " by " << currentsong->artist << endl;
        } else {
            cout << "No song is currently selected." << endl;
        }
    }

    void nextsong() {
        if (currentsong) {
            currentsong = currentsong->next;
            if (!currentsong) {
                currentsong = head;
            }
        }
    }

    void prevsong() {
        if (currentsong) {
            currentsong = currentsong->prev;
            if (!currentsong) {
                currentsong = tail;
            }
        }
    }

    void clear()
    {
        while (head != NULL)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
        tail = NULL;
        cout << "Playlist cleared." << endl;
    }

    ~MusicPlaylist()
    {
        clear();
    }
};

int main()
{
    MusicPlaylist play;
    int n;
    char c;
    do
    {

        cout << "Choose the option:\n1.Add song\n2.Display playlist\n3.Search song\n4.Next song\n5.Previous song\n6.Delete song\n7.Clear playlist" << endl;
        cin >> n;
        switch (n)
        {
        case 1:
            char a[40], s[40], g[40];
            cout << "Enter Artist name, Song name and Genre to add in playlist:" << endl;
            cin >> a >> s >> g;
            play.insert(a, s, g);
            break;

        case 2:
            cout << "Music Playlist:" << endl;
            play.display();
            break;

        case 3:
            char se[40];
            cout << "Enter name of song to be search in playlist:" << endl;
            cin >> s;
            play.search(s);
            break;

        case 4:
            cout << "Playing Next song:" << endl;
            play.nextsong();
            play.playCurrentSong();
            break;

        case 5:
            cout << "Playing Previous song:" << endl;
            play.prevsong();
            play.playCurrentSong();
            break;

        case 6:
            char d[40];
            cout << "Enter name of song to be deleted:" << endl;
            cin >> s;
            play.deleted(s);
            break;

        case 7:
            cout << "Clearing playlist:" << endl;
            play.clear();
            break;

        default:
            cout << "Invalid Option" << endl;
            break;
        }
        cout<<"Enter y to continue:"<<endl;
        cin>>c;
    }while(c=='y');
        
        return 0;
    }
