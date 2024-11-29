#include "include/MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 窗口透明度
    setWindowOpacity(0.97);
    //  禁止最大化按钮
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
    //  设置拖动窗口大小,这样的操作会使页面无法最大化;x,y 宽,长
    setFixedSize(960, 825);

    mStartLine[0] = ui->originLineEdit0;
    mStartLine[1] = ui->originLineEdit1;
    mStartLine[2] = ui->originLineEdit2;
    mStartLine[3] = ui->originLineEdit3;
    mStartLine[4] = ui->originLineEdit4;
    mStartLine[5] = ui->originLineEdit5;
    mStartLine[6] = ui->originLineEdit6;
    mStartLine[7] = ui->originLineEdit7;
    mStartLine[8] = ui->originLineEdit8;

    mEndLine[0] = ui->endLineEdit0;
    mEndLine[1] = ui->endLineEdit1;
    mEndLine[2] = ui->endLineEdit2;
    mEndLine[3] = ui->endLineEdit3;
    mEndLine[4] = ui->endLineEdit4;
    mEndLine[5] = ui->endLineEdit5;
    mEndLine[6] = ui->endLineEdit6;
    mEndLine[7] = ui->endLineEdit7;
    mEndLine[8] = ui->endLineEdit8;

    ui->label_7->setText(QString::number(ui->horizontalSlider->value()));

    ui->calculatePathButton->setDisabled(true);
    ui->autoOutputPathButton->setDisabled(true);
    ui->horizontalSlider->setDisabled(true);

    ui->displayAfterPathButton->setDisabled(true);
    ui->displayNextPathButton->setDisabled(true);

    SetInputLineStatus(mStartLine, true);
    SetInputLineStatus(mEndLine, true);

    ui->pathLabel->setText("");

    connect(ui->autoOutputPathButton, SIGNAL(clicked()), this, SLOT(DoClickedAutoOutputButton()));
    connect(ui->calculatePathButton, SIGNAL(clicked()), this, SLOT(DoClickedCalculatePathButton()));
    connect(ui->displayAfterPathButton, SIGNAL(clicked()), this, SLOT(DoClickedDisplayAfterPathButton()));
    connect(ui->displayNextPathButton, SIGNAL(clicked()), this, SLOT(DoClickedDisplayNextPathButton()));
    connect(ui->clearDisplayButton, SIGNAL(clicked()), this, SLOT(DoClickedClearDisplayButton()));
    connect(ui->createOriginStatusButton, SIGNAL(clicked()), this, SLOT(DoClickedCreateOriginStatusButton()));
    connect(ui->manualInputButton, SIGNAL(clicked()), this, SLOT(DoClickedManualInputButton()));
    connect(ui->closeAppButton, SIGNAL(clicked()), this, SLOT(DoClickedCloseAppButton()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::JudgeInputValidity(QString s)
{
    if (s.size() < 9)
    {
        return false;
    }

    int a[10] = {-1};

    std::string v = s.toStdString();

    for (int i = 0; i < 9; i++)
    {
        // 若包含非数字
        if (v[i] < 48 || v[i] > 57)
        {
            return false;
        }
        a[v[i] - '0'] = 1;
    }
    // 判断0-9数字是否都出现了
    for (int i = 0; i < 9; i++)
    {
        if (a[i] == -1)
        {
            return false;
        }
    }
    return true;
}

void MainWindow::SetInputLineStatus(QLineEdit *line[9], bool flag)
{
    for (int i = 0; i < 9; i++)
    {
        line[i]->setReadOnly(flag);
        line[i]->setMaxLength(1);
    }
}

void MainWindow::SetDefaultInput(QString s, QLineEdit *line[9])
{
    for (int i = 0; i < 9; i++)
    {
        if (s[i] != '0')
        {
            line[i]->setText(s.mid(i, 1));
        }
        else
        {
            line[i]->setText(" ");
        }
    }
}

std::string MainWindow::CreateRandomStr()
{
    std::string targetStr = "";
    bool isExist = false;
    while (targetStr.size() < 9)
    {
        char a = (rand() % 9) + '0';
        isExist = false;
        for (int i = 0; i < targetStr.size(); i++)
        {
            // 该字符已存在
            if (targetStr[i] == a)
            {
                isExist = true;
                break;
            }
        }

        if (isExist == false)
        {
            targetStr += a;
        }
    }
    return targetStr;
}

void MainWindow::WaitTime(int times)
{
    QElapsedTimer t;
    t.start();
    while (t.elapsed() < times)
    {
        QCoreApplication::processEvents();
    }
}

QString MainWindow::SpliceInputStr(QLineEdit *line[9])
{
    QString s = "";
    for (int i = 0; i < 9; i++)
    {
        if (line[i]->text() == " ")
        {
            s += '0';
        }
        else
        {
            s += line[i]->text();
        }
    }
    return s;
}

void MainWindow::OutputPath(int num)
{
    if (num < 0)
    {
        mRunningStep = mGame.mPath.size();
        return;
    }

    if (num >= mGame.mPath.size())
    {
        mRunningStep = 0;

        ui->autoOutputPathButton->setDisabled(false);
        return;
    }

    ClearLine(mStartLine);

    QString nowPath = QString::fromStdString(mGame.mPath[num]);

    SetDefaultInput(nowPath, mStartLine);

    std::stringstream ss;
    ss << "第" << num + 1 << "步, 共" << mGame.mPath.size() << "步";

    ui->pathLabel->setText(QString::fromStdString(ss.str()));

    ss << ": " << mGame.mPath[num] << std::endl;
    ui->pathTextBrowser->insertPlainText(QString::fromStdString(ss.str()));

    ss.str("");
    ss.clear();
}

void MainWindow::ClearLine(QLineEdit *line[9])
{
    for (int i = 0; i < 9; i++)
    {
        line[i]->clear();
    }
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void MainWindow::DoClickedAutoOutputButton()
{
    if (mGame.mPath.size() == 0)
    {
        QMessageBox::warning(NULL, "警告", "请先生成路径");
        return;
    }

    ui->pathTextBrowser->clear();

    ui->clearDisplayButton->setDisabled(true);
    ui->calculatePathButton->setDisabled(true);
    ui->autoOutputPathButton->setDisabled(true);
    ui->displayAfterPathButton->setDisabled(true);
    ui->displayNextPathButton->setDisabled(true);

    for (uint32_t i = 0; i < mGame.mPath.size(); i++)
    {
        OutputPath(i);
        WaitTime(10 * (100 - ui->horizontalSlider->value()));
    }

    QMessageBox::warning(NULL, "警告", "已到达,共" + QString::number(mGame.mPath.size()) + "步");

    ui->clearDisplayButton->setDisabled(false);
    ui->displayAfterPathButton->setDisabled(false);
    ui->displayNextPathButton->setDisabled(false);
}

void MainWindow::DoClickedCreateOriginStatusButton()
{
    SetInputLineStatus(mStartLine, true);
    SetInputLineStatus(mEndLine, true);

    ui->manualInputButton->setDisabled(true);
    ui->autoOutputPathButton->setDisabled(true);

    ui->calculatePathButton->setDisabled(false);

    srand((int)time(0));

    std::string startStr = CreateRandomStr();
    std::string endStr = CreateRandomStr();

    while (1)
    {
        if (mGame.IsOdevity(startStr, endStr))
        {
            break;
        }
        startStr = CreateRandomStr();
        endStr = CreateRandomStr();
    }

    ClearLine(mStartLine);
    ClearLine(mEndLine);

    SetDefaultInput(QString::fromStdString(startStr), mStartLine);
    SetDefaultInput(QString::fromStdString(endStr), mEndLine);
}

void MainWindow::DoClickedManualInputButton()
{
    QMessageBox::warning(NULL, "警告", "请手动输入初始与结束状态");

    SetInputLineStatus(mStartLine, false);
    SetInputLineStatus(mEndLine, false);

    ui->calculatePathButton->setDisabled(false);
    ui->autoOutputPathButton->setDisabled(true);
}

void MainWindow::DoClickedCalculatePathButton()
{
    mStartInputStr = SpliceInputStr(mStartLine);
    mEndInputStr = SpliceInputStr(mEndLine);

    if (!JudgeInputValidity(mStartInputStr) || !JudgeInputValidity(mEndInputStr))
    {
        QMessageBox::warning(NULL, "警告", "请检查输入的合法性");
        return;
    }

    if (!mGame.IsOdevity(mStartInputStr.toStdString(), mEndInputStr.toStdString()))
    {
        QMessageBox::warning(NULL, "警告", "不可达请重新输入");

        DoClickedClearDisplayButton();
        return;
    }

    ui->calculatePathButton->setDisabled(true);
    ui->autoOutputPathButton->setDisabled(true);
    ui->manualInputButton->setDisabled(true);

    SetInputLineStatus(mStartLine, true);
    SetInputLineStatus(mEndLine, true);

    mGame.mStartConfiguration = mStartInputStr.toStdString();
    mGame.mEndConfiguration = mEndInputStr.toStdString();

    mGame.FindPath();

    QMessageBox::warning(NULL, "警告", "路径已经生成,共" + QString::number(mGame.mPath.size()) + "步");

    ui->autoOutputPathButton->setDisabled(false);
    ui->clearDisplayButton->setDisabled(false);
    ui->displayNextPathButton->setDisabled(false);

    ui->horizontalSlider->setDisabled(false);


    for (int i = 0, size = this->mGame.mOpenTable.size(); i < size; i++)
    {
        ui->open_textBrowser->insertPlainText(this->mGame.mOpenTable[i] + "\n\n");
    }

    for (int i = 0, size = this->mGame.mCloseTable.size(); i < size; i++)
    {
        ui->close_textBrowser->insertPlainText(this->mGame.mCloseTable[i] + "\n\n");
    }
}

void MainWindow::DoClickedClearDisplayButton()
{
    ui->calculatePathButton->setDisabled(true);
    ui->autoOutputPathButton->setDisabled(true);
    ui->displayAfterPathButton->setDisabled(true);
    ui->displayNextPathButton->setDisabled(true);

    ui->horizontalSlider->setDisabled(true);

    ui->autoOutputPathButton->setDisabled(false);
    ui->manualInputButton->setDisabled(false);

    ui->horizontalSlider->setValue(50);

    ClearLine(mStartLine);
    ClearLine(mEndLine);

    SetInputLineStatus(mStartLine, true);
    SetInputLineStatus(mEndLine, true);

    ui->pathTextBrowser->clear();
    ui->open_textBrowser->clear();
    ui->close_textBrowser->clear();

    std::vector<State>().swap(mGame.mOpenState);
    std::vector<State>().swap(mGame.mCloseState);
    std::vector<std::string>().swap(mGame.mPath);

    ui->pathLabel->setText("");
}


void MainWindow::DoClickedDisplayAfterPathButton()
{
    mRunningStep--;
    OutputPath(mRunningStep);
}

void MainWindow::DoClickedDisplayNextPathButton()
{
    ui->displayAfterPathButton->setDisabled(false);

    if (mRunningStep == 0)
    {
        OutputPath(0);
    }

    mRunningStep++;

    OutputPath(mRunningStep);
}

void MainWindow::DoClickedCloseAppButton()
{
    QMessageBox box;
    box.setText("提示");
    box.setInformativeText("确实要退出吗?");
    box.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    box.setDefaultButton(QMessageBox::Ok);

    if (box.exec() == QMessageBox::Ok)
    {
        QApplication::exit();
    }
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    ui->label_7->setText(QString::number(value));
}

void MainWindow::on_pathTextBrowser_sourceChanged(const QUrl &arg1)
{
    ui->pathTextBrowser->moveCursor(QTextCursor::End);
}
// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
