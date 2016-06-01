#include <stdlib.h>
#include <stdio.h>

#include "pipebinaryformat.h"


//To compile in linux
// g++ imgWrite.cpp pipebinaryformat.cpp -o imgWrite

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

printf("Open pipe %s for writing. You should have mkfifo mypipe in linux.\n",pname);

pipeBinaryFormat *pipeformat = new pipeBinaryFormat();


FILE *fp;
fp = fopen(pname,"w");

//make image memory
int imgsize = 256*256;

unsigned short *imgdata =(unsigned short*) malloc(imgsize*sizeof(short));

int nimgs = 100;
int errcode = 0;

for (int k=0; k<nimgs;k++)
{
    //create image. change every time, with k as offset to a counter.
    for (int pix = 0; pix<imgsize;pix++)
    {
        imgdata[pix] =(unsigned short)( k + pix);
    }
    
    //on last image, set errcode to 1.
    if (k==(nimgs-1))
        errcode =1;
    
    // send the image to pipe.
    printf("Sending img %d\n",k);
    pipeformat->writeDataBlock(
            fp,
            imgdata,
            256,//xsuze
            256,//y size
            imgsize,//num pixels
            k,//frame nuimber
            0,//some other int you can send, imgcnt
            errcode);//error code, anotehr header metadata number yuo can send. 
    
    
}


free(imgdata);
fclose(fp);

delete pipeformat;

return(0);
}
