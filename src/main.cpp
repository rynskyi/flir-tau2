#include <stdio.h>
#include <stdint.h>
#include "TauCam.h"

int main()
{
    printf("Main:\n");
    TauCam cam = TauCam();
    cam.setPalette(3);
    cam.setPalette(7);
    cam.setPalette(9);
}