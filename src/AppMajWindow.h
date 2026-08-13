#pragma once

#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QWidget>
#include <QLineEdit>
#include <QDebug>
#include <iostream>
#include <cmath>          // 用于 M_PI 等

#include "Robot.h"
#include "MoveCommander.h"

// ---------- 原有函数 ----------
void printEnc()
{
    int absshift23[8] = { 0 };
    std::cout << std::endl << "enc:";
    for (int i = 0; i < 8; i++)
    {
        controlSystem::GetAbsEncValue(&absshift23[i], i);
        std::cout << absshift23[i] << ",";
    }
    std::cout << "end" << std::endl;
}

// ---------- 平移命令（原有）----------
void moveDir(double x, double y, double z){
    if(std::abs(x)>100||std::abs(y)>100 
    ||std::abs(z)>100){
        std::cout<<"Warning: move step too large!"<<std::endl;
        return;
    }
    std::cout<<"moved "<<controlSystem::JogLine(x, y, z)<<std::endl;
}

// ---------- 主窗口类 ----------
class AppMajWindow {
public:
    AppMajWindow() {
        int   Pusle[8] = { 131072, 131072, 131072, 131072, 131072, 131072, 131072, 131072 };
        double Pitch[8] = { 10,			16.66,    124.54,	2 * M_PI,		2 * M_PI,2 * M_PI,20 ,2 * M_PI };
        double Ratio[8] = { 1,			 1,			20,     50,			30,   1,     1,      1 };
        double HLimit[8] = { 400,  200,   10,  M_PI / 2,   M_PI / 4,    2 * M_PI + 0.5 ,  2.5 * M_PI , 20 };
        double LLimit[8] = { -400,  -200,  -400, -M_PI / 2,   -M_PI / 4,    -2 * M_PI - 0.5 , -2.5 * M_PI ,-20 };
        int dirReverse[8] = { 0,0,0,0,0,0,0,0 };
        int wAxisMap[8] = { 0,1,2,3,4,-1,-1, -1 };
        int Encvalue0[8] = { 132282,-1184821,-2421091,7450751,70946,0,0,0 };
        int wAxisMirror[8] = { -1,-1,-1,-1,-1,-1 ,-1,-1 };

        controlSystem::InitSystem(Ratio, Pitch, Pusle, HLimit, LLimit, dirReverse, wAxisMap, wAxisMirror);
        printEnc();
        controlSystem::SetAbsPos(Encvalue0, Ratio, Pitch, Pusle, wAxisMap);
        controlSystem::SetFeedSpeed(2);
    }

    ~AppMajWindow() {
        controlSystem::CloseSystem();
    }

