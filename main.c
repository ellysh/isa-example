#include <unistd.h>
#include <sys/io.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

#define TRUE    1
#define FALSE   0

#define CHECK_BIT(var, pos) ((var) & (1<<(pos)))

static const unsigned long kRgCsr = 0x330;
static const unsigned long kRgA = 0x332;
static const unsigned long kRgB = 0x334;
static const unsigned long kRegistersCount = 16;

static const int kCommandDelay = 1000;

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
    outw(0x0100, kRgCsr);
    usleep(kCommandDelay);
    outw(0x0000, kRgCsr);
    usleep(kCommandDelay);
}

void WriteCommand()
{
    outw(0x0000, kRgA);
    usleep(kCommandDelay);
    outw(0x0B00, kRgB);
    usleep(kCommandDelay);
}

double GetAngle(unsigned short reg)
{
    double result = 0;
    double weight = 45.0/8192.0;

    int i;

    for (i = 0; i < 16; i++)
    {
        if ( CHECK_BIT(reg, i) )
            result += weight;

        weight = weight * 2;
    }

    return result;
}

int main(int argc, char **argv)
{
    OpenPort();

    StartDevice();

    unsigned short rg_a;
    unsigned short rg_b;
    unsigned short rg_c;

    while (TRUE)
    {
        system("clear");

        WriteCommand();

        rg_a = inw(kRgA);
        rg_b = inw(kRgB);
        rg_c = inw(kRgCsr);

        printf("kRgA = 0x%x\n", rg_a);
        printf("kRgB = 0x%x\n", rg_b);
        printf("kRgC = 0x%x\n", rg_c);
        printf("angle = %f\n", GetAngle(rg_a));

        usleep(100 * 1000);
    }
}
