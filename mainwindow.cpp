#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QVBoxLayout"
#include "QLabel"
#include "QLineEdit"
#include "QScrollArea"
#include <iostream>
#include <chrono>
#include <thread>
#include "QTimer"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("The Fourth Dungeon"); // title of the tab

    QWidget *container = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(container);

    // layout for messages //

    QWidget *messageWidget = new QWidget(this);
    QVBoxLayout *messageLayout = new QVBoxLayout(messageWidget);

    QScrollArea *scroll = new QScrollArea(this);
    scroll->setWidgetResizable(true);
    scroll->setWidget(messageWidget);

    layout->addWidget(scroll);

    // shows player health //
    QLabel *label = new QLabel("press any button to start the game");
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);

    // input //
    QLineEdit *input = new QLineEdit(this);
    input->setAlignment(Qt::AlignCenter);
    layout->addWidget(input);

    connect(input, &QLineEdit::returnPressed, this, [this, input, messageLayout, label] { // when return pressed
    QString userText = input->text();      // capture input

    if(health == 0){
        input->setEnabled(false);
        label->setText("Game Over You Have Lost");
        QTimer::singleShot(5000, qApp, &QApplication::quit);
    }

    if(winPoints == 5){
        input->setEnabled(false);
        label->setText("Game Over You Have Beaten the dungeon congratulations!");
        QTimer::singleShot(5000, qApp, &QApplication::quit);
    }

    if(health > 0 && winPoints < 5) {

        if(monsterAction){
            if(userText.toLower() != "f" & userText.toLower() != "b"){
                QLabel *newLabel = new QLabel("Invalid Input Please Type in B (for blocking) or F (for Fighting)", this);  // show end result
                newLabel->setAlignment(Qt::AlignCenter);
                messageLayout->addWidget(newLabel);
            }
        }
        
        int random = rand() % 3;
        if(random == 0 && !monsterAction){
            QLabel *newLabel = new QLabel("The Goblin does a dance do you attempt to fight back?", this);  // show end result
            newLabel->setAlignment(Qt::AlignCenter);
            messageLayout->addWidget(newLabel);
            dance = true;
            monsterAction = true; 
        }
        if(random == 1 && !monsterAction){
            QLabel *newLabel = new QLabel("The Goblin moves towards you, do you attempt to fight back?", this);  // show end result
            newLabel->setAlignment(Qt::AlignCenter);
            messageLayout->addWidget(newLabel);
            monsterAction = true;
            attack = true;  
        }

        if(random == 2 && !monsterAction){
            QLabel *newLabel = new QLabel("The Goblin charges recklessly towards you, do you attempt to fight back?", this);  // show end result
            newLabel->setAlignment(Qt::AlignCenter);
            messageLayout->addWidget(newLabel);
            monsterAction = true;
            recklessAttack = true; 
        }

        if(!(recklessAttack || attack) && monsterAction){
            if(userText.toLower() == "b"){
                QLabel *newLabel = new QLabel("You block as the goblin moves on", this);  // show end result
                newLabel->setAlignment(Qt::AlignCenter);
                messageLayout->addWidget(newLabel);
                dance = false;
                monsterAction = false;
            }
            if(userText.toLower() == "f"){
                goblinHealth = goblinHealth - 10;
                if(goblinHealth > 0){
                    QLabel *newLabel = new QLabel("Your attack sends the goblin reeling", this);  // show end result
                    newLabel->setAlignment(Qt::AlignCenter);
                    messageLayout->addWidget(newLabel);
                    
                }
                
                if(goblinHealth == 0){
                    winPoints++;
                    if(winPoints < 5){
                        QLabel *newLabel = new QLabel("The Goblin Dies as another takes its place", this);  // show end result
                        newLabel->setAlignment(Qt::AlignCenter);
                        messageLayout->addWidget(newLabel);
                        goblinHealth = 30;
                    }
                    if(winPoints == 5){
                        QLabel *newLabel = new QLabel("Every Goblin from the dungeon has been defeated", this);  // show end result
                        newLabel->setAlignment(Qt::AlignCenter);
                        messageLayout->addWidget(newLabel);
                    }
                }
                dance = false;
                monsterAction = false;
            }
        }

        if(!(dance || attack) && monsterAction){
            if(userText.toLower() == "b"){
                QLabel *newLabel = new QLabel("You try to block but the goblin bypasses your shield as you take ten damage", this);  // show end result
                newLabel->setAlignment(Qt::AlignCenter);
                messageLayout->addWidget(newLabel);
                health = health -10;
                recklessAttack = false;
                monsterAction = false;
            }
            if(userText.toLower() == "f"){
                goblinHealth = goblinHealth - 10;
                if(goblinHealth > 0){
                    QLabel *newLabel = new QLabel("Your attack sends the goblin reeling", this);  // show end result
                    newLabel->setAlignment(Qt::AlignCenter);
                    messageLayout->addWidget(newLabel);
                }

                if(goblinHealth == 0){
                    winPoints++;
                    if(winPoints < 5){
                        QLabel *newLabel = new QLabel("The Goblin Dies as another takes its place", this);  // show end result
                        newLabel->setAlignment(Qt::AlignCenter);
                        messageLayout->addWidget(newLabel);
                        goblinHealth = 30;
                    }
                    if(winPoints == 5){
                        QLabel *newLabel = new QLabel("Every Goblin from the dungeon has been defeated", this);  // show end result
                        newLabel->setAlignment(Qt::AlignCenter);
                        messageLayout->addWidget(newLabel);
                    }
                }
                recklessAttack = false;
                monsterAction = false;
            }
        }

        if(!(recklessAttack || dance) && monsterAction){
            if(userText.toLower() == "b"){
                QLabel *newLabel = new QLabel("You block as the goblin moves on", this);  // show end result
                newLabel->setAlignment(Qt::AlignCenter);
                messageLayout->addWidget(newLabel);
                attack = false;
                monsterAction = false;
            }
            if(userText.toLower() == "f"){
                goblinHealth = goblinHealth - 10;
                if(goblinHealth > 0){
                    QLabel *newLabel = new QLabel("Your attack sends the goblin reeling but the goblin strikes back", this);  // show end result
                    newLabel->setAlignment(Qt::AlignCenter);
                    messageLayout->addWidget(newLabel);
                    health = health - 10;
                }

                if(goblinHealth == 0){
                    winPoints++;
                    if(winPoints < 5){
                        QLabel *newLabel = new QLabel("The Goblin Dies as another takes its place", this);  // show end result
                        newLabel->setAlignment(Qt::AlignCenter);
                        messageLayout->addWidget(newLabel);
                        goblinHealth = 30;
                    }
                    if(winPoints == 5){
                        QLabel *newLabel = new QLabel("Every Goblin from the dungeon has been defeated", this);  // show end result
                        newLabel->setAlignment(Qt::AlignCenter);
                        messageLayout->addWidget(newLabel);
                    }
                }
                attack = false;
                monsterAction = false;
            }
        }

    }
    

    input->clear();
    if(health > 0 && winPoints < 2){
        label->setText("Your current health is " + QString::number(health) + "\n type f to fight back or b to block");//updates health
    }
    

    }); 
    setCentralWidget(container);
}

MainWindow::~MainWindow()
{
    delete ui;
}
