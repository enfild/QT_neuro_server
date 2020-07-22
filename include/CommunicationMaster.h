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

namespace  {

}

class CommunicationMaster: public QObject
{
    Q_OBJECT

public:

    struct tempData {
        /// \ Порт сокета
        int Port = 7755;

        /// \ номер кадра
        int id;

        /// \ изображение для общзения с другим классом
        QByteArray imageBA;

        /// \ выходные данные
        QString outString;
    };

    tempData temp;

    /// \ стартуем экземпляр класса с обработкой кадра
    NeuronetMaster nMaster;

    /// \ конструктор
    CommunicationMaster(QString serverName);

    /// \ деструктор
    ~CommunicationMaster();

    /// \ PIPE локальный сокет
    QLocalSocket* localSocket;

    /// \ Инициализация сокета
    void connectSocket();

private slots:

    // Слот обработки нового клиентского подключения
    virtual void slotNewConnection();

    // Слот чтения информации от клиента
    void slotReadClient();

    // Метод для отправки клиенту подтверждения о приёме информации
    void sendToClient(QLocalSocket* localSocket, QString stringIn);

private:

    /// \ Указатель на QLocalServer
    QLocalServer* localServer;

    /// \ статус сервера
    int server_status;

    ///  \ задержка
    void sleep();

};

#endif // COMMUNICATIONMASTER_H
