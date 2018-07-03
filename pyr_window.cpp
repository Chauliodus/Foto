#include "pyr_window.h"
#include <QtWidgets>
#include <qhash.h>
#include <qlist.h>

PyramidalWindow::PyramidalWindow(QWidget *parent) : QWidget(parent)
{
    layer = 1;
    qDecr = 2;
    redusedPicture = QPixmap();

    configWindow();
    configImages();

    selected = white;

    configPictureLabel();

    pictureLabel->setPixmap(selected);

    configSelectLevelMenu();
    configSelectPictureMenu();
    configMenuBar();
    configScrollArea();
    configSizeLabel();
    configOpenedFiles();
    configSaveButton();
    configQdecrEdit();

    sizeLabel->setText("Size: " + QString::number(selected.width()) + "x" + QString::number(selected.height()));

    configCheckBox();
    configSlider();

    soapLevel->setValue(layer);

    configLevelLabel();
    configManual();

    levelLabel->setText(QString::number(layer));

    addToList("white");
}

int PyramidalWindow::getMaxLayer()
{
    maxLayer = 1;
    int w = selected.width();
    int h = selected.height();
    while(w > 1 || h > 1){
        w /= qDecr;
        h /= qDecr;
        maxLayer++;
    }
    return maxLayer;
}

bool PyramidalWindow::uniq(QString file)
{
    // проверка на уникальность
    bool uniq = true;
    int diag = sqrt(pow(selected.width(), 2) + pow(selected.height(), 2));

    if (files.empty()){
        files.append(MyFileData(file, layer, diag, qDecr, stretch->isChecked()));
        files[files.count() - 1].setFilePicture(selected);
    } else {
        foreach(MyFileData f, files){
            if (file == f.getFileName())
                uniq = false;
        }
    }
    return uniq;
}

void PyramidalWindow::configPictureLabel()
{
    pictureLabel = new QLabel(this);
    pictureLabel->setGeometry(10, 25, white.width(), white.height());
    pictureLabel->setAlignment(Qt::AlignCenter);
}

void PyramidalWindow::configSelectPictureMenu()
{
    selectPictureMenu = new QMenu("Выбрать");
    action1Puzzle = selectPictureMenu->addAction(puzzle, "&puzzle", this, SLOT(pictureSelected()));
    action2Red = selectPictureMenu->addAction(red, "&red", this, SLOT(pictureSelected()));
    action3Cyan = selectPictureMenu->addAction(cyan, "&cyan", this, SLOT(pictureSelected()));
    action4Violet = selectPictureMenu->addAction(violet, "&violet", this, SLOT(pictureSelected()));
    action5FromFile = selectPictureMenu->addAction(fromFile, "&из файла", this, SLOT(addPictureFromFile()));
}

void PyramidalWindow::configSelectLevelMenu()
{
    selectLevelMenu = new QMenu("Выбрать слой");
    for(int i = 1; i <= getMaxLayer(); i++){
        selectLevelMenu->addAction(selected, QString::number(i), this, SLOT(menuLevelChanged()));
    }
}

void PyramidalWindow::configWindow()
{
    this->setStyleSheet("background-color: rgb(175, 134, 100)");
    resize(840, 600);
    setWindowTitle("Пирамида изображений");
    //setAttribute(Qt::WA_DeleteOnClose);
}

void PyramidalWindow::configScrollArea()
{
    scrollArea = new QScrollArea(this);
    scrollArea->setGeometry(10, 25, 550, 550);
    scrollArea->setWidget(pictureLabel);
    scrollArea->setStyleSheet("background-color: rgb(0, 0, 0)");
    scrollArea->setAlignment(Qt::AlignCenter);
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
}

//void PyramidalWindow::configInputLayer()
//{
//    input->setGeometry(570, 25, 60, 50);
//    inputLayer = new QLineEdit;
//    inputLayer->setGeometry(570, 45, 60, 20);
//    inputLayer->setParent(this);
//    QRegExp rx("(\\d)");
//    QValidator *v = new QRegExpValidator(rx, this);
//    inputLayer->setValidator(v);
//    connect(inputLayer, SIGNAL(textChanged(const QString &)), this, SLOT(menuLevelChanged()));
//}

void PyramidalWindow::configSizeLabel()
{
    sizeLabel = new QLabel(this);
    sizeLabel->setGeometry(180, 0, 180, 25);
}

