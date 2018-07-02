#include "pyr_window.h"
//#include <ui_Pyr_window.h>
#include <QtWidgets>
#include <qhash.h>
#include <qlist.h>

PyramidalWindow::PyramidalWindow(QWidget *parent) : QWidget(parent) // , ui(new Ui::PyramidalWindow)
{
    configWindow();
    configImages();
    configPictureLabel();
    configSelectLevelMenu(selected);
    configSelectPictureMenu();
    configMenuBar();
    configScrollArea();
    configInputDepth();
    getPyramid(selected, depth);

    sizeLabel = new QLabel(this);
    sizeLabel->setGeometry(200, 0, 100, 25);//(selectPictureMenu->width() + selectLevelMenu->width() + 5, 0, 50, 25);
    sizeLabel->setText("Size: " + QString::number(selected.width()) + "x" + QString::number(selected.height()));

    stretch = new QCheckBox(this);
    stretch->setGeometry(300, 0, 100, 25);
    stretch->setText("Stretch");
    QObject::connect(stretch, SIGNAL(stateChanged(int)), this, SLOT(stretchStateChanged()));

    soapLevel = new QSlider(Qt::Horizontal, this);
    soapLevel->setGeometry(570, 75, 100, 10);
    soapLevel->setStyleSheet("background-color: rgb(255, 179, 104);");
   // QObject::connect(soapLevel, SIGNAL(valueChanged(int)), this, SLOT(sliderMoved()));
    soapLevel->setMaximum(100);
    soapLevel->setMinimum(10);
    soapLevel->setTickPosition(QSlider::TicksBelow);
    soapLevel->setTickInterval(20);
    soapLevel->setDisabled(true);
  //  soapLevel->setValue(level * 10);

    levelLabel = new QLabel(this);
    levelLabel->setGeometry(680, 75, 100, 10);
    levelLabel->setText(QString::number(level));

    //QObject::connect(m1, SIGNAL(triggered()), this, SLOT(menu1()));
    //QObject::connect(m2, SIGNAL(triggered()), this, SLOT(menu1()));

    manual = new QLabel(this);
    manual->setGeometry(570, 95, 250, 500);
    manual->setText("<b>HOW TO USE</b><br><br>1) Click \"Select picture\" to choose an image. <br><br>2) Input a number from 2 to 9 to <br>point a height of the pyramid.<br>It will set automatically,<br>rechoose level after inputting.<br>(It is 5 by default). <br><br>3) Click \"Select level\" to set the layer. <br><br>4) If you want to smooth the picture, <br>push \"stretch\" and enjoy big <br>soaped image.<br><br>It was nice to work, have a good time :)");
}

PyramidalWindow::~PyramidalWindow()
{
    //delete ui;
}

void PyramidalWindow::configPictureLabel()
{
    pictureLabel = new QLabel(this);
    pictureLabel->setGeometry(10, 25, white.width(), white.height());
    pictureLabel->setPixmap(selected);
    pictureLabel->setBackgroundRole(QPalette::Base);
}

void PyramidalWindow::configSelectPictureMenu()
{
    selectPictureMenu = new QMenu("Select image");
    action1Puzzle = selectPictureMenu->addAction(puzzle, "&puzzle", this, SLOT(pictureSelected()));
    action2Red = selectPictureMenu->addAction(red, "&red", this, SLOT(pictureSelected()));
    action3Cyan = selectPictureMenu->addAction(cyan, "&cyan", this, SLOT(pictureSelected()));
    action4Violet = selectPictureMenu->addAction(violet, "&violet", this, SLOT(pictureSelected()));
    action5FromFile = selectPictureMenu->addAction(white, "&white", this, SLOT(pictureSelected()));
}

void PyramidalWindow::configSelectLevelMenu(QPixmap picture)
{
    selectLevelMenu = new QMenu("Select level");
    for(int i = 1; i <= depth; i++){
        selectLevelMenu->addAction(picture, QString::number(i), this, SLOT(levelChanged()));
    }
}

void PyramidalWindow::configWindow()
{
    this->setStyleSheet("background-color: rgb(175, 134, 100)");
    resize(800, 600);
    setWindowTitle("Пирамида изображений");
    //setAttribute(Qt::WA_DeleteOnClose);
}

