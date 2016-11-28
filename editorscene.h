#ifndef EDITORSCENE_H
#define EDITORSCENE_H

#include <QGraphicsScene>
#include <QtCore>
#include <QFileDialog>
#include "atomgraphicitem.h"
#include "bondgraphicsitem.h"
#include "ImageRecognition/bonddetector.h"
#include "ImageRecognition/blobdetector.h"
#include "ImageRecognition/atomfinder.h"

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

    void readFromImage();

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
    void mergeNearAtoms(AtomGraphicItem* atom);
    void mergeAtoms(AtomGraphicItem* atom,AtomGraphicItem* atom2);


    //QVector<QVector <int> >
    QVector<BondGraphicsItem*>bonds;
    QVector<AtomGraphicItem*> atoms;

    int myMode;

    void clean();
    void removeAll();

};

#endif // EDITORSCENE_H
