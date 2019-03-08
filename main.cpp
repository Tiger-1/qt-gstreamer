#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml/QQmlContext>
#include <QtQml/QQmlEngine>
#include <QApplication>
#include <QSet>
#include <gst/gst.h>
#include <QtCore/QObject>
#include <QtQuick/QQuickItem>
#include <QtCore/QPointer>
#include <QtQuick/QSGNode>
#include <QtQuick/QSGFlatColorMaterial>
#include <VideoItem.h>
#include <videosurface.h>


int main(int argc, char *argv[])
{
    gst_init(NULL, NULL);
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    qmlRegisterType<VideoItem>("VideoItem", 1, 0,"VideoItem");

    GstElement *pipeline = gst_pipeline_new(NULL);
    GstElement *testsrc = gst_element_factory_make("videotestsrc", NULL);
    GstElement *videoconvert = gst_element_factory_make("videoconvert", NULL);
    GstElement *videosink = gst_element_factory_make("qt5videosink", NULL);
    GstElement *testsrc1 = gst_element_factory_make("videotestsrc", NULL);
    GstElement *videoconvert1 = gst_element_factory_make("videoconvert", NULL);
    GstElement *videosink1 = gst_element_factory_make("qt5videosink", NULL);
    QQmlApplicationEngine engine;

//    QGLContext *gl;
//    QGLContext::create(gl);
//    gl->currentContext();
    //engine.rootContext()->setContextProperty((QString)QGLContext::currentContext(),NULL);

//    g_object_set(G_OBJECT(videosink),"glcontext",(GValue *)QGLContext::currentContext(), NULL);
//    gl->doneCurrent();
    VideoSurface *surface = new VideoSurface;
    videosink = surface->videoSink();
    engine.rootContext()->setContextProperty(QLatin1String("videoSurface1"), surface);
    VideoSurface *surface1 = new VideoSurface;
    videosink1 = surface1->videoSink();
    engine.rootContext()->setContextProperty(QLatin1String("videoSurface2"), surface1);

    gst_bin_add_many(GST_BIN(pipeline), testsrc, videoconvert, videosink, testsrc1, videoconvert1, videosink1, NULL);
    gst_element_link_many(testsrc, videoconvert, videosink, NULL);
    gst_element_link_many(testsrc1, videoconvert1, videosink1, NULL);


    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
    gst_element_set_state(pipeline, GST_STATE_PLAYING);
    return app.exec();
}
