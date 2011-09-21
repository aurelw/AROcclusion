#ifdef _WIN32
#include <windows.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#ifndef __APPLE__
#include <GL/gl.h>
#include <GL/glut.h>
#else
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#endif
#include <AR/gsub.h>
#include <AR/video.h>
#include <AR/param.h>
#include <AR/ar.h>

//
// Camera configuration.
//
#ifdef _WIN32
char			*vconf = "Data\\WDM_camera_flipV.xml";
#else
char			*vconf = "v4l2src device=/dev/video0 ! video/x-raw-rgb, framerate=30/1, width=640, height=480 ! ffmpegcolorspace ! identity name=artoolkit ! fakesink sync=true";

#endif

int             xsize, ysize;
int             thresh = 100;
int             count = 0;

char           *cparam_name    = "Data/camera_para.dat";
ARParam         cparam;

char           *patt_name      = "Data/patt.hiro";
int             patt_id;
double          patt_width     = 80.0;
double          patt_center[2] = {0.0, 0.0};
double          patt_trans[3][4];

/* calibration */
float zbuffer_samples[512];
float cZbuffer = 0.0;
int kinectDepth_samples[512];
int cKinectDepth = 0;
int nsamples = 0;
ARUint8* gImage;

float kinectZbuffer[640*480];

static void   init(void);
static void   cleanup(void);
static void   keyEvent( unsigned char key, int x, int y);
static void   mainLoop(void);
static void   draw(ARUint8 *image, ARUint32 *depthBuffer);
static void   printCalibrationData();
static void   convertDepthToZ(ARUint32 *depthBuffer);

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	init();
    printf("start cap...\n");
    printf("Move the marker to the center of the screen.\n");
    printf("Press 's' to take a sample.\n");
    printf("Take several samples for different distances.\n");
    arVideoCapStart();
    argMainLoop( NULL, keyEvent, mainLoop );
	return (0);
}

static void   keyEvent( unsigned char key, int x, int y)
{
    /* quit if the ESC key is pressed */
    if( key == 0x1b ) {
        printf("*** %f (frame/sec)\n", (double)count/arUtilTimer());
        cleanup();
        printCalibrationData();
        exit(0);
    /* take a calibration sample */
    } else if (key == 0x73) {
        if (cZbuffer != 1.0 && cKinectDepth != 0) {
            zbuffer_samples[nsamples] = cZbuffer;
            kinectDepth_samples[nsamples] = cKinectDepth;
        }
        nsamples++;
    }
}

/* main loop */
static void mainLoop(void)
{
    ARUint8         *dataPtr;
    ARUint32        *depthBuffer;
    ARMarkerInfo    *marker_info;
    int             marker_num;
    int             j, k;

    /* grab a vide frame */
    if( (dataPtr = (ARUint8 *)arVideoGetImage()) == NULL ) {
        arUtilSleep(2);
        return;
    }
    if( count == 0 ) arUtilTimerReset();
    count++;
    gImage = dataPtr;

    argDrawMode2D();
    argDispImage( dataPtr, 0,0 );

    /* grab depth image */
    depthBuffer = arVideoGetDepthImage();
    convertDepthToZ(depthBuffer);

    /* detect the markers in the video frame */
    if( arDetectMarker(dataPtr, thresh, &marker_info, &marker_num) < 0 ) {
        cleanup();
        exit(0);
    }

    arVideoCapNext();

    /* check for object visibility */
    k = -1;
    for( j = 0; j < marker_num; j++ ) {
        if( patt_id == marker_info[j].id ) {
            if( k == -1 ) k = j;
            else if( marker_info[k].cf < marker_info[j].cf ) k = j;
        }
    }
    if( k == -1 ) {
        argSwapBuffers();
        return;
    }

    /* get the transformation between the marker and the real camera */
    arGetTransMat(&marker_info[k], patt_center, patt_width, patt_trans);

    draw(dataPtr, depthBuffer);

    argSwapBuffers();
}

