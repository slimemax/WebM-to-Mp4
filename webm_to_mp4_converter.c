#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

#define MAX_FILES 100
#define MAX_FILENAME_LENGTH 256
#define MAX_COMMAND_LENGTH 1024  // Increased buffer size for command

void list_webm_files(char files[MAX_FILES][MAX_FILENAME_LENGTH], int *file_count) {
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (d) {
        *file_count = 0;
        while ((dir = readdir(d)) != NULL) {
            if (strstr(dir->d_name, ".webm") != NULL && *file_count < MAX_FILES) {
                strncpy(files[*file_count], dir->d_name, MAX_FILENAME_LENGTH - 1);  // Ensure null-termination
                files[*file_count][MAX_FILENAME_LENGTH - 1] = '\0'; // Manually null-terminate in case of truncation
                (*file_count)++;
            }
        }
        closedir(d);
    }
}

void display_menu(char files[MAX_FILES][MAX_FILENAME_LENGTH], int file_count) {
    printf("Available .webm files in the current directory:\n");
    for (int i = 0; i < file_count; i++) {
        printf("%d. %s\n", i + 1, files[i]);
    }
    printf("Select a file to convert by entering its number: ");
}

void remove_extension(char *filename) {
    char *dot = strrchr(filename, '.');
    if (dot && strcmp(dot, ".webm") == 0) {
        *dot = '\0'; // Remove the .webm extension
    }
}

int main() {
    char files[MAX_FILES][MAX_FILENAME_LENGTH];
    int file_count = 0;
    int selection = 0;

    // List all .webm files in the current directory
    list_webm_files(files, &file_count);

    if (file_count == 0) {
        printf("No .webm files found in the current directory.\n");
        return 1;
    }

    // Display menu and get user input
    display_menu(files, file_count);
    scanf("%d", &selection);

    if (selection < 1 || selection > file_count) {
        printf("Invalid selection.\n");
        return 1;
    }

    // Prepare input and output file names
    char input_file[MAX_FILENAME_LENGTH];
    strncpy(input_file, files[selection - 1], MAX_FILENAME_LENGTH - 1);
    input_file[MAX_FILENAME_LENGTH - 1] = '\0'; // Ensure null-termination

    remove_extension(input_file);

    char output_file[MAX_FILENAME_LENGTH];
    if (snprintf(output_file, sizeof(output_file), "%s.mp4", input_file) >= MAX_FILENAME_LENGTH) {
        printf("Error: output filename is too long.\n");
        return 1;
    }

    // Construct and execute ffmpeg command
    char command[MAX_COMMAND_LENGTH];
    if (snprintf(command, sizeof(command), "ffmpeg -y -i \"%s\" \"%s\"", files[selection - 1], output_file) >= MAX_COMMAND_LENGTH) {
        printf("Error: command too long.\n");
        return 1;
    }

    printf("Converting %s to %s...\n", files[selection - 1], output_file);
    int result = system(command);

    if (result == 0) {
        printf("Conversion successful! Output file: %s\n", output_file);
    } else {
        printf("Conversion failed.\n");
    }

    return 0;
}

