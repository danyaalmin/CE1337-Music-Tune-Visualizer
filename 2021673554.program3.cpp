// Danya Almintakh
// CS 1337- 503 Becker
// Homework 1 Program 1.
// 3.1 Software:
// Machine: Microsoft Surface Pro 8
// Software: Windows 11 for x64-based Systems
// Compiler : Code::Blocks

#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cctype>
#include <cstdlib>

using namespace std;

struct Key
{
    char letter;
    char symbol;
    int octave;
    double frequency;
    double wavelength;
};

struct Note
{
    char letter;
    char symbol;
    int octave;
    double duration;
    char comma;
};

struct Key* makeKey(int octave0, char keyLetter0, char keySymbol0, double freq0, double wave0)
{
    struct Key* result = nullptr;

    result = new Key;
    result->octave = octave0;
    result->letter = keyLetter0;
    result->symbol = keySymbol0;
    result->frequency = freq0;
    result->wavelength = wave0;

    return result;
}

struct Note* makeNote(int octave1, char keyLetter1, char keySymbol1, double dur1, char coma)
{
    struct Note* result1 = nullptr;

    result1 = new Note;
    result1->octave = octave1;
    result1->letter = keyLetter1;
    result1->symbol = keySymbol1;
    result1->duration = dur1;
    result1->comma = coma;

    return result1;
}

void showKey(struct Key myKey)
{
    cout << setw(1) <<"["<< myKey.letter ;
    cout << setw(1) << myKey.symbol;
    cout << setw(1) << myKey.octave << "]==>   ( ";
    cout << setw(7) << fixed << setprecision(4) << myKey.frequency << " * ";
    cout << setw(7) << fixed << setprecision(4) << myKey.wavelength << " = ";
    cout << myKey.frequency * myKey.wavelength<< ")";
    cout << endl;
}

void showNote(struct Note myNote)
{
    cout << setw(1) <<"("<< myNote.letter;
    cout << setw(1) << myNote.octave;
    cout << setw(1) << myNote.symbol;
    cout << setw(1) << myNote.comma;
    cout << setw(7)<< fixed << setprecision(3) <<myNote.duration << ")";
    cout << endl;
}

// 3.3.3.1 show key vector

void showKeyVector(vector<Key> Keys)
{
    for (Key x : Keys)
    {
        showKey(x);
    }
}

void showTuneVector(vector<Note> tune)
{
    for (Note x : tune)
    {
        showNote(x);
    }
}
// 3.3.3.3
int FetchIndex(Note target, vector<Key> Keys)
{
    int result = -1;
    int loop = 0;
    int max = Keys.size();

    for (loop = 0; loop < max; loop++)
    {
        if (Keys[loop].letter == target.letter)
        {
            if (Keys[loop].octave == target.octave)
            {
                if (Keys[loop].symbol == target.symbol)
                {
                    result = loop;
                }
            }
        }
    }
    return result;
}

// 3.3.4.1
void loadKey(vector<Key>* Keys)
{
    Keys->clear();
    ifstream keyFile("Keys.txt");
    string token;

    struct Key* newKey = nullptr;

    char keyLetter = '\0';
    char keySymbol = '\0';
    int octave;
    double freq = 0.0;
    double wavelength = 0.0;

    while (!keyFile.eof())
    {
        getline(keyFile, token, ',');
        octave = stoi(token);
        getline(keyFile, token, ',');
        keyLetter = token[0];
        getline(keyFile, token, ',');
        keySymbol = token[0];
        getline(keyFile, token, ',');
        freq = stod(token);

        getline(keyFile, token, '\n');
        wavelength = stod(token);


        newKey = makeKey(octave, keyLetter, keySymbol, freq, wavelength);

        Keys->push_back(*newKey);
    }
    keyFile.close();
}

// 3.3.4.2
void getFileName(string* ptr)
{
    string filename;
    cout << "Please enter the file name: ";
    cin >> filename;
    *ptr = filename;
}

void loadTune(vector<Note>* tune, string filename)
{
    tune->clear();
    ifstream tuneFile;
    tuneFile.open(filename);
    string token;

    struct Note* newNote = nullptr;

    char NoteLetter = '\0';
    char NoteSymbol = '\0';
    int octave = 0;
    double duration = 0;
    char comma;

    while (!tuneFile.eof())
    {

        tuneFile >> NoteLetter;
        tuneFile >> octave;
        tuneFile >> NoteSymbol;
        tuneFile >> comma;
        tuneFile >> duration;

        newNote = makeNote(octave, NoteLetter, NoteSymbol, duration, comma);

        tune->push_back(*newNote);
    }
    tuneFile.close();
}

void myName(string name)
{
    cout << "Danya Almintakh";
    cout << "\nCS 1337-503";
    cout << "\nProgram 3";
    cout << "\n10/14/2022";
    cout << "\n=======================\n";
}

// 3.3.5.1

void drawNote(int minOctave, int maxOctave, int keyIndex, int noteDuration)
{
    int start_position = minOctave * 17;
    int stop_position = (maxOctave + 1) * 17;
    for (int i = start_position; i < keyIndex; i++)
    {
        cout << ".";
    }

    switch (noteDuration)
    {
        case 125:
            cout << "|";
            break;
        case 250:
            cout << "+";
            break;
        case 500:
            cout << "o";
            break;
        case 750:
            cout << "O";
            break;
        case 1000:
            cout << "$";
            break;
        default:
            cout << "-";
            break;
    }
    for (int i = keyIndex + 1; i <= stop_position; i++)
    {
        cout << ".";
    }

    cout << "\n";
}

void drawTune(vector<Key> Keys, vector<Note> tune)
{
    int minOctave = tune[0].octave;
    int maxOctave = tune[0].octave;

    for (int i = 1; i < tune.size(); i++)
    {
        minOctave = min(minOctave, tune[i].octave);
        maxOctave = max(maxOctave, tune[i].octave);
    }

    for (int i = 0; i < tune.size(); i++)
    {
        int keyIndex = FetchIndex(tune[i], Keys);
        drawNote(minOctave, maxOctave, keyIndex, tune[i].duration);
    }

}

void menu()
{
    vector<Key> Keys;
    vector<Note> Tune;
    string filename = " ";

    int choice = 0;
    while (choice != 7)
    {
        cout << ("1. Load Key File\n");
        cout << ("2. Show Loaded Keys\n");
        cout << ("3. Set Tune Filename\n");
        cout << ("4. Load Tune File\n");
        cout << ("5. Show Tune File\n");
        cout << ("6. Draw Tune File\n");
        cout << ("7. Exit\n");
        cout << ("========================\n");
        cout << "::>";
        cin >> choice;
        switch (choice)
        {
            case 1:
            {

                loadKey(&Keys);

                break;
            }
            case 2:
            {
                showKeyVector(Keys);
                break;
            }
            case 3:
            {
                getFileName(&filename);
                break;
            }
            case 4:
            {
                loadTune(&Tune, filename);
                break;
            }
            case 5:
            {
                showTuneVector(Tune);
                break;
            }
            case 6:
            {
                drawTune(Keys, Tune);
                break;
            }
            case 7:
            {
                break;
            }
        }
    }
}

int main()
{
    string name = " ";
    myName(name);
    menu();
}


















































































