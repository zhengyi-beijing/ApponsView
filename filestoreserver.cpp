#include "filestoreserver.h"
#include <QDir>
#include <QDateTime>
#include "QLogger.h"
#include <QDebug>
#include <QMessageBox>
int MAX_SIZE = 2*1024 * 1024;
FileStoreServer::FileStoreServer()
{
    fileSize = 0;
    id = 0;

    QDir dir(QDir::currentPath());
    if (!dir.exists("logs"))
        dir.mkdir("logs");
    dir.setCurrent(".\\logs");
    prefix = fileNamePrefix();
    file = NULL;
}

FileStoreServer::~FileStoreServer()
{
    if(file)
        closeFile();
}

QString FileStoreServer::fileNamePrefix()
{
    QString _fileName = "x-ray_";
    QDateTime currentTime = QDateTime::currentDateTime();
    _fileName += currentTime.date().toString("yy-MM-dd");
    _fileName += "-";
    _fileName += currentTime.time().toString("hh_mm_ss");
    return _fileName;
}

QFile* FileStoreServer::newFile()
{
    QString _fileName =  filePath + "/"+ prefix;
    _fileName += "-";
    _fileName += QString::number(id++);
    _fileName += ".raw";
    QString msg("Apply new file");
    msg += _fileName;
    qDebug() << msg;
    QLogger::QLog_Trace("Appons", msg);
    return new QFile(_fileName);
}

void FileStoreServer::append(ImageData* block, QString path, int sizelimit)
{
    filePath = path;
    singleFileSize = sizelimit;
    qDebug()<<"Append Image data";
    lock.lockForWrite();
        dataList.append(block);
    lock.unlock();
    qDebug()<<"Append Image data wake all======";
    listEmpty.wakeAll();
}

void FileStoreServer::stop()
{
    listEmpty.wakeAll();
    running = false;
}

void FileStoreServer::clearBuffer()
{
    qDebug()<< "waiting for lock\n";
    lock.lockForWrite();
    while (!dataList.isEmpty())
        delete dataList.takeFirst();
    lock.unlock();
    closeFile();
    qDebug()<< "free lock\n";
}

void FileStoreServer::run(){
    running = true;
    while (running) {
        if (dataList.size() == 0) {
            qDebug()<<"List Emty wait........";
            mutex.lock();
            listEmpty.wait(&mutex);
            mutex.unlock();
            qDebug()<<"Image data waked **********======";
        }
        if(dataList.isEmpty())
            break;
        lock.lockForWrite();
            ImageData* block = dataList.first();
            dataList.removeFirst();
        lock.unlock();
        write(block);
        delete block;
        block = NULL;
    }
}

void FileStoreServer::closeFile()
{
    QLogger::QLog_Trace("Appons", "File close");
    qDebug() << "File Close";
    if(file) {
        file->close();
        delete file;
    }
    file = NULL;
    fileSize = 0;
}

void FileStoreServer::write(ImageData* block)
{
    QLogger::QLog_Trace("Appons", "write Image data");
    qDebug()<< "Write Image Data";
    if (!file) {
        file = newFile();
        if(!file->open(QIODevice::WriteOnly)) {
            qDebug()<<"Open writing file failed\n";
            return;
        };

    }
    if (file) {
        long size = block->size();
        long writed = 0;
        char* src = block->data();
        while (size > 0) {
            writed = file->write((char*)src, size);
            src += writed;
            size -= writed;
        }
        fileSize += block->size();
//        qDebug()<<"fileSize is "<<fileSize;
//        qDebug()<<"MAX_SIZE is "<<singleFileSize;
//        if (fileSize > (singleFileSize-1024)) {
//            closeFile();
//        }
        if (block->islast())
            closeFile();
    }

}
