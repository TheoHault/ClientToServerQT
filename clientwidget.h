#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QMainWindow>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class ClientWidget; }
QT_END_NAMESPACE

class ClientWidget : public QMainWindow
{
    Q_OBJECT

public:
    ClientWidget(QWidget *parent = nullptr);
    ~ClientWidget();

private:
    Ui::ClientWidget *ui;
    QTcpSocket* socketDialogueServeur;
    QString typeDemande;
private slots:
   void on_pushButtonConnexion_clicked();
   void on_pushButtonOrdinateur_clicked();
   void on_pushButtonUtilisateur_clicked();
   void on_pushButtonOs_clicked();
   void on_pushButtonArchitecture_clicked();
   void onQTcpSocket_connected();
   void onQTcpSocket_disconnected();
   void onQTcpSocket_error(QAbstractSocket::SocketError socketError);
   void onQTcpSocket_stateChanged(QAbstractSocket::SocketState socketState);
   void onQTcpSocket_hostFound();
   void onQTcpSocket_aboutToClose();
   //void onQTcpSocket_bytesWritten(quint64 bytes);
   //void onQTcpSocket_readChannelFinished();
   void onQTcpSocket_readyRead();
};

#endif // CLIENTWIDGET_H
