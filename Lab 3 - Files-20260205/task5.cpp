#include <iostream>
#include <unistd.h>
#include <limits.h>
#include <dirent.h>

using namespace std;

int main() {
    char cwd[PATH_MAX];
    // current directory
    getcwd(cwd, sizeof(cwd));
    cout << "Current directory: " << cwd << endl;
    // cd to "folder"
    chdir("folder");
    // new directory
    getcwd(cwd, sizeof(cwd));
    cout << "After chdir: " << cwd << endl;

    // print files in folder
    DIR* dir = opendir(".");
    struct dirent* entry;
    cout << "Directory contents:" << endl;
    while ((entry = readdir(dir)) != nullptr) {
        cout << entry->d_name << endl;
    }
    closedir(dir);
    return 0;
}
