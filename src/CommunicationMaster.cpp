#include "include/CommunicationMaster.h"

#include <QDataStream>
#include <QPixmap>



CommunicationMaster::CommunicationMaster() : QObject(nullptr)
{
    CommunicationMaster::connectSocket();
}

CommunicationMaster::~CommunicationMaster(){


}

void CommunicationMaster::connectSocket()
{
    MainSocket.bind(QHostAddress::LocalHost, Port);
    QObject::connect(&MainSocket, &QUdpSocket::readyRead, this, [=]() {reciveSocket();});
}

bool CommunicationMaster::reciveSocket(){
    bool result;
    qDebug() << "CATCH SIGNAL";
//    if(udpSocket.bytesAvailable()){
//        qDebug() << "BYTES AVAILABLE";
//    }
    while (MainSocket.hasPendingDatagrams()) {
    qDebug() << "HAS DATAGRAMM";
        QByteArray buffer(MainSocket.pendingDatagramSize(), 0 );
        MainSocket.readDatagram( buffer.data(), buffer.size() );

        QDataStream stream( buffer );
        stream.setVersion( QDataStream::Qt_5_0 );

        quint16 width, height, y;
        stream >> width >> height >> y;

        if( !image )
            image = new QImage( width, height, QImage::Format_RGB32 );
        else if( image->width() != width || image->height() != height )
        {
            delete image;
            image = new QImage( width, height, QImage::Format_RGB32 );
        }
qDebug() << "before datagramm";
        for( int x=0; x<width; ++x )
        {
            quint8 red, green, blue;
            stream >> red >> green >> blue;

            image->setPixel( x, y, qRgb( red, green, blue ) );
            qDebug() << sizeof(image);
        }


        //        qDebug() << "HAS PENDING";

        //        QByteArray datagram;
        //        datagram.resize(udpSocket.pendingDatagramSize());
        //        result = udpSocket.readDatagram(datagram.data(), datagram.size());

        //        qDebug() << "Message receive: " << datagram.data();

    }
//    setText( "s" );
//      setPixmap( QPixmap::fromImage( *image ) );
//      resize( image->size() );
    //сборка изображения


    return result;
}

bool CommunicationMaster::sendSocket(){

    QByteArray Data; // Message for send
    Data += "SAMP";
    Data += QString( 93 );
    Data += QString( 119 );
    Data += QString( 26 );
    Data += QString( 214 );
    Data += QString(7777 & 0xFF);
    Data += QString(7777 >> 8 & 0xFF);
    Data.append("i");

    bool result = MainSocket.writeDatagram(Data, QHostAddress::LocalHost, Port);
    return result;
}

void CommunicationMaster::sleep()
{
    QEventLoop loop;
    QTimer::singleShot(100, &loop, SLOT(quit()));
    loop.exec();
}
