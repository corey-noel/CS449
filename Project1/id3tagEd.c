// Corey Noel
// For CS 449
// Assignment 1

#include <stdio.h>
#include <string.h>

// tag structure
struct Tag {
    char tag[3];
    char title[30];
    char artist[30];
    char album[30];
    char year[4];
    char comment[28];
    char zero;
    char trackNumber;
    char genre;
};


int main(int argc, char *argv[]) {
    FILE *file;
    int hasTag;
    struct Tag in;

    // throws error if no file specified
    if (argc < 2) {
        printf("Error: No filename specified\n");
        return 1;
    }

    // throws error if file not found
    file = fopen(argv[1], "rb");
    if (file == 0) {
        printf("Error: Could not open file %s\n", argv[1]);
        return 1;
    }

    // reads file into structure
    fseek(file, -128, SEEK_END);
    fread(&in, 128, 1, file);

    // determines if file has a tag or not
    hasTag = (strncmp(in.tag, "TAG", 3) == 0);

    // if only reading structure
    if (argc == 2) {
        if (hasTag) {
            printf("Title: %.30s\n", in.title);
            printf("Artist: %.30s\n", in.artist);
            printf("Album: %.30s\n", in.album);
            printf("Year: %.4s\n", in.year);
            printf("Comment: %.28s\n", in.comment);
            printf("Track number: %d\n", in.trackNumber);
        } else {
            printf("The file has no tag.\n");
        }
    } 

    // if editing structure 
    else {
        int i;

        // create output struct
        struct Tag out;

        // use old tag as base for output
        if (hasTag) {
            out = in;
        } 

        // use empty tag as base for new tag
        else {
            out.tag[0] = 'T';
            out.tag[1] = 'A';
            out.tag[2] = 'G';
            memset(&out.title[0], 0, 30);
            memset(&out.artist[0], 0, 30);
            memset(&out.album[0], 0, 30);
            memset(&out.year[0], 0, 4);
            memset(&out.comment[0], 0, 28);
            out.zero = 0;
            out.trackNumber = 0;
            out.genre = 0;
        }

        // read in command line args
        for (i = 2; i < argc - 1; i += 2) {
            printf("%d\n", i);
            if (strcmp(argv[i], "-title") == 0) {
                printf("Changed title to %s\n", argv[i + 1]);
                strncpy(out.title, argv[i + 1], 30);
            } else if (strcmp(argv[i], "-artist") == 0) {
                printf("Changed artist to %s\n", argv[i + 1]);
                strncpy(out.artist, argv[i + 1], 30);
            } else if (strcmp(argv[i], "-album") == 0) {
                printf("Changed album to %s\n", argv[i + 1]);
                strncpy(out.album, argv[i + 1], 30);
            } else if (strcmp(argv[i], "-year") == 0) {
                printf("Changed year to %s\n", argv[i + 1]);
                strncpy(out.year, argv[i  + 1], 4);
            } else if (strcmp(argv[i], "-comment") == 0) {
                printf("Changed comment to %s\n", argv[i + 1]);
                strncpy(out.comment, argv[i + 1], 28);
            } else if (strcmp(argv[i], "-track") == 0) {
                printf("Changed track to %s\n", argv[i + 1]);
                out.trackNumber = atoi(argv[i + 1]) % 256;
            }
        }

        // print to file
        // open file in write mode and write to it
        if (hasTag) {
            fclose(file);
            file = fopen(argv[1], "wb");
            fseek(file, -128, SEEK_END);
            fwrite(&out, 128, 1, file);
        } 

        // open file in append mode and write to it
        else {
            fclose(file);
            file = fopen(argv[1], "a+b");
            fwrite(&out, 128, 1, file);
        }
    }

    // close file and wrap up
    fclose(file);
    return 0;
}