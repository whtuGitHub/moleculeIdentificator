#ifndef EDITORSCENE_H
#define EDITORSCENE_H

#include <QGraphicsScene>
#include <QtCore>
#include <QFileDialog>
#include "atomgraphicitem.h"
#include "bondgraphicsitem.h"
#include "ImageRecognition/bonddetector.h"
#include "ImageRecognition/atomfinder.h"
#include "ImageRecognition/moleculegrabber.h"
#include "imagecapture.h"

class EditorScene: public QGraphicsScene
{
    Q_OBJECT
public:
    enum Mode {add,edit,remove};
    EditorScene();
    ~EditorScene();
    QVector<AtomGraphicItem*> getAtoms();
    QVector<BondGraphicsItem*> getBonds();
    std::vector<std::vector<int> > getConnectivityMatrix();
    std::vector<Atom *> getAtomVector();

public slots:
    void setMyModeAdd(bool toggled);
    void setMyModeEdit(bool toggled);
    void setMyModeRemove(bool toggled);
    void setElement(QString element);
    void setBondOrder(int);
    void drawSMILE(QString);

    void readFromImage(QImage img=QImage(0,0,QImage::Format_RGB32));

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;
//    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;

private:
    void addAtom(QPointF pos);
    void addBond(AtomGraphicItem *atom1, AtomGraphicItem *atom2);
    void addBond(AtomGraphicItem *atom1, AtomGraphicItem *atom2, int bondOrder);


    void removeAtom(AtomGraphicItem *atom);
    void removeBond(BondGraphicsItem *bond);
    void editBond();
    AtomGraphicItem* lastAtom;
    AtomGraphicItem* atomAt(QPointF pos);

    QString atomicSymbol;
    int bondOrder;
    int charge;
    int atomID;

    void insertAtom(AtomGraphicItem* atom);
    bool mergeNearAtoms(AtomGraphicItem* atom,int dist =20);
    void mergeAtoms(AtomGraphicItem* atom, AtomGraphicItem* atom2, bool ord=false);
    bool mergeBonds(BondGraphicsItem* bond, BondGraphicsItem* bond2);
    void mergeNearBonds(BondGraphicsItem* bond);
    void mergeNearBonds();


    //QVector<QVector <int> >
    QVector<BondGraphicsItem*>bonds;
    QVector<AtomGraphicItem*> atoms;

    int myMode;

    void clean();
    void removeAll();
    void combBonds(qreal minThresh=20, qreal maxThresh=50);

    QPointF* intersectingBonds(BondGraphicsItem* b1, BondGraphicsItem* b2, qreal minThresh=20, qreal maxThresh=50);

    std::vector<std::array<int, 4> > mergeLines(std::vector<std::array<int, 4> > );
    QVector<BondGraphicsItem*> mergeLines(QVector<BondGraphicsItem*>);
    void mergeLines(BondGraphicsItem* bond);

    QLineF combineLines(QLineF l1,QLineF l2);
    qreal lineDistance(QLineF l1,QLineF l2);
    qreal pointLineDist(QLineF v, QPointF p );



};

#endif // EDITORSCENE_H
