#include <iostream>
#include <string>
#include <unistd.h> //this give acess to fork() and execvp() I had no idea till now
#include <sys/wait.h> // like the name suggest this gives acces to the wati function
#include <sstream>
#include <vector>
#include <fstream> //this thing lets c++ read from a file
using namespace std;

int main(int argc, char* argv[]) { // argc = how many things were typed and argv = what those things were
    if (argc > 2) {
        cerr << "Error: too many arguements!" << endl;
        return 1;
    }
    
    bool batchMode = false;
    
    ifstream batchFile;
    
    if (argc == 2){
        batchMode = true;
        batchFile.open(argv[1]);
        
        if(!batchFile) {
            cerr << "Could not open the batch file womp womp :(" << endl;
            return 1;
            }
        }
    string line;

    istream* input = &cin;

    if (batchMode) {
        input = &batchFile;
    }
    
    if (!batchMode) {
        cout << "tinysh> ";
    }
    
    while (getline(*input, line)) {
        if (batchMode) {
            cout << line << endl;
        }

        vector<string> commands;
        string command;
        stringstream lineStream(line);

        while (getline(lineStream, command, ';')) {
            commands.push_back(command);
        }

        bool shouldQuit = false;
        
        int childCount = 0;
                
        for (string& command : commands) {

            istringstream iss(command);

            vector<string> parts;
            string word;

            while (iss >> word) {
                parts.push_back(word);
            }

            if (parts.empty()) {
                continue;
            }
            
            if (parts[0] == "quit") {
                shouldQuit = true;
                continue;
            }

            vector<char*> args;

            for (string& part : parts) {
                args.push_back(part.data());
            }

            args.push_back(nullptr);

            pid_t pid = fork();

            if (pid == 0) {

                execvp(args[0], args.data());

                cerr << "Command failed" << endl;
                exit(1);
            }
            else if (pid > 0) {
                childCount++;
            }
            else {
                cerr << "fork failed :((" << endl;
            }
        }

        for (int i = 0; i < childCount; i++){
            wait(nullptr);
        }
        
        if (shouldQuit) {
            break;
        }
        
        if (!batchMode) {
            cout << "tinysh> ";
        }
        
    }

    return 0;
}
