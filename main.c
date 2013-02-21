#include <unistd.h>
#include <sys/io.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

#define TRUE    1
#define FALSE   0

static const unsigned long kRgCsr = 0x330;
static const unsigned long kRgA = 0x332;
static const unsigned long kRgB = 0x334;
static const unsigned long kRegistersCount = 16;

void OpenPort()
{
    int rc;
    rc = ioperm(kRgCsr, kRegistersCount, 1);
    if ( rc != 0 )
    {
        printf("OpenPort() - error = %d\n", errno);
        exit(0);
    }
}

void StartDevice()
{
    outb(0x00, kRgCsr);
    outb(0x01, kRgCsr + 1);
    usleep(5);
    outw(0x0000, kRgCsr);
    usleep(5);
}

void WriteCommand()
{
    outw(0x0000, kRgA);
    usleep(5);
    outw(0x00, kRgB);
    outw(0x0B, kRgB + 1);
    usleep(5);
}

int main(int argc, char **argv)
{
    OpenPort();

    StartDevice();

    unsigned short rg_a;
    unsigned short rg_b;

    while (TRUE)
    {
        WriteCommand();

        rg_a = inw(kRgA);
        rg_b = inw(kRgB);

        if ( (rg_a != 0x20) && (rg_b != 0x20) )
        {
            printf("kRgA = 0x%x\n", rg_a);
            printf("kRgB = 0x%x\n", rg_b);
            break;
        }
    }
}
