#include <unistd.h>
#include <sys/io.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

static const unsigned long kRgCsr = 0x330;
static const unsigned long kRgA = 0x332;
static const unsigned long kRgB = 0x334;
static const unsigned long kRegistersCount = 3;

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
    outw(0x100, kRgCsr);
    usleep(1);
    outw(0x0, kRgCsr);
}

int main(int argc, char **argv)
{
    OpenPort();

    StartDevice();

    printf("0x330 = 0x%x\n", inw(kRgCsr));
}