void PyramidalWindow::configCheckBox()
{
    stretch = new QCheckBox(this);
    stretch->setGeometry(350, 0, 100, 25);
    stretch->setText("Растянуть");
    QObject::connect(stretch, SIGNAL(stateChanged(int)), this, SLOT(stretchStateChanged()));
}

void PyramidalWindow::configSlider()
{
    soapLevel = new QSlider(Qt::Horizontal, this);
    soapLevel->setGeometry(570, 75, 200, 15);
    soapLevel->setStyleSheet("background-color: rgb(255, 179, 104);");
    soapLevel->setMaximum(getMaxLayer());
    soapLevel->setMinimum(1);
    soapLevel->setTickPosition(QSlider::TicksBelow);
    soapLevel->setTickInterval(20);
    connect(soapLevel, SIGNAL(valueChanged(int)), this, SLOT(sliderMoved()));
}

void PyramidalWindow::configLevelLabel()
{
    levelLabel = new QLabel(this);
    levelLabel->setGeometry(780, 75, 100, 10);
}

void PyramidalWindow::configManual()
{
    manual = new QLabel(this);
    manual->setGeometry(570, 95, 250, 350);
    manual->setText("<b>РУКОВОДСТВО ПОЛЬЗОВАТЕЛЯ</b><br><br>1) Чтобы начать работу, выберите изображение<br>в меню \"Выбрать\". Можете установите<br>коэффициент уменьшения (по умолчанию <br>равен 2).<br><br>2) Программа автоматически расчитает высоту <br>пирамиды. <br><br>3) Чтобы менять размеры изображения,<br>двигайте слайдер. Выбор конкретного <br>слоя (т.е. его создание) доступен <br>в меню \"Выбрать слой\".<br><br>4) Если желаете размыть картинку, <br>жмите \"растянуть\"и наслаждайтесь большим<br>мыльным изображением.<br><br>5) Вы можете открыть изображение с диска<br>(последний пункт меню \"Выбрать\".<br>Все изображения запоминаются и<br>доступны в комбобокс.<br><br>Приятного дня :)");
}

void PyramidalWindow::configOpenedFiles()
{
    openedFiles = new QComboBox(this);
    openedFiles->setGeometry(570, 455, 150, 20);
    connect(openedFiles, SIGNAL(currentIndexChanged(int)), this, SLOT(fileChoosen()));
}

void PyramidalWindow::configSaveButton()
{
    saveButton = new QPushButton(this);
    saveButton->setGeometry(570, 485, 70, 20);
    saveButton->setText("Сохранить");
    connect(saveButton, SIGNAL(clicked()), this, SLOT(savePicture()));
}

void PyramidalWindow::configQdecrEdit()
{
    QLabel *input = new QLabel(this);
    input->setText("Коэффициент ум-я:");
    input->setGeometry(570, 45, 150, 20);
    coeff = new QLabel(this);
    coeff->setText("текущий: " + QString::number(qDecr));
    coeff->setGeometry(740, 45, 50, 20);
    inputQdecr = new QLineEdit(this);
    inputQdecr->setGeometry(680, 45, 50, 20);
    QRegExp rx("^([1-9][0-9]*|0)(\\.|,)[0-9]{2}");
    QValidator *v = new QRegExpValidator(rx, this);
    inputQdecr->setValidator(v);
    connect(inputQdecr, SIGNAL(textChanged(QString)), this, SLOT(qdecrChanged()));
}

void PyramidalWindow::addToList(QString file)
{
    if (uniq(file)) {
        files.append(MyFileData(file, layer, diag, qDecr, stretch->isChecked()));
        files[files.count() - 1].setFilePicture(selected);
        openedFiles->addItem(file);
    }
    openedFiles->setCurrentIndex(openedFiles->count() - 1);
    // SORT DIAGS
}

void PyramidalWindow::init()
{

}

void PyramidalWindow::imageProcessing(QPixmap picture, int depth)
{
    pictureLabel->setPixmap(picture);
    pictureLabel->setGeometry(10, 25, picture.width(), picture.height());
    //getPyramid(picture, depth);
}

void PyramidalWindow::rewriteLevelMenu()
{
    selectLevelMenu->clear();
    for(int i = 1; i <= getMaxLayer(); i++){
        selectLevelMenu->addAction(selected, QString::number(i), this, SLOT(menuLevelChanged()));
    }
}

