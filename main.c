#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc, char **argv) {
    FILE *fd;

    if (getuid() != 0) {
        if (setuid(0) != 0) {
            fprintf(stderr, "Error code %d invoking setuid(): %s", errno, strerror(errno));
            return -1;
        }
    }

    if (getuid() != 0) {
        fprintf(stderr, "Running user is not ROOT.");
        return -1;
    }

    fprintf(stderr, "Writing \"3\" in /proc/sys/vm/drop_caches ... ");

    fd = fopen("/proc/sys/vm/drop_caches", "w");
    fprintf(fd, "3\n");
    fclose(fd);

    fprintf(stderr, "done.\n");

    return 0;
}
