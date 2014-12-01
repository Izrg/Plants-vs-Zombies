#ifndef FPARCER_H
#define FPARCER_H
#include <QString>
#include <QFileDialog>
#include <vector>

class Fparcer
{
public:
    Fparcer();
    Fparcer(QString _fName);
    Fparcer(QString _fName,int currentLvl);
    QStringList stringList;

    //Stores the information read from the file.
    int level,rows,startTime,interval;
    double decrement;
    QList<int> sequence;

    void readFile(bool player);
    bool okFile;
    int getLevel();
    std::vector<int> getSequence();
    int getRows();
    int getStartTime();
    int getInterval();
    double getDecrement();
private:
    QString fName;
    QFile openFile;


};

#endif // FPARCER_H
