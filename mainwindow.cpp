#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "update.h"  // 添加更新界面头文件
#include "about.h"  // 确保这一行存在
#include "connectwindow.h"
#include "disconnectwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , updateProcess(new QProcess(this)) // 初始化 QProcess 成员变量
{
    ui->setupUi(this);
    initStatusBar();
    initTreeWidget(); // 初始化树形列表
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initStatusBar()
{
    // 设置高度
    statusBar()->setMinimumHeight(25);
    statusBar()->setStyleSheet(QString("QStatusBar::item{border: 1px}")); // 不显示边框

    labelStsIco = new QLabel();
    labelStsStatus = new QLabel();
    pBtnStsConnect = new QPushButton();
    pBtnStsConnect2 = new QPushButton();

    // 新建图标信息（路径为资源文件路径，请自行添加）
    connectIco = new QPixmap(":/image/image/is_connect.svg");
    disconnectIco = new QPixmap(":/image/image/is_not_connect.svg");

    QFont font("Microsoft YaHei", 10);

    labelStsIco->setMaximumSize(16, 16);
    labelStsIco->setScaledContents(true);
    labelStsIco->setPixmap(*this->disconnectIco);
    statusBar()->addWidget(labelStsIco);

    labelStsStatus->setMinimumWidth(100);
    labelStsStatus->setText("未连接设备");//功能未完善
    labelStsStatus->setFont(font);
    statusBar()->addWidget(labelStsStatus);

    //pBtnStsConnect->setFixedSize(88, 20);
    pBtnStsConnect->setIcon(QIcon(":/image/image/update.svg"));
    pBtnStsConnect->setText("检测更新");
    pBtnStsConnect->setFont(font);
    statusBar()->addPermanentWidget(pBtnStsConnect);

    //pBtnStsConnect2->setFixedSize(88, 20);
    pBtnStsConnect2->setIcon(QIcon(":/image/image/about.svg"));
    pBtnStsConnect2->setText("关于");
    pBtnStsConnect2->setFont(font);
    statusBar()->addPermanentWidget(pBtnStsConnect2);

    // 连接按钮的信号与槽
    connect(this->pBtnStsConnect, &QPushButton::clicked, this, &MainWindow::slot_stsbtn_clicked);
    connect(this->pBtnStsConnect2, &QPushButton::clicked, this, &MainWindow::slot_stsbtn_clicked2);
}

void MainWindow::slot_stsbtn_clicked()
{
    // 创建更新窗口实例
    UpdateWidget *updateWindow = new UpdateWidget(this);

    // 设置窗口标志，使其成为独立窗口
    updateWindow->setWindowFlags(Qt::Window);

    // 确保窗口关闭时自动释放内存
    updateWindow->setAttribute(Qt::WA_DeleteOnClose);

    // 显示更新窗口
    updateWindow->show();
}

void MainWindow::slot_stsbtn_clicked2()
{
    // 创建关于窗口实例
    AboutWidget *aboutWindow = new AboutWidget(this);

    // 设置窗口标志，使其成为独立窗口
    aboutWindow->setWindowFlags(Qt::Window);

    // 确保窗口关闭时自动释放内存
    aboutWindow->setAttribute(Qt::WA_DeleteOnClose);

    aboutWindow->show();
}

void MainWindow::slot_treeWidget_contextMenu(const QPoint &pos)
{
    QTreeWidgetItem *item = ui->treeWidget->itemAt(pos);
    if(!item) return;

    QMenu menu;

    // 添加菜单项
    QAction *actionDisconnect = menu.addAction(QIcon(":/image/image/disconnect.svg"), "断开设备");
    QAction *actionRename = menu.addAction(QIcon(":/image/image/rename.svg"), "重命名设备");
    QAction *actionUpdate = menu.addAction(QIcon(":/image/image/update.svg"), "更新设备");
    QAction *actionProperties = menu.addAction(QIcon(":/image/image/properties.svg"), "属性");

    // 连接信号与槽
    /*connect(actionRefresh, &QAction::triggered, this, [this]() {
        initTreeWidget(); // 刷新树形列表
    });*/

    connect(actionProperties, &QAction::triggered, this, [this, item]() {
        // 显示选中项的属性
        QMessageBox::information(this, "属性",
                                QString("选中项: %1").arg(item->text(0)));
    });

    connect(actionUpdate, &QAction::triggered, this, [this, item]() {
        // 显示选中项的属性
        QMessageBox::information(this, "更新设备",
                                 QString("选中项: %1").arg(item->text(0)));
    });

    connect(actionRename, &QAction::triggered, this, [this, item]() {
        // 显示选中项的属性
        QMessageBox::information(this, "重命名设备",
                                 QString("选中项: %1").arg(item->text(0)));
    });

    connect(actionDisconnect, &QAction::triggered, this, [this, item]() {
        // 显示选中项的属性
        QMessageBox::information(this, "断开设备",
                                 QString("选中项: %1").arg(item->text(0)));
    });

    // 显示菜单
    menu.exec(ui->treeWidget->mapToGlobal(pos));
}

// 初始化树形列表（示例数据）
void MainWindow::initTreeWidget()
{
    // 清空现有节点（避免重复添加）
    ui->treeWidget->clear();

    // 隐藏标题栏
    ui->treeWidget->setHeaderHidden(true);

    // 启用右键菜单
    ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->treeWidget, &QTreeWidget::customContextMenuRequested,
            this, &MainWindow::slot_treeWidget_contextMenu);

    // ======================
    // 创建根节点（直接在 UI 中已创建的节点可通过 item(0) 获取）
    // ======================
    // 如果 UI 中已有根节点（如你.ui 中的"EXAMPLE‘s HP39GII"），可以直接获取：
    QTreeWidgetItem *root = ui->treeWidget->invisibleRootItem(); // 获取根节点（所有节点的父节点）
    // 或通过索引获取顶层节点：ui->treeWidget->topLevelItem(0);


    // ======================
    // 示例 2：创建带折叠功能的层级节点
    // ======================
    // 创建第 2 个顶层节点（父节点为 root）
    /*QTreeWidgetItem *node2 = new QTreeWidgetItem(root);
    node2->setText(0, "EXAMPLE");
    node2->setIcon(0, QIcon(":/image/image/folder.svg")); // 文件夹图标

    // 添加子文件夹（初始折叠）
    QTreeWidgetItem *folder = new QTreeWidgetItem(node2);
    folder->setText(0, "程序文件");
    folder->setIcon(0, QIcon(":/image/image/folder.svg"));

    // 在子文件夹中添加文件
    QTreeWidgetItem *file1 = new QTreeWidgetItem(folder);
    file1->setText(0, "解方程程序.prg");
    file1->setIcon(0, QIcon(":/image/image/file.svg"));

    QTreeWidgetItem *file2 = new QTreeWidgetItem(folder);
    file2->setText(0, "统计工具.prg");
    file2->setIcon(0, QIcon(":/image/image/file.svg"));*/


    // ======================
    // 示例 3：操作 UI 中已存在的节点（如你.ui 中的"111"和"222"）
    // ======================
    // 获取 UI 中已创建的节点（通过索引，从 0 开始）
    /*QTreeWidgetItem *existingNode1 = ui->treeWidget->topLevelItem(0); // "111"
    QTreeWidgetItem *existingNode2 = ui->treeWidget->topLevelItem(1); // "222"

    // 为已有节点添加子节点
    if (existingNode1) {
        existingNode1->setText(0, "自定义节点 1"); // 修改文本
        existingNode1->setIcon(0, QIcon(":/image/image/star.svg")); // 修改图标
        QTreeWidgetItem *subNode = new QTreeWidgetItem(existingNode1);
        subNode->setText(0, "这是 UI 中已有节点的子项");
    }

    if (existingNode2) {
        existingNode2->setText(0, "自定义节点 2");
        existingNode2->setIcon(0, QIcon(":/image/image/alert.svg"));
    }*/


    // ======================
    // 通用设置（可选）
    // ======================
    ui->treeWidget->setColumnWidth(0, 180); // 设置列宽
    ui->treeWidget->expandAll(); // 展开所有节点（测试用，正式环境可按需折叠）
}

