/*
 * @Description:
 * @Version: 1.0
 * @Author: dmjcb
 * @Email: dmjcb@outlook.com
 * @Date: 2022-09-08 23:03:10
 * @LastEditors: dmjcb
 * @LastEditTime: 2024-07-20 01:46:30
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_MainWindow.h"
#include "include/Game.h"

#include <QMainWindow>
#include <QLineEdit>
#include <QTextBrowser>
#include <QMessageBox>
#include <QDebug>
#include <QTime>

#include <vector>
#include <windows.h>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    void ClearLine(QLineEdit *a[9]);

    void SetDefaultInput(QString str, QLineEdit *a[9]);

    void SetInputLineStatus(QLineEdit *line[9], bool flag);

    QString SpliceInputStr(QLineEdit *line[9]);

    std::string CreateRandomStr();

    void WaitTime(int times);

    void OutputPath(int num);

    void OuputTable(QTextBrowser text, std::vector<std::string> v);

    bool JudgeInputValidity(QString s);

private slots:
    void DoClickedAutoOutputButton();

    void DoClickedCreateOriginStatusButton();

    void DoClickedClearDisplayButton();

    void DoClickedCalculatePathButton();

    void DoClickedManualInputButton();

    void DoClickedDisplayAfterPathButton();

    void DoClickedDisplayNextPathButton();

    void DoClickedCloseAppButton();

    void on_horizontalSlider_valueChanged(int value);

    void on_pathTextBrowser_sourceChanged(const QUrl &arg1);

protected:
    Ui::MainWindow *ui;

    QLineEdit *mStartLine[9], *mEndLine[9];

    Game mGame;

    QString mStartInputStr;

    QString mEndInputStr;

    int mRunningStep = 0;
};

#endif
