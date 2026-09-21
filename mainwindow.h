#pragma once

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int health = 100;
    int winPoints = 0;
    bool attack = false;
    bool dance = false;
    bool recklessAttack = false;
    bool monsterAction = false;
    int goblinHealth = 30;
};
