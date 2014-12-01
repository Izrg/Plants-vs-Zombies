#include "pausemenu.h"
#include "ui_pausemenu.h"
#include <QFile>
#include <QDateTime>
#include <QMessageBox>

PauseMenu::PauseMenu(QWidget *parent, mainGame *rMG) :
    QDialog(parent),
    ui(new Ui::PauseMenu)
{
    ui->setupUi(this);
    mG = rMG;
    //Grab the mouse, grab the keybaord. //DOESNT WORK, NEED TO FIX MAYBE
    //this->setFocus();
    //this->grabMouse();
    //this->grabKeyboard();

}


PauseMenu::~PauseMenu()
{
    delete ui;
}

void PauseMenu::reject()
{
    //Release the mouse and keyboard
    //this->releaseKeyboard();
    //this->releaseMouse();
    mG->on_menuBtn_clicked(); // Resume the game.
}

void PauseMenu::on_resumeBtn_clicked()
{
    //Release the mouse and keyboard
    //this->releaseKeyboard();
    //this->releaseMouse();
    mG->on_menuBtn_clicked(); // Resume the game.
}

void PauseMenu::on_saveBtn_clicked()
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
            //If this line doesnt contain the users name, rewrite it
            if(!line.contains(mG->name))
            {
                s.append(line + "\n");
                continue;
            }
            //Else write the users new data.
            int time = QDateTime::currentDateTime().toTime_t();
            //Append the new user timestamp and level.
            s.append(QString("%1").arg(time) + ":" + mG->name + ":" + QString("%1").arg(mG->currentLevel) + "\n");
        }
        //re-write the file with the new user's saved data.
        save_file.resize(0);
        t << s;
        save_file.close();

    }

    QMessageBox::information(this,"Saved!", "Your game has been saved!"); // Prompt the user that their game has been saved.
}

void PauseMenu::on_restartBtn_clicked()
{
   mG->mW->restartGame();

}