void PyramidalWindow::configScrollArea()
{
    scrollArea = new QScrollArea(this);
    scrollArea->setGeometry(10, 25, 550, 550);
    scrollArea->setWidget(pictureLabel);
}

void PyramidalWindow::configMenuBar()
{
    menuBar.addMenu(selectPictureMenu);
    menuBar.addMenu(selectLevelMenu);
    menuBar.setParent(this);
    menuBar.show();
}

void PyramidalWindow::configImages()
{
    white = QPixmap(":res/images/white.png");
    puzzle = QPixmap(":res/images/puzzle.png");
    fromFile = QPixmap(":res/images/point.png");
    red = QPixmap(":res/images/red.png");
    cyan = QPixmap(":res/images/cyan.png");
    violet = QPixmap(":res/images/violet.png");
    selected = white;
}

void PyramidalWindow::configInputDepth()
{
    QLabel *input = new QLabel(this);
    input->setText("Input depth (2-9):");
    input->setGeometry(570, 25, 60, 20);
    inputDepth = new QLineEdit;
    inputDepth->setGeometry(570, 45, 60, 20);
    inputDepth->setParent(this);
    QRegExp rx("(\\d)");
    QValidator *v = new QRegExpValidator(rx, this);
    inputDepth->setValidator(v);
    connect(inputDepth, SIGNAL(textChanged(const QString &)), this, SLOT(depthChanged()));
}

void PyramidalWindow::imageProcessing(QPixmap picture, int depth)
{
    pictureLabel->setPixmap(picture);
    pictureLabel->setGeometry(10, 25, picture.width(), picture.height());
    getPyramid(picture, depth);
}

void PyramidalWindow::getPyramid(QPixmap picture, int depth)
{
    imageSpector.clear();
    for (int i = 0; i <= depth; i++){
        imageSpector.push_back(picture);
        picture = picture.scaled(picture.width() / 2, picture.height() / 2);
    }
}

void PyramidalWindow::pictureSelected()
{
    QAction *action = (QAction*)sender();
    selected = QPixmap(":res/images/" + action->iconText() + ".png");
    imageSpector.clear();
    imageProcessing(selected, depth);
    foreach(QAction *ac, selectLevelMenu->actions())
    {
         ac->setIcon(selected);
    }
    sizeLabel->setText("Size: " + QString::number(selected.width()) + "x" + QString::number(selected.height()));
}

void PyramidalWindow::depthChanged()
{
    depth = inputDepth->text().toInt();
    getPyramid(selected, depth);
    selectLevelMenu->clear();
    for(int i = 1; i <= depth; i++){
        selectLevelMenu->addAction(selected, QString::number(i), this, SLOT(levelChanged()));
    }
}

void PyramidalWindow::levelChanged()
{
    QAction *action = (QAction*)sender(); // лучше использовать QSignalMapper
    if (action->text().toInt() > 0 && action->text().toInt() <= depth) {
        level = action->text().toInt();
        pictureLabel->setPixmap(imageSpector[level - 1]);   // / 10 - 1]);
        sizeLabel->setText("Size: " + QString::number(pictureLabel->pixmap()->width()) + "x" + QString::number(pictureLabel->pixmap()->height()));
        if(stretch->isChecked()){
            pictureLabel->setPixmap(pictureLabel->pixmap()->scaled(pictureLabel->pixmap()->width() * pow(2, level - 1), pictureLabel->pixmap()->height() * pow(2, level - 1)));
        }
    }
    //soapLevel->setValue(level);
    levelLabel->setText(QString::number(level));
}

void PyramidalWindow::stretchStateChanged()
{
    if(stretch->isChecked()){
        pictureLabel->setPixmap(pictureLabel->pixmap()->scaled(pictureLabel->pixmap()->width() * pow(2, level - 1), pictureLabel->pixmap()->height() * pow(2, level - 1)));
    } else {
        pictureLabel->setPixmap(imageSpector[level - 1]);
    }
}

//void PyramidalWindow::sliderMoved()
//{
//    level = (double)soapLevel->value() / 10;
//    pictureLabel->setPixmap(selected.scaled(selected.width() / level, selected.height() / level));
//    if(stretch->isChecked()){
//        pictureLabel->setPixmap(pictureLabel->pixmap()->scaled(pictureLabel->pixmap()->width() * pow(2, level - 1), pictureLabel->pixmap()->height() * pow(2, level - 1)));
//    }
//}
