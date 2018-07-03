#include <QPixmap>
#include <QString>

#ifndef FILEDATA_H
#define FILEDATA_H

class MyFileData
{
public:
    MyFileData();
    MyFileData(QString, int, int, double, bool);
    QString getFileName() const;
    void setFileName(const QString &value);

    int getLayer() const;
    void setLayer(int value);

    double getQDecr() const;
    void setQDecr(double value);

    bool getIsStretch() const;
    void setIsStretch(bool value);

    int getDiag() const;
    void setDiag(int value);

    QPixmap getFilePicture() const;
    void setFilePicture(const QPixmap &value);

private:
    QPixmap filePicture;
    QString fileName;
    int diag;
    int layer;
    double qDecr;
    bool isStretch;
};

#endif // FILEDATA_H
