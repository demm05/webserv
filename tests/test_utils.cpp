#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string>
#include <fstream>
#include <iostream>
#include <cstring>

bool removeDirectoryRecursive(const std::string &path) {
    DIR *dir = opendir(path.c_str());
    if (!dir) return false;

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        std::string name = entry->d_name;
		// Skip the current and parent directory entries
        if (name == "." || name == "..") continue;

        std::string fullPath = path + "/" + name;
        struct stat st;
        if (stat(fullPath.c_str(), &st) == 0) {
            if (S_ISDIR(st.st_mode)) {
				// Recursively remove the directory
                if (!removeDirectoryRecursive(fullPath)) {
                    closedir(dir);
                    return false;
                }
            } else {
				// Remove the file
                if (unlink(fullPath.c_str()) != 0) {
                    closedir(dir);
                    return false;
                }
            }
        }
    }
    closedir(dir);
    return rmdir(path.c_str()) == 0;
}

void writeFile(const std::string& content, const char* path) {
    std::ofstream out(path);
    out << content;
    out.close();
}