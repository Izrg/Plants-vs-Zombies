#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include <QDialog>
#include "maingame.h"
class mainGame;
namespace Ui {
class PauseMenu;
}

class PauseMenu : public QDialog
{
    Q_OBJECT

public:
    explicit PauseMenu(QWidget *parent = 0, mainGame *rMG = 0);
    mainGame* mG;
    ~PauseMenu();

    void reject();
private slots:
    void on_resumeBtn_clicked();

    void on_saveBtn_clicked();

    void on_restartBtn_clicked();

private:
    Ui::PauseMenu *ui;
};

#endif // PAUSEMENU_H
