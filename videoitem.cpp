#include "VideoItem.h"

struct VideoItem::Private{
    QPointer<VideoSurface> surface;
    bool surfaceDirty;
    QRectF targetArea;
};

VideoItem::VideoItem(QQuickItem *parent): QQuickItem(parent), d(new Private){
    d->surfaceDirty = true;
    setFlag(QQuickItem::ItemHasContents, true);
}

VideoItem::~VideoItem(){
    setSurface(0);
    delete d;
}

VideoSurface *VideoItem::surface(){
    return d->surface.data();
}

void VideoItem::setSurface(VideoSurface *surface)
{
    if(d->surface){
        d->surface.data()->d->items.remove(this);
    }
    d->surface = surface;
    d->surfaceDirty = true;

    if(d->surface){
        d->surface.data()->d->items.insert(this);
    }
}

QSGNode* VideoItem::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *UpdatePaintNodeData){

    Q_UNUSED(UpdatePaintNodeData);
    QRectF r = boundingRect();
    QSGNode* newNode = 0;

    if(d->surfaceDirty){
        delete oldNode;
        oldNode = 0;
        d->surfaceDirty = false;
    }

    if(!d->surface || d->surface.data()->d->videosink == NULL ){
        if(!oldNode){
            QSGFlatColorMaterial *material = new QSGFlatColorMaterial;
            material->setColor(Qt::black);
            QSGGeometryNode *node = new QSGGeometryNode;
            node->setMaterial(material);
            node->setFlag(QSGNode::OwnsMaterial);
            node->setFlag(QSGNode::OwnsGeometry);
            newNode = node;
            d->targetArea = QRectF();
        }else{
            newNode = oldNode;
        }
        if( r != d->targetArea ){
            QSGGeometry *geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 4);
            geometry->vertexDataAsPoint2D()[0].set(r.x(),r.y());
            geometry->vertexDataAsPoint2D()[1].set(r.x(), r.height());
            geometry->vertexDataAsPoint2D()[2].set(r.width(), r.y());
            geometry->vertexDataAsPoint2D()[3].set(r.width(), r.height());
            QSGGeometryNode *node = static_cast<QSGGeometryNode*>(newNode);
            node->setGeometry(geometry);
            d->targetArea = r;
            }
        } else {
            g_signal_emit_by_name(d->surface.data()->d->videosink,"update-node", (void *)oldNode, r.x(), r.y(), r.width(), r.height(), (void**)&newNode);
        }

        return newNode;
}