// 连接检测函数，这里用变量模拟连接状态
bool MainWindow::checkDeviceConnection(const QString& deviceName) {
    // 这里可以替换为实际的连接检测逻辑
    // 暂时用随机数模拟连接状态
    static QMap<QString, bool> deviceConnections;
    if (!deviceConnections.contains(deviceName)) {
        // 使用 QRandomGenerator 生成 0 到 1 之间的随机数
        //deviceConnections[deviceName] = QRandomGenerator::global()->bounded(2) == 0; // 50% 概率连接成功
        deviceConnections[deviceName] = true;
    }
    return deviceConnections[deviceName];
}

// 新增槽函数，用于接收选中的设备列表
void MainWindow::addSelectedDevices(const QStringList& selectedDevices) {
    QTreeWidgetItem *root = ui->treeWidget->invisibleRootItem();

    for (const QString& device : selectedDevices) {
        if (checkDeviceConnection(device)) {
            // 按照模版添加设备到树形列表
            QTreeWidgetItem *node = new QTreeWidgetItem(root);
            node->setText(0, device);
            node->setIcon(0, QIcon(":/image/image/folder.svg"));

            QTreeWidgetItem *folder = new QTreeWidgetItem(node);
            folder->setText(0, "程序文件");
            folder->setIcon(0, QIcon(":/image/image/folder.svg"));

            QTreeWidgetItem *file1 = new QTreeWidgetItem(folder);
            file1->setText(0, "解方程程序.prg");
            file1->setIcon(0, QIcon(":/image/image/file.svg"));

            QTreeWidgetItem *file2 = new QTreeWidgetItem(folder);
            file2->setText(0, "统计工具.prg");
            file2->setIcon(0, QIcon(":/image/image/file.svg"));

            // 展开设备节点及其子文件夹
            node->setExpanded(true);
            folder->setExpanded(true);
        }
    }
    connectedDevices.append(selectedDevices);
}

