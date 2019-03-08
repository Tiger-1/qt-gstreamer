import QtQuick 2.9
import QtQuick.Window 2.2
import VideoItem 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    VideoItem{
        id: video

        width: 100
        height: 100
        surface: videoSurface1
        z: 3
    }

    VideoItem{
        id: video1
        x: 100
        y: 100
        width: 100
        height: 100
        surface: videoSurface2
        z: 3
    }
}
