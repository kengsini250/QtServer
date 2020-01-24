#ifndef SERVER_H
#define SERVER_H

#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QMainWindow>
#include <QString>
#include <QByteArray>
#include <QMap>

class MyServer : public QTcpServer
{
    Q_OBJECT
public:
	explicit MyServer(QMainWindow* parent = nullptr);

    int getConnectingClient() noexcept;
protected:
    void incomingConnection(qintptr socketDescriptor);
private:
    QMap<qintptr,QTcpSocket*> AllClient;
    QMap<qintptr,QTcpSocket*>::iterator i;

    QString msg;
signals:
    void newClient();
    void setText(QString&str);
    void disconnectClient();
};

#endif
