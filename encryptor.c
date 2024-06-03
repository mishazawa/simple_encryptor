#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

char rotl (unsigned char value, unsigned int count) {
    return (value << count) | (value >> (8 - count));
}

const int SEED_LEN = 4;

int main(int argc, char *argv[]) {

    if (argc != 3) {
        printf("argc: %d\n", argc);
        return 1;
    }

    char *p;
    
    long seed = strtol(argv[1], &p, 10);
    char* filename = argv[2];

    printf("Seed: %d\n", seed);
    printf("Filename: %s\n", filename);

    srand(seed);


    FILE * file_in = fopen(filename, "rb");
    fseek(file_in, 0, 2);
    uint file_len = ftell(file_in);
    char * buffer = malloc(file_len);
    fseek(file_in, 0, 0);
    fread(buffer, file_len, 1, file_in);
    fclose(file_in);
    

    for (int i = 0; i < file_len; i++) {
        uint r1 = rand();
        uint r2 = rand() & 7;
        buffer[i] = rotl(buffer[i] ^ r1, r2); 
    }

    char * enc_ext = ".encrypted";
    char * filename_enc = malloc(strlen(filename) + strlen(enc_ext) + 1);
    strcpy(filename_enc, filename);
    strcat(filename_enc, enc_ext);
    FILE * outfile_handle = fopen(filename_enc,"wb");
    fwrite(&seed, 1, SEED_LEN, outfile_handle);
    fwrite(buffer, 1, file_len, outfile_handle);
    fclose(outfile_handle);
    printf("Filename out: %s\n", filename_enc);

    return 0;
}