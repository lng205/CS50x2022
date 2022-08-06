#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BLOCK_SIZE 512
#define JPEG_HEAD 0xffd8ffe

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //command validation check
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    //open file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("unsuported file\n");
        return 1;
    }

    //read data
    BYTE buffer[BLOCK_SIZE];

    //find first image
    do
    {
        fread(buffer, 1, BLOCK_SIZE, file);
    }
    while ((buffer[0] << 20) + (buffer[1] << 12) + (buffer[2] << 4) + (buffer[3] >> 4) != JPEG_HEAD);
    FILE *outptr = fopen("000.jpg", "w");
    fwrite(buffer, 1, BLOCK_SIZE, outptr);

    //find next image
    int i = 1;
    while (fread(buffer, 1, BLOCK_SIZE, file) == BLOCK_SIZE)
    {
        if ((buffer[0] << 20) + (buffer[1] << 12) + (buffer[2] << 4) + (buffer[3] >> 4) == JPEG_HEAD)
        {
            fclose(outptr);
            char fname[] = "000.jpg";
            //open a new file
            if (i < 10)
            {
                sprintf(&fname[2], "%d.jpg", i);
            }
            else
            {
                sprintf(&fname[1], "%d.jpg", i);
            }
            i++;
            outptr = fopen(fname, "w");
        }
        fwrite(buffer, 1, BLOCK_SIZE, outptr);
    }
    fclose(outptr);
    fclose(file);
    return 0;
}