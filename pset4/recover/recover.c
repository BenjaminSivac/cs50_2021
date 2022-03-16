#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
// 0xff 0xd8 0xff 1110. 50 JPEGs

const int HEADER_SIZE = 512;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover JPEG\n");
        return 1;
    }
    else
    {
        FILE *input = fopen(argv[1], "r");
        if (input == NULL)
        {
            printf("Could not open file.\n");
            return 1;
        }
    
        // Setting up variables
        int count = 0; // tracking number of images recovered
        uint8_t header[HEADER_SIZE]; // Our buffer of 512 bytes
        FILE *IMG_pointer = NULL; // Pointer to the file that will be written to
        char filename[8]; // Store the name of each jpeg
        
        // 
        while (fread(&header, sizeof(header), 1,
                    input)) // pointer to a block of memory, size of each element to be read, read 1 element at a time, input stream. It reads values from the input_pointer and writes them to buffer.
        {
            if (header[0] == 0xff && header[1] == 0xd8 && header[2] == 0xff && (header[3] & 0xf0) == 0xe0)
            {
                if (!(count == 0))
                {
                    fclose(IMG_pointer);
                }

                sprintf(filename, "%03i.jpg", count);
                IMG_pointer = fopen(filename, "w");
                count++;
            }

            if (!(count == 0))
            {
                fwrite(&header, sizeof(header), 1, IMG_pointer);
            }
        }
        fclose(input);
        fclose(IMG_pointer);
    
        return 0;
    }
}