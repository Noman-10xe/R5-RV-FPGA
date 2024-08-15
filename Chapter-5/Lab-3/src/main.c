#if defined(D_NEXYS_A7)
   #include "bsp_printf.h"
   #include "bsp_mem_map.h"
   #include "bsp_version.h"
#else
   PRE_COMPILED_MSG("no platform was defined")
#endif

#include "psp_api.h"


typedef struct {
    unsigned char R;
    unsigned char G;
    unsigned char B;
} RGB;

#define N 128
#define M 128

//#define N 256
//#define M 256

extern unsigned char VanGogh_128x128[];
RGB ColourImage[N][M];
unsigned char GreyImage[N][M];


void initColourImage(RGB image[N][M]) {
    int i,j;

    for (i=0;i<N;i++)
        for (j=0; j<M; j++) {
            image[i][j].R = VanGogh_128x128[(i*M + j)*3];
            image[i][j].G = VanGogh_128x128[(i*M + j)*3 + 1];
            image[i][j].B = VanGogh_128x128[(i*M + j)*3 + 2];
        }
}


unsigned char ColourToGrey_Pixel(unsigned char R, unsigned char G, unsigned char B){
	unsigned char grey = (((306 * R) + (601 * G) + (117 * B))/1024);
	return grey;
}

extern void ColourToGrey(RGB Colour[N][M], unsigned char Grey[N][M]);


int main(void) {

    
    // Create an NxM matrix using the input image
    initColourImage(ColourImage);
    
    // Transform Colour Image to Grey Image
    ColourToGrey(ColourImage,GreyImage);
    
    // Initialize Uart
    uartInit();
        
    // Print message on the serial output
    printfNexys("Created Grey Image");

    while(1);
    
    return 0;
}
