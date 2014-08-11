#ifndef PIXELORDERCONVERTER_H
#define PIXELORDERCONVERTER_H
#include <QDebug>
#include "apponscontrol.h"
#include "QLogger.h"
class PixelOrderConverter
{
public:
    PixelOrderConverter(int bNum, int pNum)
    {
        boardNum = bNum;
        pixelNum = pNum;
    }

    virtual ~PixelOrderConverter() {}
    virtual void process(ApponsControl::IImageObject* src)=0;
protected:
    int boardNum;
    int pixelNum;
};

class DualToSingleConverter: public PixelOrderConverter
{
public:
    DualToSingleConverter(int boardNum, int pixelNum): PixelOrderConverter(boardNum,pixelNum)
    {
        int size = boardNum*pixelNum;
        Q_ASSERT(size == 512);
        buffer = new quint16[size];
    }
    ~DualToSingleConverter()
    {
        delete[] buffer;
    }

    virtual void process(ApponsControl::IImageObject* src)
    {
        int width = src->Width();
        int height = src->Height();
        //qDebug() << __FUNCTION__<<"height = "<< height;
        Q_ASSERT(width == boardNum*pixelNum);
        for(int i=0; i< height; i++) {
            quint16* pline = (quint16*)src->ImageLineAddress(i);
            convertLine(pline, width);
        }
    }
 private:

    quint16* buffer;


    void copyBlock(quint16* src, int srcIndex, int destIndex)
    {
        memcpy (buffer+destIndex*pixelNum, src+srcIndex*pixelNum, pixelNum*2);
    }

    void convertLine(quint16* src, int width)
    {
        int blockNum = boardNum ;
            QString msg;
        //Low Energy Area. First half part
        for(int i=0; i < blockNum/2 ; i++) {
            copyBlock(src, i, i*2);
            //QLogger::QLog_Trace("Appons", "App start");
        }
        //High Energy Area. Sencond half part
        for(int i = blockNum/2; i < blockNum ; i++) {
            copyBlock(src, i, i*2-blockNum+1);
        }
        memcpy(src, buffer, width*2);
    }

};

#endif // PIXELORDERCONVERTER_H
