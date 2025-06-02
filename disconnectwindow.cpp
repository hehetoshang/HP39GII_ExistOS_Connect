#include "disconnectwindow.h"
#include "ui_disconnectwindow.h"
#include <QDebug>
#include "mainwindow.h"

disconnectwindow::disconnectwindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::disconnectwindow)
{
    ui->setupUi(this);

    MainWindow *mainWindow = qobject_cast<MainWindow*>(parent);
    if (mainWindow) {
        QStringList connectedDevices = mainWindow->getConnectedDevices();
        showConnectedDevices(connectedDevices);
    }
}

void disconnectwindow::refreshConnectedDeviceList()
{
    // 清空列表
    ui->listWidgetDevices->clear();

    // 重置全选复选框状态为未选中
    ui->checkBoxSelectAll->setChecked(false);

    MainWindow *mainWindow = qobject_cast<MainWindow*>(this->parent());
    if (mainWindow) {
        QStringList connectedDevices = mainWindow->getConnectedDevices();
        for (const QString& device : connectedDevices) {
            QListWidgetItem *item = new QListWidgetItem(device);
            item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
            item->setCheckState(Qt::Unchecked);
            ui->listWidgetDevices->addItem(item);
        }
    }
}

disconnectwindow::~disconnectwindow()
{
    delete ui;
}

void disconnectwindow::showConnectedDevices(const QStringList& devices)
{
    // 清空之前的设备列表
    ui->listWidgetDevices->clear();

    // 为每个设备创建一个列表项并添加到列表中
    for (const QString& device : devices) {
        QListWidgetItem *item = new QListWidgetItem(device);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked);
        ui->listWidgetDevices->addItem(item);
    }
}

void disconnectwindow::on_checkBoxSelectAll_stateChanged(int state)
{
    // 根据全选复选框的状态设置所有设备列表项的状态
    Qt::CheckState checkState = (state == Qt::Checked) ? Qt::Checked : Qt::Unchecked;
    for (int i = 0; i < ui->listWidgetDevices->count(); ++i) {
        QListWidgetItem *item = ui->listWidgetDevices->item(i);
        item->setCheckState(checkState);
    }
}

void disconnectwindow::on_pushButtonRefresh_clicked()
{
    // 调用新的刷新函数
    refreshConnectedDeviceList();
}

void disconnectwindow::on_pushButtonCancel_clicked()
{
    // 关闭窗口
    this->close();
}

void disconnectwindow::on_pushButtonOK_clicked()
{
    // 处理确定按钮点击事件，例如获取选中的设备
    QStringList devicesToDisconnectList;
    for (int i = 0; i < ui->listWidgetDevices->count(); ++i) {
        QListWidgetItem *item = ui->listWidgetDevices->item(i);
        if (item->checkState() == Qt::Checked) {
            devicesToDisconnectList.append(item->text());
        }
    }

    // 发射信号
    emit devicesToDisconnect(devicesToDisconnectList);

    // 关闭窗口
    this->close();
}
