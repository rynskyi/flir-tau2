#include <stdio.h>
#include <stdint.h>
#include "TauCam.h"

int main()
{
    printf("Main:\n");
    TauCam cam = TauCam();
    cam.setPalette(9);
    cam.setZoom(TAU_ZOOM_8X);
    cam.setSpotMeter(TAU_SPOTMETER_ON_C);
}