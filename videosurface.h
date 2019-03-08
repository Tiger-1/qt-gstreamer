#ifndef VIDEOSURFACE_H
#define VIDEOSURFACE_H
#include <QSet>
#include <gst/gst.h>
#include <QtCore/QObject>
#include <QtQuick/QQuickItem>
#include <QtCore/QPointer>
#include <QtQuick/QSGNode>
#include <QtQuick/QSGFlatColorMaterial>
#include "videosurfaceprivate.h"
#include "videosurface.h"


class VideoSurface: public QObject{
    Q_OBJECT
    Q_DISABLE_COPY(VideoSurface)
public:
    explicit VideoSurface(QObject *parent = 0);
    virtual ~VideoSurface();
    GstElement *videoSink();
    void onUpdate();
    static void onUpdateThunk(GstElement* sink, gpointer data);
    VideoSurfacePrivate *const d;
};

#endif // VIDEOSURFACE_H
