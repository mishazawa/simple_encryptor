#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

char rotl (unsigned char value, unsigned int count) {
    return (value << count) | (value >> (8 - count));
}

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("argc: %d\n", argc);
        return 1;
    }

    char* filename = argv[1];

    printf("Filename: %s\n", filename);



    FILE * file_in = fopen(filename, "rb");
    fseek(file_in, 0, 2);
    uint file_len = ftell(file_in);
    char * buffer = malloc(file_len);
    fseek(file_in, 0, 0);
    fread(buffer, file_len, 1, file_in);
    fclose(file_in);
    
    int seed = (int)((unsigned char)(buffer[3]) << 24 |
            (unsigned char)(buffer[2]) << 16 |
            (unsigned char)(buffer[1]) << 8 |
            (unsigned char)(buffer[0]));

    srand(seed);
    printf("Seed: %d\n", seed);
    
    char * temp_buffer = malloc(file_len - 4);


    for (int i = 4; i < file_len; i++) {
        uint r1 = rand();
        uint r2 = rand() & 7;
        temp_buffer[i - 4] = rotl(buffer[i], 8 - r2) ^ r1; 
    }

    char * dec_ext = ".decrypted";
    char * filename_dec = malloc(strlen(filename) + strlen(dec_ext) + 1);
    strcpy(filename_dec, filename);
    strcat(filename_dec, dec_ext);
    FILE * outfile_handle = fopen(filename_dec, "wb");

    fwrite(temp_buffer, 1, file_len - 4, outfile_handle);
    fclose(outfile_handle);
    printf("Filename out: %s\n", filename_dec);

    return 0;
}