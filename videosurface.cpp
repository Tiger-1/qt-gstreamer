#include "videosurface.h"

VideoSurface::VideoSurface(QObject *parent): QObject(parent), d(new VideoSurfacePrivate){

}

VideoSurface:: ~VideoSurface(){
    delete d;
}
void VideoSurface::onUpdate(){
    Q_FOREACH(QQuickItem *item, d->items){
        item->update();
    }
}
void VideoSurface::onUpdateThunk(GstElement *sink, gpointer data){
    Q_UNUSED(sink);
    VideoSurface *pThis = (VideoSurface *)data;
    pThis->onUpdate();
}
GstElement *VideoSurface::videoSink(){
    d->videosink = gst_element_factory_make("qtquick2videosink", NULL);
    g_signal_connect(d->videosink,"update",G_CALLBACK(onUpdateThunk),(void *)this);
    return d->videosink;
}


