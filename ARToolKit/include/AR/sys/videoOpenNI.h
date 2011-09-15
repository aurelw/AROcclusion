/*
 * Video capture module for OpenNI
 * 
 * (c) Copyrights 2011 Aurel Wildfellner
 * 
 * Licensed under the terms of the GPL
 *
 */
#ifndef AR_VIDEO_OPENNI_H
#define AR_VIDEO_OPENNI_H

#ifdef  __cplusplus
extern "C" {
#endif

#include <AR/config.h>
#include <AR/ar.h>

typedef struct _AR2VideoParamT AR2VideoParamT;

#ifdef  __cplusplus
}
#endif

/* extended API for depth access */
AR_DLL_API  int             arVideoInqDepthSize(int *x, int *y);
AR_DLL_API  int             ar2VideoInqDepthSize(AR2VideoParamT *vid, int *x, int *y);

AR_DLL_API  ARUint32*            arVideoGetDepthImage(void);
AR_DLL_API  ARUint32*            ar2VideoGetDepthImage(AR2VideoParamT *vid);


#endif

