#pragma once

#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QWidget>
#include <QLineEdit>
#include <QDebug>          // 可选

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

// ---------- 声明 moveDir（三个参数）----------
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

        // 4. 创建六个方向按钮：上、下、左、右、前、后
        QPushButton *upBtn    = new QPushButton("上");
        QPushButton *downBtn  = new QPushButton("下");
        QPushButton *leftBtn  = new QPushButton("左");
        QPushButton *rightBtn = new QPushButton("右");
        QPushButton *frontBtn = new QPushButton("前");
        QPushButton *backBtn  = new QPushButton("后");

        // 5. 创建输入框（放在中间）
        QLineEdit *lineEdit = new QLineEdit;
        lineEdit->setPlaceholderText("输入步长数值...");

        // 6. 辅助 lambda：读取输入框内容并转为 double（失败则返回 0.0）
        auto getValue = [&]() -> double {
            bool ok;
            double val = lineEdit->text().toDouble(&ok);
            return ok ? val : 0.0;
        };

        // 7. 为六个按钮绑定点击事件，分别调用 moveDir 并传入正确参数
        // 上：+X
        QObject::connect(upBtn, &QPushButton::clicked, [=]() {
            double val = getValue();
            moveDir(val, 0.0, 0.0);
        });
        // 下：-X
        QObject::connect(downBtn, &QPushButton::clicked, [=]() {
            double val = getValue();
            moveDir(-val, 0.0, 0.0);
        });
        // 左：+Y
        QObject::connect(leftBtn, &QPushButton::clicked, [=]() {
            double val = getValue();
            moveDir(0.0, val, 0.0);
        });
        // 右：-Y
        QObject::connect(rightBtn, &QPushButton::clicked, [=]() {
            double val = getValue();
            moveDir(0.0, -val, 0.0);
        });
        // 前：+Z
        QObject::connect(frontBtn, &QPushButton::clicked, [=]() {
            double val = getValue();
            moveDir(0.0, 0.0, val);
        });
        // 后：-Z
        QObject::connect(backBtn, &QPushButton::clicked, [=]() {
            double val = getValue();
            moveDir(0.0, 0.0, -val);
        });

        // 8. 布局：使用 3 行 3 列网格，将六个按钮和输入框合理放置
        //   第一行：前、上、后
        //   第二行：左、输入框、右
        //   第三行：空、下、空（或可放置其他控件）
        QGridLayout *directionLayout = new QGridLayout();

        // 第一行
        directionLayout->addWidget(frontBtn, 0, 0, Qt::AlignCenter);
        directionLayout->addWidget(upBtn,    0, 1, Qt::AlignCenter);
        directionLayout->addWidget(backBtn,  0, 2, Qt::AlignCenter);

        // 第二行
        directionLayout->addWidget(leftBtn,  1, 0, Qt::AlignCenter);
        directionLayout->addWidget(lineEdit, 1, 1);
        directionLayout->addWidget(rightBtn, 1, 2, Qt::AlignCenter);

        // 第三行（下按钮单独放在中间）
        directionLayout->addWidget(downBtn,  2, 1, Qt::AlignCenter);

        // 设置拉伸，使所有单元格均匀分布，整体居中
        directionLayout->setColumnStretch(0, 1);
        directionLayout->setColumnStretch(1, 1);
        directionLayout->setColumnStretch(2, 1);
        directionLayout->setRowStretch(0, 1);
        directionLayout->setRowStretch(1, 1);
        directionLayout->setRowStretch(2, 1);

        // 9. 主布局：垂直排列 Reset 按钮 + 方向区域
        QVBoxLayout *mainLayout = new QVBoxLayout();
        mainLayout->addWidget(resetBtn);
        mainLayout->addLayout(directionLayout);

        window.setLayout(mainLayout);

        // 10. 显示窗口
        window.show();

        // 11. 进入事件循环
        app.exec();
    }
};