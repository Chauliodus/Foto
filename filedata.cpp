#include "filedata.h"

MyFileData::MyFileData()
{
    this->setFileName("");
    this->setDiag(0);
    this->setLayer(1);
    this->setQDecr(2);
    this->setIsStretch(false);
    this->setFilePicture(QPixmap());
}

MyFileData::MyFileData(QString name, int layer, int diag, double q, bool isStr)
{
    this->setFileName(name);
    this->setDiag(diag);
    this->setLayer(layer);
    this->setQDecr(q);
    this->setIsStretch(isStr);
}
QString MyFileData::getFileName() const
{
    return fileName;
}

void MyFileData::setFileName(const QString &value)
{
    fileName = value;
}
int MyFileData::getLayer() const
{
    return layer;
}

void MyFileData::setLayer(int value)
{
    layer = value;
}
double MyFileData::getQDecr() const
{
    return qDecr;
}

void MyFileData::setQDecr(double value)
{
    qDecr = value;
}
bool MyFileData::getIsStretch() const
{
    return isStretch;
}

void MyFileData::setIsStretch(bool value)
{
    isStretch = value;
}
int MyFileData::getDiag() const
{
    return diag;
}

void MyFileData::setDiag(int value)
{
    diag = value;
}
QPixmap MyFileData::getFilePicture() const
{
    return filePicture;
}

void MyFileData::setFilePicture(const QPixmap &value)
{
    filePicture = value;
}






