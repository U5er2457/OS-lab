#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

void copy_file_sys(const char *source, const char *destination, size_t buffer_size) {
    int src = open(source, O_RDONLY);
    if (src == -1) {
        perror("Greška pri otvaranju izvorne datoteke!");
        exit(EXIT_FAILURE);
    }

    int dest = open(destination, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest == -1) {
        perror("Greška pri otvaranju odredišne datoteke!");
        close(src);
        exit(EXIT_FAILURE);
    }

    char *buffer = malloc(buffer_size);
    if (buffer == NULL) {
        perror("Greška pri alociranju buffera!");
        close(src);
        close(dest);
        exit(EXIT_FAILURE);
    }

    ssize_t bytes_read;
    while ((bytes_read = read(src, buffer, buffer_size)) > 0) {
        ssize_t bytes_written = write(dest, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            perror("Greška pri pisanju u odredišnu datoteku!");
            free(buffer);
            close(src);
            close(dest);
            exit(EXIT_FAILURE);
        }
    }

    if (bytes_read == -1)
        perror("Greška pri čitanju iz izvorne datoteke!");

    free(buffer);
    close(src);
    close(dest);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Korištenje: %s <izvor> <odredište> <veličina buffera>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *source = argv[1];
    const char *destination = argv[2];
    size_t buffer_size = atoi(argv[3]);

    copy_file_sys(source, destination, buffer_size);
    return EXIT_SUCCESS;
}
