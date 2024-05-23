#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/inotify.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define EVENT_SIZE  (sizeof(struct inotify_event))
#define BUF_LEN     (1024 * (EVENT_SIZE + 16))

void log_event(const char *event_type, const char *file_name) {
    FILE *log_file = fopen("event_log.txt", "a");
    if (log_file != NULL) {
        fprintf(log_file, "%s: %s\n", event_type, file_name);
        fclose(log_file);
    }
}

void handle_event(struct inotify_event *event, const char *directory) {
    if (event->mask & IN_CREATE) {
        printf("File created: %s\n", event->name);
    }
    if (event->mask & IN_DELETE) {
        printf("File deleted: %s\n", event->name);
    }
    if (event->mask & IN_MODIFY) {
        printf("File modified: %s\n", event->name);
    }
    if (event->mask & IN_MOVE) {
        printf("File moved: %s\n", event->name);
    }
    if (event->mask & IN_ATTRIB) {
        printf("Metadata changed for: %s\n", event->name);
    }
    if (event->mask & IN_MOVED_FROM) {
        printf("File moved out of directory: %s\n", event->name);
    }
    if (event->mask & IN_MOVED_TO) {
        printf("File moved into directory: %s\n", event->name);
    }
    log_event("EVENT", event->name);
}

int main(int argc, char **argv) {
    int fd;
    int wd;
    char buffe