static void init( void )
{
    ARParam  wparam;
	
    /* open the video path */
    if( arVideoOpen( vconf ) < 0 ) exit(0);
    /* find the size of the window */
    if( arVideoInqSize(&xsize, &ysize) < 0 ) exit(0);
    printf("Image size (x,y) = (%d,%d)\n", xsize, ysize);

    /* set the initial camera parameters */
    if( arParamLoad(cparam_name, 1, &wparam) < 0 ) {
        printf("Camera parameter load error !!\n");
        exit(0);
    }
    arParamChangeSize( &wparam, xsize, ysize, &cparam );
    arInitCparam( &cparam );
    printf("*** Camera Parameter ***\n");
    arParamDisp( &cparam );

    if( (patt_id=arLoadPatt(patt_name)) < 0 ) {
        printf("pattern load error !!\n");
        exit(0);
    }

    /* open the graphics window */
    argInit( &cparam, 1.0, 0, 0, 0, 0 );
}

/* cleanup function called when program exits */
static void cleanup(void)
{
    arVideoCapStop();
    arVideoClose();
    argCleanup();
}

static void draw(ARUint8 *image, ARUint32 *depthBuffer)
{
    double    gl_para[16];
    GLfloat   mat_ambient[]     = {0.0, 0.0, 1.0, 1.0};
    GLfloat   mat_flash[]       = {0.0, 0.0, 1.0, 1.0};
    GLfloat   mat_flash_shiny[] = {50.0};
    GLfloat   light_position[]  = {100.0,-200.0,200.0,0.0};
    GLfloat   ambi[]            = {0.1, 0.1, 0.1, 0.1};
    GLfloat   lightZeroColor[]  = {0.9, 0.9, 0.9, 0.1};

    argDrawMode3D();
    argDraw3dCamera( 0, 0 );
    glClearDepth( 1.0 );
    glClear(GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    /* load the camera transformation matrix */
    argConvGlpara(patt_trans, gl_para);
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixd( gl_para );

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambi);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightZeroColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_flash);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_flash_shiny);	
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);

    glMatrixMode(GL_MODELVIEW);
    glTranslatef( 0.0, 0.0, -40.0 );
    glutSolidCube(80.0);

    glDisable( GL_LIGHTING );

    /* draw a "hud" */
    glLoadIdentity();
    glDisable( GL_LIGHTING );
    glDisable(GL_DEPTH_TEST); 
    glTranslatef( 0.0, 0.0, 400.0 );
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POINTS);
        glVertex3f(0.0, 0.0, 0.0);
    glEnd();
    glEnable(GL_DEPTH_TEST);

    /* read depth data */
    glReadPixels(320, 240, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &cZbuffer); 
    cKinectDepth = * (depthBuffer + 640*240 + 320);
    printf("depth [zbuffer]:%f  [kinect]:%i\n", cZbuffer, cKinectDepth); 
}


static void printCalibrationData() {
    int i;

    printf("kinectD = [");
    for (i=0; i<nsamples; i++) {
       printf("%i,", kinectDepth_samples[i] );
    }
    printf("]\n");

    printf("zbufferD = [");
    for (i=0; i<nsamples; i++) {
       printf("%f,", zbuffer_samples[i] );
    }
    printf("]\n");
}


static void convertDepthToZ(ARUint32 *depthBuffer) {
    int  x, y, xres, yres;
    double z, kd;
    int i = 0;
    arVideoInqDepthSize(&xres, &yres);
    for (y=yres; y>0; y--) {
        for (x=0; x<xres; x++) {
            kd = depthBuffer[y*xres+x];
            if (kd == 0) {
                z = 0.999;
            } else if (kd < 470) {
                z = 0.7;
            } else if (kd > 2400) {
                z = 0.999;
            } else {
                // compute from fitted polynome
                //z = 2.5517e-1 * kd*kd*kd - 1.2510e-07 * kd*kd + 2.1150e-04 * kd + 8.6259e-01 ; 
                z = -2.4801e-08 * kd*kd + 9.6423e-05 * kd + 9.0128e-01;
                //z = 0.965;
            }
            kinectZbuffer[i++] = (float) z;
        }        
    }
}
