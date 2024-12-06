#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

int main(int argc, char** args){
    char *path;

    //first, we determine what the directory path is, if there is one
    if(argc < 2){
        path = ".";
    }
    else {
        path = args[1];
    }

    struct stat buff;

    //if data retrieval fails, exit
    if(stat(path, &buff) == -1){
        perror("stat error");

        //Put the EXIT_FAILURE code
        exit(EXIT_FAILURE);
    }

    DIR *directoryPath = opendir(path);

    //If we have an open error, also put EXIT_FAILURE
    if(directoryPath == NULL){
        perror("Open Directory Error");
        exit(EXIT_FAILURE)
    }

    struct dirent *currentDirectory;

    //Now, we need to loop through all the entries in the path until we hit Null
    //Null signifies the end of the path!


    //I do the assignment of currentDirectory and then check for NULL
    while((currentDirectory = readdir(directoryPath) != NULL)){
        //make a filepath variable to store the path, with the max size for safety

        char filePath[FILENAME_MAX]

        //using snprintf, we can concat the directory path with the entry name
        snprintf(filePath, sizeof(filePath), "%s/%s", path, currentDirectory->d_name);

        //Print the name of the entry
        printf("%16.16s\t", currentDirectory->d_name);

        //Now print the number of links
        printf("%" PRIdMAX "\t", (int)buff.st_nlink);

        //Get the type of file, making sure to bitwise and with S_IFMT
        switch(buff.st_mode & S_IFMT){
            case S_IFREG:
                printf("REG\t");
                break;

            case S_IFDIR:
                printf("DIR\t");
                break;

            case S_IFSOCK:
                printf("SOCK\t");
                break;

            case S_IFLNK:
                printf("LNK\t");
                break;

            case S_IFBLK:
                printf("BLK\t");
                break;

            case S_IFCHR:
                printf("CHR\t");
                break;

            case S_IFIFO:
                printf("FIFO\t");
                break;

            default:
                printf("UNKNOWN\t");
                break;
        }

        //Now we check if the current entry is its own directory
        //If it is, get the number of entries

        if((buff.st_mode & S_IFMT) == S_IFDIR){
            DIR *directoryPath2 = opendir(filePath);

            //Show error if opening failure
            if(directoryPath2 == NULL){
                perror("Open Directory Error");
                exit(EXIT_FAILURE)
            }

            struct dirent *tmp;

            //Now we count
            int count = 0;

            //Do the same assignment trick, and go until NULL
            while((tmp = readdir(directoryPath2) != NULL)){
                count++;
            }

            //If it is closed, show error
            if(closedir(directoryPath2)){
                perror("Closed Directory");
                exit(EXIT_FAILURE);
            }

            //Print the count
            printf("%d\t", count);
        }
        else {
            //If it is not a dir, the size if from the stat() method
            printf("%" PRIdMAX "\t", (int)statbuf.st_size);
        }

        //if the file is a normal file, we have to show a preview of the text
        if((statbuf.st_mode & S_IFMT) == S_IFREG){
            int fileDirectory = open(filepath, O_RDONLY);

            //Show error if not opening
            if(fd == -1){
                perror("Open Directory Error");
                exit(EXIT_FAILURE)
            }

            char hold[16];
            int byteAmount = read(fileDirectory, hold, 16);

            if(byteAmount == -1){
                perror("Read Error");
                exit(EXIT_FAILURE);
            }

            //Our preview may have illegal ASCII characters (Not printable)
            //Replace them with a space
            for(int i = 0; i < byteAmount; i++){
                if(hold[i] < 32 || hold[i] > 126){
                    printf(" ");
                }
                else {
                    printf("%c", hold[i]);
                }
            }
        }

        //Print a newline for next entry
        printf("\n");
    }

    //Last error check
    if (closedir(directoryPath) == -1) {
        perror("Closed Directory");
        exit(EXIT_FAILURE);
    }
}