void MainWindow::on_action_connect_device_triggered()
{
    connectwindow *ConnectWindow = new connectwindow(this);
    // 设置窗口标志，使其成为独立窗口
    ConnectWindow->setWindowFlags(Qt::Window);

    // 确保窗口关闭时自动释放内存
    ConnectWindow->setAttribute(Qt::WA_DeleteOnClose);

    // 连接信号与槽
    connect(ConnectWindow, &connectwindow::selectedDevicesChanged, this, &MainWindow::addSelectedDevices);

    ConnectWindow->show();
}

void MainWindow::on_action_disconnect_device_triggered()
{
    // 创建断开设备窗口实例，将 MainWindow 作为父窗口
    disconnectwindow *disconnectWindow = new disconnectwindow(this);
    // 设置窗口标志，使其成为独立窗口
    disconnectWindow->setWindowFlags(Qt::Window);
    // 确保窗口关闭时自动释放内存
    disconnectWindow->setAttribute(Qt::WA_DeleteOnClose);

    // 连接信号和槽
    connect(disconnectWindow, &disconnectwindow::devicesToDisconnect, this, &MainWindow::removeDisconnectedDevices);

    // 显示断开设备窗口
    disconnectWindow->show();
}

QStringList MainWindow::getConnectedDevices() const
{
    return connectedDevices;
}


void MainWindow::removeDisconnectedDevices(const QStringList& devices) {
    for (const QString& device : devices) {
        connectedDevices.removeAll(device);

        // 从树形列表中移除对应的设备节点
        QTreeWidgetItem *root = ui->treeWidget->invisibleRootItem();
        for (int i = 0; i < root->childCount(); ++i) {
            QTreeWidgetItem *item = root->child(i);
            if (item->text(0) == device) {
                delete item;
                break;
            }
        }
    }
}




void MainWindow::on_action_update_triggered()
{
    // 创建临时目录
    QTemporaryDir tempDir;
    if (!tempDir.isValid()) {
        QMessageBox::critical(this, "错误", "无法创建临时目录");
        return;
    }

    // 定义临时文件路径
    QString tempFilePath = tempDir.path() + "/ExistOS_Updater_v1.1.2.exe";

    // 从资源文件中读取可执行文件
    QFile resourceFile(":/exe/exe/ExistOS_Updater_v1.1.2.exe");
    if (!resourceFile.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "错误", "无法打开资源文件");
        return;
    }

    // 将资源文件内容写入临时文件
    QFile tempFile(tempFilePath);
    if (!tempFile.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(this, "错误", "无法创建临时文件");
        resourceFile.close();
        return;
    }
    tempFile.write(resourceFile.readAll());
    resourceFile.close();
    tempFile.close();

    // 设置临时文件可执行权限（在 Windows 上通常不需要，但保留代码以保持跨平台兼容性）
    tempFile.setPermissions(tempFile.permissions() | QFileDevice::ExeOwner);

    // 使用 startDetached 启动进程
    if (!QProcess::startDetached(tempFilePath)) {
        QMessageBox::critical(this, "错误", "无法启动更新程序");
    }
}

