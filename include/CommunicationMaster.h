#ifndef COMMUNICATIONMASTER_H
#define COMMUNICATIONMASTER_H

#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>
#include <QImage>
#include <QEventLoop>
#include <QTimer>

namespace  {

int Port = 7755;

struct command {
    /// \ номер кадра
    int id;
    /// \ строки с командами
    const QString start = "st";

    const QString finish = "fin";

};

}

class CommunicationMaster: public QObject
{
    Q_OBJECT

public:

    CommunicationMaster();

    ~CommunicationMaster();

    /// \ Инициализация сокета
    void connectSocket();

//signals:
//    bool imageIsReady;

private:

    QImage *image;

    /// \ сокет проги
    QUdpSocket MainSocket;

    /// \ сокет дочернего процесса
    QUdpSocket MinorSocket;

    /// \ статус сервера
    int server_status;

    /// \ прием
    bool reciveSocket();

    void sleep();

    /// \ отправка
    bool sendSocket();

};



#endif // COMMUNICATIONMASTER_H
