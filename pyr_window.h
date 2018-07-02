#ifndef PYR_WINDOW_H
#define PYR_WINDOW_H

#include "selectpictureaction.h"

#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QMenuBar>
#include <QScrollArea>
#include <QTextEdit>
#include <QWidget>
#include <QtGui>
#include <ui_Pyr_window.h>

namespace Ui{
class PyramidalWindow;
}

class PyramidalWindow : public QWidget
{
    Q_OBJECT

public:
    explicit PyramidalWindow(QWidget *parent = 0);
    ~PyramidalWindow();

private:
    //Ui::PyramidalWindow *ui;
    int depth = 5;
    double level = 1;

    QLabel      *pictureLabel;
    QLabel      *sizeLabel;
    QLabel      *levelLabel;
    QLabel      *manual;
    QMenuBar    menuBar;
    QMenu       *selectPictureMenu;
    QMenu       *selectLevelMenu;
    QScrollArea *scrollArea;
    QLineEdit   *inputDepth;
    QCheckBox   *stretch;
    QSlider     *soapLevel;

    QAction     *action1Puzzle;
    QAction     *action2Red;
    QAction     *action3Cyan;
    QAction     *action4Violet;
    QAction     *action5FromFile;

    QPixmap white;
    QPixmap puzzle;
    QPixmap red;
    QPixmap cyan;
    QPixmap violet;
    QPixmap fromFile;
    QPixmap selected;

    QVector<QPixmap> imageSpector;

    void configPictureLabel();
    void configMenuBar();
    void configSelectPictureMenu();
    void configSelectLevelMenu(QPixmap);
    void configWindow();
    void configScrollArea();
    void configImages();
    void configInputDepth();
    void imageProcessing(QPixmap, int);
    void getPyramid(QPixmap, int);

public slots:
    void pictureSelected();
    void depthChanged();
    void levelChanged();
    void stretchStateChanged();
  //  void sliderMoved();
};    

#endif // PYR_WINDOW_H
