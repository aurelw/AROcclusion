/*
 * Video capture module with libfreenect for AR Toolkit
 * 
 * (c) Copyrights 2010 Aurel Wildfellner
 * 
 * licensed under the terms of the GPL v2.0
 *
 */

/* include AR Toolkit*/ 
#include <AR/config.h>
#include <AR/ar.h>
#include <AR/video.h>

/* using memcpy */
#include <string.h>
#include <pthread.h>

/* openni */
#include <XnOpenNI.h>
#include <XnLog.h>
#include <XnCppWrapper.h>


#define XML_CONFIG  "/home/aurel/SamplesConfig.xml"


struct _AR2VideoParamT {
	/* size of the image */
	int	width, height;

	/* the actual video buffer 
       double buffering is done in render part,
        so simply lock and copy here */
    ARUint8             *backBuffer;
    ARUint8             *frontBuffer;
    size_t              rgbBuffer_size;

    int depthWidth, depthHeight;
    ARUint32 *depthBackBuffer;
    ARUint32 *depthFrontBuffer;
    size_t depthBuffer_size;

    /* openni */
    xn::Context *context;
    xn::DepthGenerator *depthGen;
    xn::ImageGenerator *imageGen;

    pthread_mutex_t videoBuffer_mutex;
    pthread_t openni_event_thread;

    int streaming;
};


static AR2VideoParamT* gVid = 0;


int arVideoOpen( char *config ) {
   if( gVid != NULL ) {
        printf("Device has been opened!!\n");
        return -1;
    }
    gVid = ar2VideoOpen( config );
    if( gVid == NULL ) return -1;
}

int arVideoClose( void ) {
	return ar2VideoClose(gVid);
}

int arVideoDispOption( void ) {
   return 0;
}

int arVideoInqSize( int *x, int *y ) {
	ar2VideoInqSize(gVid,x,y);
	return 0;
}

ARUint8 *arVideoGetImage( void ) {
   return ar2VideoGetImage(gVid);  // address of your image data
}

int arVideoCapStart( void ) {
	ar2VideoCapStart(gVid);
	return 0;
}

int arVideoCapStop( void ) {
	ar2VideoCapStop(gVid);
	return 0;
}

int arVideoCapNext( void ) {
	ar2VideoCapNext(gVid);
	return 0;
}

int arVideoInqDepthSize(int *x, int *y) {
    ar2VideoInqDepthSize(gVid, x, y);
    return 0;
}

ARUint32* arVideoGetDepthImage() {
    return gVid->depthFrontBuffer;
}

/*---------------------------------------------------------------------------*/


void *openni_threadfunc(void *arg) {
    printf("threadfunction started\n");
    while (gVid->streaming) {
        gVid->context->WaitAndUpdateAll();

        printf("copying rgb frame\n");
        /* copy rgb to backbuffer */
        const XnRGB24Pixel *rgb = gVid->imageGen->GetRGB24ImageMap();
        memcpy(gVid->backBuffer, rgb, gVid->rgbBuffer_size);
       
        //switch buffers 
        ARUint8 *hbuf = gVid->backBuffer;
        gVid->backBuffer = gVid->frontBuffer;
        gVid->frontBuffer = hbuf;

    }
    pthread_exit(NULL);
}

/*
void rgb_cb(freenect_device *dev, freenect_pixel *rgb, uint32_t timestamp) {
    ARUint8 *hbuf;    
    if (!gVid->backBuffer) return;

    pthread_mutex_lock(&gVid->videoBuffer_mutex);

    memcpy(gVid->backBuffer, rgb, gVid->rgbBuffer_size);
    hbuf = gVid->backBuffer;
    gVid->backBuffer = gVid->frontBuffer;
    gVid->frontBuffer = hbuf;

    pthread_mutex_unlock(&gVid->videoBuffer_mutex);
}


void depth_cb(freenect_device *dev, freenect_depth *depth, uint32_t timestamp) {
    int i;

    for (i=0; i<gVid->depthWidth*gVid->depthHeight; i++) {
        gVid->depthBuffer[i] = depth[i];
    }
}
*/

AR2VideoParamT* ar2VideoOpen(char *config_in ) {

	AR2VideoParamT *vid = 0;
	char *config;

	/* init ART structure */
    arMalloc( vid, AR2VideoParamT, 1 );

    /* allocate the buffer */

    vid->width = 640;
    vid->height = 480;
    vid->rgbBuffer_size = vid->width * vid->height * 3 * sizeof(ARUint8);
    vid->backBuffer = (ARUint8*) malloc(vid->rgbBuffer_size);
    vid->frontBuffer = (ARUint8*) malloc(vid->rgbBuffer_size);

    vid->depthWidth = 640;
    vid->depthHeight = 480;
    vid->depthBuffer_size = vid->width * vid->height * sizeof(ARUint32);
    vid->depthBackBuffer = (ARUint32*) malloc(vid->depthBuffer_size);
    vid->depthFrontBuffer = (ARUint32*) malloc(vid->depthBuffer_size);

    vid->streaming = FALSE;
		
	/* report the current version and features */
	printf ("libARvideo: openni init\n");

    /* openni */
    XnStatus nRetVal = XN_STATUS_OK;
    vid->context = new xn::Context();

    /* init the nodes from the XML config file */
    nRetVal = vid->context->InitFromXmlFile(XML_CONFIG, NULL);


    pthread_mutex_init(&vid->videoBuffer_mutex, NULL);
	
	/* return the video handle */
    gVid = vid;
	return vid;
}


int ar2VideoClose(AR2VideoParamT *vid) {
    vid->streaming = FALSE;    
	return 0;
}


ARUint8* ar2VideoGetImage(AR2VideoParamT *vid) {
    ARUint8 *tb;
	/* just return the bare video buffer */   
    pthread_mutex_lock(&vid->videoBuffer_mutex);
    tb = vid->frontBuffer;
    pthread_mutex_unlock(&vid->videoBuffer_mutex);
	return tb;
}


int ar2VideoCapStart(AR2VideoParamT *vid) {
    printf("fooooooooO\n");
    vid->streaming = TRUE;
    if ( pthread_create(&(vid->openni_event_thread), NULL, openni_threadfunc, NULL) ) {
        printf("libARVideo: creating thread FAILED!\n");
    }
    return 0;
}


int ar2VideoCapStop(AR2VideoParamT *vid) {
	/* stop pipeline */
	printf("libARVideo: can't stop streaming");
}


int ar2VideoCapNext(AR2VideoParamT *vid) {
	return TRUE;
}


int ar2VideoInqSize(AR2VideoParamT *vid, int *x, int *y ) {
   *x = vid->width; // width of your static image
   *y = vid->height; // height of your static image
}


int ar2VideoInqDepthSize(AR2VideoParamT *vid, int *x, int *y ) {
    *x = vid->depthWidth;
    *y = vid->depthHeight;
}

ARUint32 *ar2VideoGetDepthImage(AR2VideoParamT* vid) {
    return vid->depthFrontBuffer;
}