    void ShowMajWindow() {
        // 1. 创建 QApplication（原有方式）
        int argc = 0;
        char *argv[] = { nullptr };
        QApplication app(argc, argv);

        // 2. 主窗口
        QWidget window;
        window.setWindowTitle("Controller");

        // 3. Reset Position 按钮
        QPushButton *resetBtn = new QPushButton("Reset Position");
        QObject::connect(resetBtn, &QPushButton::clicked, [=]() {
            controlSystem::GoHome(1);
        });

        // 4. 创建平移按钮：+x、-x、+y、-y、+z、-z
        QPushButton *xPlusBtn    = new QPushButton("+x");
        QPushButton *xMinusBtn   = new QPushButton("-x");
        QPushButton *yPlusBtn    = new QPushButton("+y");
        QPushButton *yMinusBtn   = new QPushButton("-y");
        QPushButton *zPlusBtn    = new QPushButton("+z");
        QPushButton *zMinusBtn   = new QPushButton("-z");

        // 5. 创建旋转按钮：+ry、-ry、+rz、-rz
        QPushButton *ryPlusBtn   = new QPushButton("+ry");
        QPushButton *ryMinusBtn  = new QPushButton("-ry");
        QPushButton *rzPlusBtn   = new QPushButton("+rz");
        QPushButton *rzMinusBtn  = new QPushButton("-rz");

        // 6. 创建输入框（所有按钮共用此输入框） 
        QLineEdit *lineEdit = new QLineEdit;
        lineEdit->setPlaceholderText("输入速度(mm/s)...");

        QLineEdit *dirEdit = new QLineEdit;
        dirEdit->setPlaceholderText("输入方向(度/s)...");

        // 7. 辅助 lambda：读取输入框内容并转为 double（失败则返回 0.0）
        auto getValue = [&]() -> double {
            bool ok;
            double val = lineEdit->text().toDouble(&ok);
            return ok ? val : 0.0;
        };
        auto getDirValue = [&]() -> double {
            bool ok;
            double val = dirEdit->text().toDouble(&ok);
            return ok ? val : 0.0;
        };

        // ---------- 绑定平移按钮（调用 moveDir）----------
        QObject::connect(xPlusBtn, &QPushButton::clicked, [=]() {
            double val = getValue();
            moveDir(val, 0.0, 0.0);
        });
        QObject::connect(xMinusBtn, &QPushButton::clicked, [=]() {
            double val = getValue();
            moveDir(-val, 0.0, 0.0);
        });
        QObject::connect(yPlusBtn, &QPushButton::clicked, [=]() {
            double val = getValue();
            moveDir(0.0, val, 0.0);
        });
        QObject::connect(yMinusBtn, &QPushButton::clicked, [=]() {
            double val = getValue();
            moveDir(0.0, -val, 0.0);
        });
        QObject::connect(zPlusBtn, &QPushButton::clicked, [=]() {
            double val = getValue();
            moveDir(0.0, 0.0, val);
        });
        QObject::connect(zMinusBtn, &QPushButton::clicked, [=]() {
            double val = getValue();
            moveDir(0.0, 0.0, -val);
        });

        // ---------- 绑定旋转按钮（调用 controlSystem::JogDir）----------
        QObject::connect(ryPlusBtn, &QPushButton::clicked, [=]() {
            double val = getDirValue();
            controlSystem::JogDir(val, 0.0);   // ry 增加
        });
        QObject::connect(ryMinusBtn, &QPushButton::clicked, [=]() {
            double val = getDirValue();
            controlSystem::JogDir(-val, 0.0);  // ry 减少
        });
        QObject::connect(rzPlusBtn, &QPushButton::clicked, [=]() {
            double val = getDirValue();
            controlSystem::JogDir(0.0, val);   // rz 增加
        });
        QObject::connect(rzMinusBtn, &QPushButton::clicked, [=]() {
            double val = getDirValue();
            controlSystem::JogDir(0.0, -val);  // rz 减少
        });

        // ------------------------------------------------------------
        // 8. 布局设计：两行水平布局，第一行平移按钮+输入框，第二行旋转按钮
        // ------------------------------------------------------------
        // 第一行：平移按钮 + 输入框
        QHBoxLayout *row1 = new QHBoxLayout();
        row1->addWidget(xPlusBtn);
        row1->addWidget(xMinusBtn);
        row1->addWidget(yPlusBtn);
        row1->addWidget(yMinusBtn);
        row1->addWidget(zPlusBtn);
        row1->addWidget(zMinusBtn);
        row1->addWidget(lineEdit);   // 输入框放在第一行末尾
        row1->setSpacing(6);
        row1->setContentsMargins(10, 5, 10, 5);

        // 第二行：旋转按钮（居中显示）
        QHBoxLayout *row2 = new QHBoxLayout();
        row2->addWidget(ryPlusBtn);
        row2->addWidget(ryMinusBtn);
        row2->addWidget(rzPlusBtn);
        row2->addWidget(rzMinusBtn);
        row2->addWidget(dirEdit);   // 输入框放在第二行末尾
        row2->setSpacing(6);
        row2->setContentsMargins(10, 5, 10, 5);
        // 让第二行居中对齐
        row2->setAlignment(Qt::AlignCenter);

        // 9. 主布局：垂直排列 Reset 按钮 + 两行
        QVBoxLayout *mainLayout = new QVBoxLayout();
        mainLayout->addWidget(resetBtn);
        mainLayout->addLayout(row1);
        mainLayout->addLayout(row2);
        // 让两行水平布局在垂直方向上居中（可选）
        mainLayout->setAlignment(row1, Qt::AlignCenter);
        mainLayout->setAlignment(row2, Qt::AlignCenter);

        window.setLayout(mainLayout);

        // 10. 显示窗口
        window.show();

        // 11. 进入事件循环
        app.exec();
    }
};