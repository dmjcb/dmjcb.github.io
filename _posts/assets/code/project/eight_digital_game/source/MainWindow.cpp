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

    m_s_line[0] = ui->originLineEdit0;
    m_s_line[1] = ui->originLineEdit1;
    m_s_line[2] = ui->originLineEdit2;
    m_s_line[3] = ui->originLineEdit3;
    m_s_line[4] = ui->originLineEdit4;
    m_s_line[5] = ui->originLineEdit5;
    m_s_line[6] = ui->originLineEdit6;
    m_s_line[7] = ui->originLineEdit7;
    m_s_line[8] = ui->originLineEdit8;

    m_end_line[0] = ui->endLineEdit0;
    m_end_line[1] = ui->endLineEdit1;
    m_end_line[2] = ui->endLineEdit2;
    m_end_line[3] = ui->endLineEdit3;
    m_end_line[4] = ui->endLineEdit4;
    m_end_line[5] = ui->endLineEdit5;
    m_end_line[6] = ui->endLineEdit6;
    m_end_line[7] = ui->endLineEdit7;
    m_end_line[8] = ui->endLineEdit8;

    ui->label_7->setText(QString::number(ui->horizontalSlider->value()));

    ui->calculatePathButton->setDisabled(true);
    ui->autoOutputPathButton->setDisabled(true);
    ui->horizontalSlider->setDisabled(true);

    ui->displayAfterPathButton->setDisabled(true);
    ui->displayNextPathButton->setDisabled(true);

    set_line_status(m_s_line, true);
    set_line_status(m_end_line, true);

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

bool MainWindow::judge(QString s)
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

void MainWindow::set_line_status(QLineEdit *line[9], bool flag)
{
    for (int i = 0; i < 9; i++)
    {
        line[i]->setReadOnly(flag);
        line[i]->setMaxLength(1);
    }
}

void MainWindow::set_default_input(QString s, QLineEdit *line[9])
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

std::string MainWindow::get_random()
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

void MainWindow::wait_time(int ms)
{
    QEventLoop loop;
    QTimer::singleShot(ms, &loop, &QEventLoop::quit);
    loop.exec();
}

QString MainWindow::splice_str(QLineEdit *line[9])
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

void MainWindow::output_path(int num)
{
    if (num < 0)
    {
        m_step = m_game.m_path.size();
        return;
    }

    if (num >= m_game.m_path.size())
    {
        m_step = 0;

        ui->autoOutputPathButton->setDisabled(false);
        return;
    }

    ClearLine(m_s_line);

    QString now_path = QString::fromStdString(m_game.m_path[num]);

    set_default_input(now_path, m_s_line);

    std::stringstream ss;
    ss << "第" << num + 1 << "步, 共" << m_game.m_path.size() << "步";

    ui->pathLabel->setText(QString::fromStdString(ss.str()));

    ss << ": " << m_game.m_path[num] << std::endl;
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
    if (m_game.m_path.size() == 0)
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

    for (uint32_t i = 0; i < m_game.m_path.size(); i++)
    {
        output_path(i);
        wait_time(10 * (100 - ui->horizontalSlider->value()));
    }

    QMessageBox::warning(NULL, "警告", "已到达,共" + QString::number(m_game.m_path.size()) + "步");

    ui->clearDisplayButton->setDisabled(false);
    ui->displayAfterPathButton->setDisabled(false);
    ui->displayNextPathButton->setDisabled(false);
}

void MainWindow::DoClickedCreateOriginStatusButton()
{
    set_line_status(m_s_line, true);
    set_line_status(m_end_line, true);

    ui->manualInputButton->setDisabled(true);
    ui->autoOutputPathButton->setDisabled(true);

    ui->calculatePathButton->setDisabled(false);

    srand((int)time(0));

    std::string startStr = get_random();
    std::string endStr = get_random();

    while (1)
    {
        if (m_game.is_odevity(startStr, endStr))
        {
            break;
        }
        startStr = get_random();
        endStr = get_random();
    }

    ClearLine(m_s_line);
    ClearLine(m_end_line);

    set_default_input(QString::fromStdString(startStr), m_s_line);
    set_default_input(QString::fromStdString(endStr), m_end_line);
}

void MainWindow::DoClickedManualInputButton()
{
    QMessageBox::warning(NULL, "警告", "请手动输入初始与结束状态");

    set_line_status(m_s_line, false);
    set_line_status(m_end_line, false);

    ui->calculatePathButton->setDisabled(false);
    ui->autoOutputPathButton->setDisabled(true);
}

void MainWindow::DoClickedCalculatePathButton()
{
    m_start_s = splice_str(m_s_line);
    m_end_s = splice_str(m_end_line);

    if (!judge(m_start_s) || !judge(m_end_s))
    {
        QMessageBox::warning(NULL, "警告", "请检查输入的合法性");
        return;
    }

    if (!m_game.is_odevity(m_start_s.toStdString(), m_end_s.toStdString()))
    {
        QMessageBox::warning(NULL, "警告", "不可达请重新输入");

        DoClickedClearDisplayButton();
        return;
    }

    ui->calculatePathButton->setDisabled(true);
    ui->autoOutputPathButton->setDisabled(true);
    ui->manualInputButton->setDisabled(true);

    set_line_status(m_s_line, true);
    set_line_status(m_end_line, true);

    m_game.m_start_config = m_start_s.toStdString();
    m_game.m_end_config = m_end_s.toStdString();

    m_game.find_path();

    QMessageBox::warning(NULL, "警告", "路径已经生成,共" + QString::number(m_game.m_path.size()) + "步");

    ui->autoOutputPathButton->setDisabled(false);
    ui->clearDisplayButton->setDisabled(false);
    ui->displayNextPathButton->setDisabled(false);

    ui->horizontalSlider->setDisabled(false);


    for (int i = 0, size = this->m_game.m_open_table.size(); i < size; i++)
    {
        ui->open_textBrowser->insertPlainText(this->m_game.m_open_table[i] + "\n\n");
    }

    for (int i = 0, size = this->m_game.m_close_table.size(); i < size; i++)
    {
        ui->close_textBrowser->insertPlainText(this->m_game.m_close_table[i] + "\n\n");
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

    ClearLine(m_s_line);
    ClearLine(m_end_line);

    set_line_status(m_s_line, true);
    set_line_status(m_end_line, true);

    ui->pathTextBrowser->clear();
    ui->open_textBrowser->clear();
    ui->close_textBrowser->clear();

    std::vector<State>().swap(m_game.m_open_state);
    std::vector<State>().swap(m_game.m_close_state);
    std::vector<std::string>().swap(m_game.m_path);

    ui->pathLabel->setText("");
}


void MainWindow::DoClickedDisplayAfterPathButton()
{
    m_step--;
    output_path(m_step);
}

void MainWindow::DoClickedDisplayNextPathButton()
{
    ui->displayAfterPathButton->setDisabled(false);

    if (m_step == 0)
    {
        output_path(0);
    }

    m_step++;

    output_path(m_step);
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
