#ifndef FILESTORESERVER_H
#define FILESTORESERVER_H
#include <QThread>
#include <QReadWriteLock>
#include <QWaitCondition>
#include <QFile>

class ImageData
{
    char* imgdata;
    long  imgsize;
public:
    ImageData(void* src, size_t l)
    {
        imgdata = (char*)malloc(l);
        memcpy(imgdata, src, l);
        imgsize = l;
    }

    char* data() { return imgdata; }
    const long size() { return imgsize;}
};

class FileStoreServer: public QThread
{
    Q_OBJECT

public:
    FileStoreServer();
    ~FileStoreServer();
    void append(ImageData* block, QString path, int sizelimit);

protected:
    void run();
    void write(ImageData* block);
private:
    int id;
    QList<ImageData*> dataList;
    QReadWriteLock lock;
    QWaitCondition listEmpty;
    QMutex mutex;
    long fileSize;
    QString prefix;
    QFile* file;
    QFile* newFile();
    void closeFile();
    QString fileNamePrefix();
    QString filePath;
    int singleFileSize;
};

#endif // FILESTORESERVER_H
