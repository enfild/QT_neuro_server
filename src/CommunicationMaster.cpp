#include "include/CommunicationMaster.h"
#include "include/NeuronetMaster.h"


CommunicationMaster::CommunicationMaster(QString serverName) : QObject(nullptr)
{
    // Создаём и запускаем сервер командой listen.
    // Если сервер не может быть запущен, выдать сообщение об ошибке и завершить работу программы
    localServer = new QLocalServer(this);
    if(!localServer->listen(serverName))
    {
        qWarning() << "BAAAAAAAAD";
        localServer->close();
        return;
    }
    qDebug() << "ZAEBAL" << serverName;

        NeuronetMaster nMaster;

    // Соединяем сигнал сервера о наличии нового подключения с обработчиком нового клиентского подключения
    QObject::connect(localServer, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));

//    QObject::connect(this, SIGNAL(recieveDone()), &nMaster, SLOT(TF_processing(false, imageQ)));

//    QObject::connect(this, recieveDone(), [=] (QImage imageQ) {nMaster.TF_processing(false, imageQ); });
    QObject::connect(this, SIGNAL(recieveDone()), &nMaster, SLOT(TF_processing(false, QImage)));


   }

CommunicationMaster::~CommunicationMaster(){

}

void CommunicationMaster::slotNewConnection()
{
    qDebug() << "NewConnection";
    // Получаем сокет, подключённый к серверу
    localSocket = localServer->nextPendingConnection();
    // Соединяем сигнал отключения сокета с обработчиком удаления сокета

    connect(localSocket, SIGNAL(disconnected()), localSocket, SLOT(deleteLater()));
    // Соединяем сигнал сокета о готовности передачи данных с обработчиком данных

    connect(localSocket, SIGNAL(readyRead()), this, SLOT(slotReadClient()));
    server_status = localSocket->isValid();
    // Отправляем информацию клиенту о соединении с сервером
    //    sendToClient(localSocket, "Server response: Connected!");
}

// Слот чтения информации от клиента
void CommunicationMaster::slotReadClient()
{
    qDebug() << "slotReadClient";
    // Получаем QLocalSocket после срабатывания сигнала о готовности передачи данных
    localSocket = (QLocalSocket*)sender();

    if(localSocket->isValid()){

        qDebug() << localSocket;

        QByteArray inArray = localSocket->readAll();

        qDebug() << sizeof(inArray);

        imageQ = QImage::fromData(inArray, "PNG");

        const auto resSaved = imageQ.save("D:/0.png");

        qDebug() << sizeof(imageQ) << "READED IMAGE";


        emit recieveDone();

//                QString coordinates = NeuronetMaster::TF_processing(false);
    }

}

// Метод для отправки клиенту подтверждения о приёме информации
void CommunicationMaster::sendToClient(QLocalSocket* localSocket, QString stringIn)
{
    qDebug() << localSocket->isValid();

    QByteArray baString = stringIn.toUtf8();

    localSocket->write(baString);

}



void CommunicationMaster::sleep()
{
    QEventLoop loop;
    QTimer::singleShot(100, &loop, SLOT(quit()));
    loop.exec();
}
