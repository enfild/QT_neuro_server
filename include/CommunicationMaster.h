#ifndef COMMUNICATIONMASTER_H
#define COMMUNICATIONMASTER_H

#include <QObject>

#include <include/NeuronetMaster.h>

#include <QLocalSocket>
#include <QLocalServer>

#include <QString>
#include <QImage>
#include <QEventLoop>
#include <QTimer>
#include <QBuffer>

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

    CommunicationMaster(QString serverName);

    ~CommunicationMaster();

    static QLocalSocket* localSocket;

    /// \ Инициализация сокета
    void connectSocket();

public slots:

    // Слот обработки нового клиентского подключения
    virtual void slotNewConnection();

    // Слот чтения информации от клиента
    void slotReadClient();

    // Метод для отправки клиенту подтверждения о приёме информации
    static void sendToClient(QLocalSocket* localSocket, QString stringIn);

private:

    // Указатель на QLocalServer
    QLocalServer* localServer;

    /// \ сокет дочернего процесса
    //    MyLocalServer server("MyLocalServer");

    /// \ статус сервера
    int server_status;

    void sleep();

};



#endif // COMMUNICATIONMASTER_H
