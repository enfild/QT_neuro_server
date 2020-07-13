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
#define slots

//#define Q_SIGNALS
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

// class NeuronetMaster;

class CommunicationMaster: public QObject
{
    Q_OBJECT


public:

     NeuronetMaster nMaster;

    CommunicationMaster(QString serverName);

    ~CommunicationMaster();

    QLocalSocket* localSocket;

    /// \ Инициализация сокета
    void connectSocket();

    QImage imageQ;

private slots:

    // Слот обработки нового клиентского подключения
    virtual void slotNewConnection();

    // Слот чтения информации от клиента
    void slotReadClient();

    // Метод для отправки клиенту подтверждения о приёме информации
    void sendToClient(QLocalSocket* localSocket, QString stringIn);


private:

    // Указатель на QLocalServer
    QLocalServer* localServer;

    /// \ статус сервера
    int server_status;

    void sleep();

};



#endif // COMMUNICATIONMASTER_H
