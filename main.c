#include <unistd.h>
#include <sys/io.h>
#include <stdlib.h>

static const unsigned long kBaseAddress = 0x330;
static const unsigned long kRegistersCount = 3;

void OpenPort()
{
    int rc;
    rc = ioperm(kBaseAddress, kRegistersCount, 1);
    if ( rc != 0 )
        exit(0);
}

int main(int argc, char **argv)
{
    OpenPort();
}
