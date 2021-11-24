#include "clientwidget.h"
#include "ui_clientwidget.h"
#include <QDebug>
#include <QTimer>
ClientWidget::ClientWidget(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ClientWidget)
{
    ui->setupUi(this);
    ui->groupBox->setEnabled(false);
    socketDialogueServeur = new  QTcpSocket();
    connect(socketDialogueServeur, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &ClientWidget::onQTcpSocket_error);
    connect(ui->ConnexionButton,SIGNAL(clicked()),this,SLOT(on_pushButtonConnexion_clicked()));
    connect(ui->OsButton,SIGNAL(clicked()),this,SLOT(on_pushButtonOs_clicked()));
    connect(ui->NomOrdinateurButton,SIGNAL(clicked()),this,SLOT(on_pushButtonOrdinateur_clicked()));
    connect(ui->NomUtilisateurbutton,SIGNAL(clicked()),this,SLOT(on_pushButtonUtilisateur_clicked()));
    connect(ui->ArchitectureProcesseurButton,SIGNAL(clicked()),this,SLOT(on_pushButtonArchitecture_clicked()));
    connect(socketDialogueServeur,SIGNAL(stateChanged(QAbstractSocket::SocketState)),this,SLOT(onQTcpSocket_stateChanged(QAbstractSocket::SocketState)));
    connect(socketDialogueServeur,SIGNAL(readyRead()),this, SLOT(onQTcpSocket_readyRead()));
    connect(socketDialogueServeur,SIGNAL(hostFound()),this,SLOT(onQTcpSocket_hostFound()));
    connect(socketDialogueServeur,SIGNAL(aboutToClose()),this,SLOT(onQTcpSocket_aboutToClose()));
}

ClientWidget::~ClientWidget()
{
    delete ui;
}

void ClientWidget::onQTcpSocket_error(QAbstractSocket::SocketError socketError)
{
    ui->EtatConnexionEdit->append(socketDialogueServeur->errorString());
}

void ClientWidget::on_pushButtonConnexion_clicked(){
    if(socketDialogueServeur->state() == QAbstractSocket::ConnectedState)
    {
        socketDialogueServeur->close();
        ui->ConnexionButton->setText("Connexion");

    }
    else
    {
    QString Addresse = ui->AdresseIpEdit->text();
    QString port = ui->NumeroPortEdit->text();
    ui->EtatConnexionEdit->append(QString("Connexion à l'adresse : "+Addresse));
    ui->EtatConnexionEdit->append(QString("Port : "+port));
    socketDialogueServeur->connectToHost(Addresse,port.toInt());
    ui->ConnexionButton->setText("Deconnexion");
    }
}
void ClientWidget::on_pushButtonOs_clicked()
{
    typeDemande="o";
    socketDialogueServeur->write(typeDemande.toLatin1());


}
void ClientWidget::on_pushButtonOrdinateur_clicked()
{
    typeDemande="c";
    socketDialogueServeur->write(typeDemande.toLatin1());

}

void ClientWidget::on_pushButtonUtilisateur_clicked()
{
    typeDemande="u";
    socketDialogueServeur->write(typeDemande.toLatin1());

}

void ClientWidget::on_pushButtonArchitecture_clicked()
{
    typeDemande="a";
    socketDialogueServeur->write(typeDemande.toLatin1());


}
void ClientWidget::onQTcpSocket_connected(){

    ui->EtatConnexionEdit->append(QString("Connecté"));

}

void ClientWidget::onQTcpSocket_stateChanged(QAbstractSocket::SocketState socketState){
    if (socketState == QAbstractSocket::UnconnectedState){
        onQTcpSocket_disconnected();
        ui->groupBox->setEnabled(false);
        ui->AdresseIpEdit->setEnabled(true);
        ui->NumeroPortEdit->setEnabled(true);


    }
    if (socketState == QAbstractSocket::ConnectedState){
        onQTcpSocket_connected();
         ui->groupBox->setEnabled(true);
         ui->AdresseIpEdit->setEnabled(false);
         ui->NumeroPortEdit->setEnabled(false);
    }

}

void ClientWidget::onQTcpSocket_disconnected(){

    ui->EtatConnexionEdit->append("Succefully disconnected");

}

void  ClientWidget::onQTcpSocket_readyRead()
{
    if(typeDemande == "o"){
        ui->OsEdit->setText(socketDialogueServeur->readAll());
    }
    if(typeDemande == "c"){
        ui->NomOrdinateurEdit->setText(socketDialogueServeur->readAll());
    }
    if(typeDemande == "u"){
        ui->NomUtilisateuEdit->setText(socketDialogueServeur->readAll());
    }
    if(typeDemande == "a"){
        ui->ArchitectureProcesseurEdit->setText(socketDialogueServeur->readAll());

    }
}
void ClientWidget::onQTcpSocket_hostFound(){
    ui->EtatConnexionEdit->append("host founded");
}
void ClientWidget::onQTcpSocket_aboutToClose(){
     ui->EtatConnexionEdit->append("Server about to close");
}
