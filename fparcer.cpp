#include "fparcer.h"
#include <iostream>
#include <QTextStream>
#include <QDebug>


Fparcer::Fparcer()
{
}

Fparcer::Fparcer(QString _fName)
{
    if(_fName.isEmpty()){

        return;
    }

    fName = _fName;
}

Fparcer::Fparcer(QString _fName, int currentLvl)
{
    if(_fName.isEmpty()){

        return;
    }

    fName = _fName;
    level = currentLvl;
}


void Fparcer::readFile(bool player)
{
    QFile openFile;


    openFile.setFileName(fName);
    openFile.open(QIODevice::ReadOnly);
    QTextStream in (&openFile);
    QString line = in.readAll();

    stringList = line.split(QRegExp("[\r\n:\"]"),QString::SkipEmptyParts);
    if(player)
    {
        for(int i = 0; i < stringList.size(); i++)
        {

        }
        return;
    }

    //qDebug() << "Reading line: " << stringList << endl;
    //For loop for the levels.txt
    for(int i = 0; i < stringList.size(); i++)
    {
        if((i % 6) == 0)
        {
            if(stringList.at(i).toInt() == level)
            {
                //Split the "sequence" into its own substring
                QString tempLine = stringList.at(i+1);
                QStringList tempList = tempLine.split(QRegExp("[\r\n,\"]"),QString::SkipEmptyParts);
                for(int j =0; j < tempList.size(); j ++)
                {
                    //qDebug() << "Sequence: " << tempList.at(j).toInt() << endl;
                    sequence.append(tempList.at(j).toInt());

                }
                //qDebug() << "Level: " << level << endl;
                rows = stringList.at(i+2).toInt();
                //qDebug() << "Rows: " << rows << endl;
                startTime = stringList.at(i+3).toInt();
                //qDebug() << "start time: " << startTime << endl;
                interval = stringList.at(i+4).toInt();
                //qDebug() << "interval: " << interval << endl;
                decrement = stringList.at(i+5).toDouble();
                //qDebug() << "decrement: " << decrement << endl;
                return;
            }
        }
    }
}

int Fparcer::getLevel()
{

}

std::vector<int> Fparcer::getSequence()
{

}

int Fparcer::getRows()
{

}

int Fparcer::getStartTime()
{

}

int Fparcer::getInterval()
{

}

double Fparcer::getDecrement()
{

}
