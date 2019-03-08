#ifndef VIDEOSURFACEPRIVATE_H
#define VIDEOSURFACEPRIVATE_H
#include <QSet>
#include <gst/gst.h>
#include "videosurface.h"
#include "VideoItem.h"
class VideoItem;
class VideoSurfacePrivate {
public:
    VideoSurfacePrivate(): videosink(NULL){}
    QSet<VideoItem *> items;
    GstElement* videosink;
};



#endif // VIDEOSURFACEPRIVATE_H
