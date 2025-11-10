#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void copy_file_c(const char *source, const char *destination, size_t buffer_size) {
    FILE *src = fopen(source, "rb");
    if (src == NULL) {
        perror("Greška pri otvaranju izvorne datoteke!");
        exit(EXIT_FAILURE);
    }

    FILE *dest = fopen(destination, "wb");
    if (dest == NULL) {
        perror("Greška pri otvaranju odredišne datoteke!");
        fclose(src);
        exit(EXIT_FAILURE);
    }

    char *buffer = malloc(buffer_size);
    if (buffer == NULL) {
        perror("Greška pri alociranju buffera!");
        fclose(src);
        fclose(dest);
        exit(EXIT_FAILURE);
    }

    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, buffer_size, src)) > 0) {
        if (fwrite(buffer, 1, bytes_read, dest) != bytes_read) {
            perror("Greška pri pisanju u odredišnu datoteku!");
            free(buffer);
            fclose(src);
            fclose(dest);
            exit(EXIT_FAILURE);
        }
    }

    if (ferror(src))
        perror("Greška pri čitanju iz izvorne datoteke!");

    free(buffer);
    fclose(src);
    fclose(dest);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Pravilno korištenje: %s <izvor> <odredište> <veličina buffera>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *source = argv[1];
    const char *destination = argv[2];
    size_t buffer_size = atoi(argv[3]);

    copy_file_c(source, destination, buffer_size);
    return EXIT_SUCCESS;
}
