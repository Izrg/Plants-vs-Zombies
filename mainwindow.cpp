#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "maingame.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QDebug>
extern QList<QList<QGraphicsPixmapItem*>*> *zombieGridList;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //User selection is removed until user wants it.
    ui->userSelectorBox->setVisible(false);
    ui->userSelectorBox->setEnabled(false);

    //Makes sure that the levels file is present.
    QString tempFile = QCoreApplication::applicationDirPath() + "/pvz_levels.csv";
    Fparcer *tempParce = new Fparcer(tempFile);
    tempParce->readFile(false);
    if(tempParce->stringList.isEmpty())
    {
        QMessageBox::about(this,"Error","No Level information found");
        parent->close();
    }
    delete tempParce;

    tempFile = QCoreApplication::applicationDirPath() + "/pvz_players.csv";
    //Parce the player file
    playerParce = new Fparcer(tempFile);
    playerParce->readFile(true);
    if(playerParce->stringList.isEmpty())
    {
        qDebug() << "Player file empty" << endl;
        ui->deleteBtn->setEnabled(false);
        ui->startBtn->setEnabled(false);
        ui->changeuserBtn->setEnabled(false);

    }else{
        int lastTime = 0;

        for(int i = 0; i < playerParce->stringList.size(); i++)
        {
            //For earch row in the file
            if((i%3) == 0)
            {
                //If the timestamp is larger than the previous one, that player played last
                if(playerParce->stringList.at(i).toInt() > lastTime)
                {
                    //Set the new last time.
                    lastTime = playerParce->stringList.at(i).toInt();
                    //Set the last user played.
                    lastUser = playerParce->stringList.at(i+1);
                    userLvl = playerParce->stringList.at(i+2).toInt();
                }
            }
        }
        //Set the last user played name on the label.
        ui->usernameLbl->setText(lastUser);
        ui->lvlLbl->setText(QString("Current Level: %1").arg(userLvl));
    }


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::restartGame()
{
    //Delete the previous mG instance
    delete mG;
    //set a new mG instance.
    mG = new mainGame(0,this);
    mG->show();
}

void MainWindow::on_startBtn_clicked()
{


    //Show the new game window
    mG = new mainGame(0,this);
    mG->show();

    //Hide this current window
    this->close();
}


void MainWindow::on_changeuserBtn_clicked()
{
    ui->deleteBtn->setEnabled(false);
    ui->startBtn->setEnabled(false);
    ui->changeuserBtn->setEnabled(false);
    ui->addUserBtn->setEnabled(false);

    ui->userSelectorBox->clear();
    for(int i = 0; i < playerParce->stringList.size(); i++)
    {
        //at each new row
        if((i%3) == 0)
        {
            //get the size of the userselectorbox
            //Add the username to the end of the combobox.
            ui->userSelectorBox->addItem(playerParce->stringList.at(i+1),ui->userSelectorBox->currentIndex());
        }
    }
    ui->userSelectorBox->setVisible(true);
    ui->userSelectorBox->setEnabled(true);

}

void MainWindow::on_userSelectorBox_activated(const QString &arg1)
{

    ui->usernameLbl->setText(ui->userSelectorBox->currentText());
    lastUser = ui->userSelectorBox->currentText();
    for(int i =0; i < playerParce->stringList.size(); i++)
    {
        if((i%3) == 0)
        {
            //Checks for the users name in the file
            if(playerParce->stringList.at(i+1) == ui->userSelectorBox->currentText())
            {
                //Set the new user level based on that name.
                userLvl = playerParce->stringList.at(i+2).toInt();
                ui->lvlLbl->setText(QString("Current Level: %1").arg(userLvl));
                break;
            }
        }
    }
    //reset the combobox visibility
    ui->userSelectorBox->setVisible(false);
    ui->userSelectorBox->setEnabled(false);

    ui->deleteBtn->setEnabled(true);
    ui->startBtn->setEnabled(true);
    ui->changeuserBtn->setEnabled(true);
    ui->addUserBtn->setEnabled(true);

}

void MainWindow::on_addUserBtn_clicked()
{

    QString tempFile = QCoreApplication::applicationDirPath() + "/pvz_players.csv";

    bool ok;
    QString name = QInputDialog::getText(this,tr("Enter new user"),tr("Username:"),QLineEdit::Normal,"",&ok);
    if((name.length() - 1) >= 10)
    {
        // prompt the user to enter a valid username
        QMessageBox::information(this,"Error!", "Please enter a name less than 10 charachters");
        return;
    }

    QFile save_file (tempFile);
    //Write to the player file
    if(save_file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        //Write the new users data.
        QTextStream out(&save_file);
        out << QDateTime::currentDateTime().toTime_t() << ":" << name << ":" << 1 << endl;

        save_file.close();
        delete playerParce;// delete the previous player parce.
        //Re-read the new player file.
        playerParce = new Fparcer(tempFile);
        playerParce->readFile(true);

        ui->deleteBtn->setEnabled(true);
        ui->startBtn->setEnabled(true);
        ui->changeuserBtn->setEnabled(true);
    }

    int lastTime = 0;
    for(int i = 0; i < playerParce->stringList.size(); i++)
    {
        //For earch row in the file
        if((i%3) == 0)
        {
            //If the timestamp is larger than the previous one, that player played last
            if(playerParce->stringList.at(i).toInt() > lastTime)
            {
                //Set the new last time.
                lastTime = playerParce->stringList.at(i).toInt();
                //Set the last user played.
                lastUser = playerParce->stringList.at(i+1);
                userLvl = playerParce->stringList.at(i+2).toInt();
            }
        }
    }
    //Show the new users name and level on the label.
    ui->usernameLbl->setText(lastUser);
    ui->lvlLbl->setText(QString("Current Level: %1").arg(userLvl));


}

void MainWindow::on_deleteBtn_clicked()
{

    QString tempFile = QCoreApplication::applicationDirPath() + "/pvz_players.csv";
    QFile save_file (tempFile);
    if(save_file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QString s;
        QTextStream t(&save_file);
        while(!t.atEnd())
        {
            QString line = t.readLine();
            if(!line.contains(lastUser)) s.append(line + "\n");
        }
        save_file.resize(0);
        t << s;
        save_file.close();
    }
    //Delete the last instance of playerParce.
    delete playerParce;
    //Re-read the new file with the removed user.
    playerParce = new Fparcer(tempFile);
    playerParce->readFile(true);
    //Prompt the user that a user has been deleted.
    QMessageBox::information(this,"Deleted", QString("User %1 has been deleted").arg(lastUser)); // Prompt the user that their game has been saved.

    if(playerParce->stringList.size() == 0)
    {
        ui->deleteBtn->setEnabled(false);
        ui->startBtn->setEnabled(false);
        ui->changeuserBtn->setEnabled(false);
        ui->usernameLbl->setText("");
        ui->lvlLbl->setText("");
        return;
    }


    int lastTime = 0;
    for(int i = 0; i < playerParce->stringList.size(); i++)
    {
        //For earch row in the file
        if((i%3) == 0)
        {
            //If the timestamp is larger than the previous one, that player played last
            if(playerParce->stringList.at(i).toInt() > lastTime)
            {
                //Set the new last time.
                lastTime = playerParce->stringList.at(i).toInt();
                //Set the last user played.
                lastUser = playerParce->stringList.at(i+1);
                userLvl = playerParce->stringList.at(i+2).toInt();
            }
        }
    }
    //Show the new users name and level on the label.
    ui->usernameLbl->setText(lastUser);
    ui->lvlLbl->setText(QString("Current Level: %1").arg(userLvl));

}
