#include "Server.h"

MyServer::MyServer(QMainWindow* parent):QTcpServer(parent)
{
    listen(QHostAddress::Any, 55555);
}

int MyServer::getConnectingClient() noexcept
{
    return AllClient.size();
}

void MyServer::incomingConnection(qintptr socketDescriptor)
{
    QTcpSocket* currentClient = new QTcpSocket(this);
    currentClient->setSocketDescriptor(socketDescriptor);

    //-------------------new Client------------------------------
    connect(currentClient,&QTcpSocket::readyRead,[=](){
        msg = currentClient->readAll();
        emit setText(msg);

        i=AllClient.begin();
        while(i!=AllClient.end()){
            i.value()->write("\n--Client disconnect--\n");
            i++;
        }
    });

    AllClient.insert(socketDescriptor,currentClient);
    emit newClient();
    //------------------------------------------------------------

    //-------------------Client disconnect------------------------
    connect(currentClient,&QTcpSocket::disconnected,[=]{

        AllClient.remove(socketDescriptor);

        QString str = QString::number(socketDescriptor)+ " disconnect\n";
        emit setText(str);

        i=AllClient.begin();
        while(i!=AllClient.end()){
            i.value()->write("\n--Client disconnect--\n");
            i++;
        }
        emit disconnectClient();
    });
    //-------------------------------------------------------------
}
