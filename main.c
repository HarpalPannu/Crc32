#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "crc.h"
char *readable_fs(double size, char *buf)
{
    int i = 0;
    const char *units[] = {"B", "kB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB"};
    while (size > 1024)
    {
        size /= 1024;
        i++;
    }
    sprintf(buf, "%.*f %s", i, size, units[i]);
    return buf;
}
int main(void)
{
    char *filenames[5] =
        {
            "/media/harpal/Data/New folder/It.2017.RERiP.720p.BluRay.x264-Pahe.in.mkv",
            "Manzil.mp3"};
    int sel = 0;
    char buf[10];
    crc_t crc;
    time_t start, end;
    start = time(NULL);
    crc = crc_init();
    FILE *file = NULL;
    file = fopen(filenames[sel], "rb");
    if (file == NULL)
    {
        printf("Error! Unable to read file\n");
        return -1;
    }
    unsigned char buffer[1024];
    size_t bytesRead = 0;
    struct stat info;
    lstat(filenames[sel], &info);
    double filesize = info.st_size;
    double processed = 0;
    printf("Name: %s \nSize: %s (%d Bytes)\n", filenames[sel],readable_fs(info.st_size, buf), (int)filesize);

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0)
    {
        crc = crc_update(crc, buffer, bytesRead);

        processed += bytesRead;
        double precent = (processed / filesize) * 100.0;
        printf("%0.2f%c \r", precent, '%');
        fflush(stdout);
    }

    crc = crc_finalize(crc);

    printf("CRC32 Hexadecimal: 0x%lX\n", (unsigned long)crc);
    printf("CRC32 Decimal: %ld\n", (unsigned long)crc);
    end = time(NULL);
    int timetook = end - start;
    printf("Time taken: %d s\n", timetook);
    return 0;
}
