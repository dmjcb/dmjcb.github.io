/*
 * @Description:
 * @Version: 1.0
 * @Author: dmjcb
 * @Email: dmjcb@outlook.com
 * @Date: 2022-09-08 23:03:10
 * @LastEditors: dmjcb
 * @LastEditTime: 2024-07-19 17:45:14
 */
#include "include/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

    w.setWindowTitle("八数码");
    w.setWindowIcon(QIcon(":eight.ico"));

    w.show();

    return a.exec();
}