void PyramidalWindow::reduce(QPixmap pix)
{
    for(int i = 1; i < layer; i++){
        pix = pix.scaled(pix.width() / qDecr, pix.height() / qDecr);
    }
    redusedPicture = pix;

    if (stretch->isChecked()){
        pictureLabel->setPixmap(pix.scaled(selected.width(), selected.height()));
    } else {
        pictureLabel->setPixmap(redusedPicture);
    }

    pictureLabel->setGeometry(10, 25, pictureLabel->pixmap()->width(), pictureLabel->pixmap()->height());
    levelLabel->setText(QString::number(layer));
    QString realSize = "Текущий размер: " + QString::number(redusedPicture.width()) + "x" + QString::number(redusedPicture.height());
    QString origSize = "Размер оригинала: " + QString::number(selected.width()) + "x" + QString::number(selected.height());
    sizeLabel->setText(realSize + "<br>" + origSize);
    soapLevel->setValue(layer);
}

void PyramidalWindow::redrawSlider()
{
    soapLevel->setMaximum(getMaxLayer());
}

//void PyramidalWindow::getPyramid(QPixmap picture, int depth)
//{
//    imageSpector.clear();
//    for (int i = 0; i <= depth; i++){
//        imageSpector.push_back(picture);
//        picture = picture.scaled(picture.width() / 2, picture.height() / 2);
//    }
//}

void PyramidalWindow::pictureSelected()
{
    QAction *action = (QAction*)sender();
    selected = QPixmap(":res/images/" + action->iconText() + ".png");

    addToList(action->iconText());

    reduce(selected);
    rewriteLevelMenu();
    redrawSlider();

    foreach(QAction *ac, selectLevelMenu->actions())
    {
         ac->setIcon(selected);
    }
}

//void PyramidalWindow::layerEditChanged()
//{
//    layer = inputLayer->text().toInt();

//    reduce(selected);
//    redrawSlider();
//    rewriteLevelMenu();
//}

void PyramidalWindow::menuLevelChanged()
{
    QAction *action = (QAction*)sender();
    layer = action->text().toInt();
    soapLevel->setValue(layer);
    reduce(selected);
}

void PyramidalWindow::stretchStateChanged()
{
    if(stretch->isChecked()){
        pictureLabel->setPixmap(redusedPicture.scaled(selected.width(), selected.height()));
        pictureLabel->setGeometry(10, 25, selected.width(), selected.height());
    } else {
        pictureLabel->setPixmap(redusedPicture);
        pictureLabel->setGeometry(10, 25, redusedPicture.width(), redusedPicture.height());
    }
}

void PyramidalWindow::sliderMoved()
{
    layer = soapLevel->value();

    reduce(selected);
}

void PyramidalWindow::fileChoosen()
{
    QString fileName = openedFiles->currentText();
    bool catched = false;
    foreach(MyFileData f, files){
        if (f.getFileName() == fileName){
            selected = f.getFilePicture();
            layer = f.getLayer();
            qDecr = f.getQDecr();
            stretch->setChecked(f.getIsStretch());
            soapLevel->setValue(layer);
            catched = true;
        }
    }
    if (catched == true){
        reduce(selected);
        rewriteLevelMenu();
    } else {
        qDebug() << "accidentally file not found";
    }

}

void PyramidalWindow::addPictureFromFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, ("Open File"),
                                                      "/home",
                                                      ("Images (*.png *.xpm *.jpg)"));
    if( !fileName.isNull() )
    {
        QPixmap pix;
        pix.load(fileName);
        selected = pix;
        // обрезка имени
        for(int i = fileName.size() - 1; i > 0; i--){
            if (fileName[i] == '/'){
                fileName = fileName.right(i);
            }
        }
        addToList(fileName);
        reduce(selected);
        redrawSlider();
        rewriteLevelMenu();
    }
}

void PyramidalWindow::savePicture()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save Picture"), "",
                                                    tr("Images (*.png *.xpm *.jpg)"));
    if (fileName.isEmpty())
        return;
    else {
        pictureLabel->pixmap()->save(fileName);
        if (!pictureLabel->pixmap()->save("file2.jpg")) QMessageBox::warning(this,"","Не удалось сохранить файл",QMessageBox::Ok,0);
    }
}

void PyramidalWindow::qdecrChanged()
{
    qDecr = inputQdecr->text().toDouble();

    coeff->setText(QString::number(qDecr));
    rewriteLevelMenu();
    redrawSlider();
    reduce(selected);
}
