#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

void truncateFiles(const char *dirPath, const char *dateStr);

void truncateFilesRecursive(const char *dirPath, const char *dateStr);

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <directory> <date>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *dirPath = argv[1];
    const char *dateStr = argv[2];

    truncateFiles(dirPath, dateStr);

    return EXIT_SUCCESS;
}

void truncateFiles(const char *dirPath, const char *dateStr)
{
    truncateFilesRecursive(dirPath, dateStr);
}

void truncateFilesRecursive(const char *dirPath, const char *dateStr)
{
    DIR *dir;
    struct dirent *entry;
    struct stat fileStat;

    if ((dir = opendir(dirPath)) == NULL)
    {
        perror("Error opening directory");
        return;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", dirPath, entry->d_name);

        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        if (lstat(path, &fileStat) < 0)
        {
            perror("Error stating file");
            continue;
        }

        if (S_ISDIR(fileStat.st_mode))
        {
            truncateFilesRecursive(path, dateStr); // Recurse into subdirectory
        }
        else
        {
            // Check file creation date
            time_t creationTime = fileStat.st_ctime;
            struct tm *tm_creation = localtime(&creationTime);
            char creationDateStr[11]; // YYYY-MM-DD
            strftime(creationDateStr, sizeof(creationDateStr), "%Y-%m-%d", tm_creation);

            // Compare creation date with provided date
            if (strcmp(creationDateStr, dateStr) > 0)
            {
                // Truncate file to half its original size
                off_t originalSize = fileStat.st_size;
                off_t newSize = originalSize / 2;

                if (truncate(path, newSize) != 0)
                {
                    perror("Error truncating file");
                }
                else
                {
                    printf("Truncated %s to half its original size\n", path);
                }
            }
        }
    }

    closedir(dir);
}
