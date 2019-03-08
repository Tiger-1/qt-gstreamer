#ifndef VIDEOITEM_H
#define VIDEOITEM_H
#include <gst/gst.h>
#include <QSet>
#include <QtCore/QObject>
#include <QtQuick/QQuickItem>
#include <QtCore/QPointer>
#include <QtQuick/QSGNode>
#include <QtQuick/QSGFlatColorMaterial>
#include "VideoItem.h"
#include "videosurface.h"

class VideoSurface;
class VideoItem: public QQuickItem{
    Q_OBJECT
    Q_PROPERTY(VideoSurface* surface READ surface WRITE setSurface)
public:
    explicit VideoItem(QQuickItem *parent = 0);
    virtual ~VideoItem();

    VideoSurface *surface();
    void setSurface(VideoSurface *surface);
    virtual QSGNode* updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *UpdatePaintNodeData);
    struct Private;
    Private* const d;
};

#endif // VIDEOITEM_H
