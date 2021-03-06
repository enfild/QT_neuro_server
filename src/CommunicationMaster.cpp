#include "include/CommunicationMaster.h"

CommunicationMaster::CommunicationMaster(QString serverName) : QObject(nullptr)
{
    // Создаём и запускаем сервер командой listen.
    // Если сервер не может быть запущен, выдать сообщение об ошибке и завершить работу программы
    localServer = new QLocalServer(this);
    if(!localServer->listen(serverName))
    {
        qWarning() << "FALSE LISTEN SERVER";
        localServer->close();
        return;
    }

    QObject::connect(localServer, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));

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
    // можно отправить информацию клиенту о соединении с сервером
    //    sendToClient(localSocket, "Server response: Connected!");
}

// Слот чтения информации от клиента
void CommunicationMaster::slotReadClient()
{
    // Получаем QLocalSocket после срабатывания сигнала о готовности передачи данных
    localSocket = (QLocalSocket*)sender();

	if (localSocket->isValid())
	{

		temp.imageBA = localSocket->readAll();

		temp.outString = nMaster.TF_processing(false, temp.imageBA);
		if (temp.outString != "") 
		{
		sendToClient(localSocket, temp.outString);
		}
		else
		{
			sendToClient(localSocket, "Empty");
		}
    }
}

void CommunicationMaster::sendToClient(QLocalSocket* localSocket, QString stringIn)
{

    QByteArray baString = stringIn.toUtf8();

    localSocket->write(baString);
}

void CommunicationMaster::sleep()
{
    QEventLoop loop;
    QTimer::singleShot(100, &loop, SLOT(quit()));
    loop.exec();
}
