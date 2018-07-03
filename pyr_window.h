#ifndef PYR_WINDOW_H
#define PYR_WINDOW_H

#include "filedata.h"

#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QListView>
#include <QListWidget>
#include <QMenuBar>
#include <QPushButton>
#include <QScrollArea>
#include <QTextEdit>
#include <QWidget>
#include <QtGui>

class PyramidalWindow : public QWidget
{
    Q_OBJECT

public:
    explicit PyramidalWindow(QWidget *parent = 0);

private:
    int layer; // номер отображаемого слоя
    int maxLayer; // count of max decreas
    double qDecr; // coeffitient of decreas
    int diag; // диагональ

    // компоненты на форме

    QLabel      *pictureLabel;
    QLabel      *sizeLabel;
    QLabel      *levelLabel;
    QLabel      *manual;
    QLabel      *coeff;
    QMenuBar    menuBar;
    QMenu       *selectPictureMenu;
    QMenu       *selectLevelMenu;
    QScrollArea *scrollArea;
    QLineEdit   *inputQdecr;
    QCheckBox   *stretch;
    QSlider     *soapLevel;
    QComboBox   *openedFiles;
    QPushButton *saveButton;

    // пункты меню выбора изображения

    QAction     *action1Puzzle;
    QAction     *action2Red;
    QAction     *action3Cyan;
    QAction     *action4Violet;
    QAction     *action5FromFile;

    // начальные изображения
    QPixmap white;
    QPixmap puzzle;
    QPixmap red;
    QPixmap cyan;
    QPixmap violet;
    QPixmap fromFile;
    QPixmap selected; // рабочее изображение
    QPixmap redusedPicture; // selected after decreas

    QVector<MyFileData> files;

    int getMaxLayer();
    bool uniq(QString file);

    // установка внешнего вида формы

    void configPictureLabel();
    void configMenuBar();
    void configSelectPictureMenu();
    void configSelectLevelMenu();
    void configWindow();
    void configScrollArea();
    void configImages();
    void configInputLayer();
    void configSizeLabel();
    void configCheckBox();
    void configSlider();
    void configLevelLabel();
    void configManual();
    void configOpenedFiles();
    void configSaveButton();
    void configQdecrEdit();

    void addToList(QString);
    void init(); // задание значений по умолчанию

    void imageProcessing(QPixmap, int); // работа с изображением
    void rewriteLevelMenu();
    void reduce(QPixmap);
    void redrawSlider();
    // void getPyramid(QPixmap, int); // получение спектра слоев

public slots:
    void pictureSelected(); // обработка нажатия на пункт меню выбора картинки
    //void layerEditChanged(); // когда был выбран другой слой - manually by testedit!
    void menuLevelChanged(); // когда был выбран другой слой - by menu!
    void stretchStateChanged(); // изменилось состояние растянуто/не растянуто
    void sliderMoved(); // обработка движений бегунка
    void fileChoosen();
    void addPictureFromFile();
    void savePicture();
    void qdecrChanged();
};    

#endif // PYR_WINDOW_H
