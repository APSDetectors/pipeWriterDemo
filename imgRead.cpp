#include <stdlib.h>
#include <stdio.h>

#include "pipebinaryformat.h"


//To compile in linux
// g++ imgRead.cpp pipebinaryformat.cpp -o imgRead

int main(int argc, char *argv[]) {

char pname[256];

if (argc>1)
{
    strcpy(pname, argv[1]);
}   
else
{
    strcpy(pname,"./mypipe");
}

pipeBinaryFormat *pipeformat = new pipeBinaryFormat();


FILE *fp;

printf("To Open pipe %s for reading.\n",pname);
fp = fopen(pname,"r");

printf("Done Open pipe %s for reading.\n",pname);

int imgsize = 256*256;

unsigned short *imgdata =(unsigned short*) malloc(imgsize*sizeof(short));

int nimgs = 100;

int sizex, sizey, size_pixels, frame_number, inp_img_cnt, error_code;
error_code=0;

while (error_code ==0)
{
    
    // send the image to pipe.
    printf("Waiting for image\n");
    pipeformat->readDataBlock(
            fp,
            imgdata,
            &sizex,
            &sizey,
            &size_pixels,
            &frame_number,
            &inp_img_cnt,
            &error_code);
    
    printf("Got Img Num %d, size=%d,%d, Num pix=%d, Err=%d\n",
        frame_number,sizex,sizey,size_pixels,error_code);
    
}

printf("Got last img, close up\n");

free(imgdata);
fclose(fp);

delete pipeformat;

return(0);
}
