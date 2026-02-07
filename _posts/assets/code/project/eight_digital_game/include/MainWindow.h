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
#include "include/game.h"

#include <QMainWindow>
#include <QLineEdit>
#include <QTextBrowser>
#include <QMessageBox>
#include <QDebug>
#include <QTimer>

#include <vector>


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

    void set_default_input(QString str, QLineEdit *a[9]);

    void set_line_status(QLineEdit *line[9], bool flag);

    QString splice_str(QLineEdit *line[9]);

    std::string get_random();

    void wait_time(int ms);

    void output_path(int num);

    void output_table(QTextBrowser text, std::vector<std::string> v);

    bool judge(QString s);

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

    QLineEdit *m_s_line[9], *m_end_line[9];

    Game m_game;

    QString m_start_s;

    QString m_end_s;

    int m_step = 0;
};

#endif
