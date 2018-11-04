#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

int main(int argc, char* argv[]) {
    DIR *dp;
    struct dirent *dirp;
    struct stat fileStat;

    if ((dp=opendir("./")) == NULL) {
        fprintf(stderr, "Can't open current directory.\n");
        exit(1);
    }

    while ((dirp = readdir(dp)) != NULL) {
        if ((lstat(dirp->d_name, &fileStat)) == -1) {
            perror(dirp->d_name);
            exit(2);
        }

        if (S_ISBLK(fileStat.st_mode)) { // block
            printf("b");
        } else if (S_ISSOCK(fileStat.st_mode)) { // socket
            printf("s");
        } else if (S_ISLNK(fileStat.st_mode)) { // symlink
            printf("l");
        } else if (S_ISFIFO(fileStat.st_mode)) { // pipe
            printf("f");
        } else if (S_ISCHR(fileStat.st_mode)) { // char
            printf("c");
        } else if (S_ISDIR(fileStat.st_mode)) { // dir
            printf("d");
        } else if (S_ISREG(fileStat.st_mode)) { // regular
            printf("-");
        } else {
            fprintf(stderr, "Unknown mode of file %s.", dirp->d_name);
        }

        printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
        printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
        if ((fileStat.st_mode & S_ISUID)) {
            printf("s");
        } else {
            printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
        }
        printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
        printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
        if ((fileStat.st_mode & S_ISGID)) {
            printf("s");
        } else {
            printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
        }
        printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
        printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
        if ((fileStat.st_mode & S_ISVTX)) {
            printf("t");
        } else {
            printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");
        }

        printf(" %d %s\n", fileStat.st_nlink, dirp->d_name);
    }

    if ((closedir(dp)) == -1) {
        perror("./");
        exit(3);
    }  

    return 0;
}