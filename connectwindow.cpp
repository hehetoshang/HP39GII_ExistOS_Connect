#include "connectwindow.h"
#include "ui_connectwindow.h"
#include "mainwindow.h"
#include <QDebug>

connectwindow::connectwindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::connectwindow)
{
    ui->setupUi(this);
    QStringList devices = scan_device();
    showDevices(devices);
}

connectwindow::~connectwindow()
{
    delete ui;
}

void connectwindow::showDevices(const QStringList& devices)
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

void connectwindow::on_checkBoxSelectAll_stateChanged(int state)
{
    // 根据全选复选框的状态设置所有设备列表项的状态
    Qt::CheckState checkState = (state == Qt::Checked) ? Qt::Checked : Qt::Unchecked;
    for (int i = 0; i < ui->listWidgetDevices->count(); ++i) {
        QListWidgetItem *item = ui->listWidgetDevices->item(i);
        item->setCheckState(checkState);
    }
}

// 新增刷新函数
void connectwindow::refreshDeviceList()
{
    // 清空列表
    ui->listWidgetDevices->clear();

    // 重置全选复选框状态为未选中
    ui->checkBoxSelectAll->setChecked(false);

    // 重新添加三个设备
    QStringList devices = scan_device();
    for (const QString& device : devices) {
        QListWidgetItem *item = new QListWidgetItem(device);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked);
        ui->listWidgetDevices->addItem(item);
    }
}

QStringList connectwindow::scan_device() {
    QStringList devicelist = {"设备 1", "设备 2", "设备 3"};
    return devicelist;
}

void connectwindow::on_pushButtonRefresh_clicked()
{
    // 调用新的刷新函数
    refreshDeviceList();
}

void connectwindow::on_pushButtonCancel_clicked()
{
    // 关闭窗口
    this->close();
}

void connectwindow::on_pushButtonOK_clicked()
{
    // 处理确定按钮点击事件，例如获取选中的设备
    QStringList selectedDevices;
    for (int i = 0; i < ui->listWidgetDevices->count(); ++i) {
        QListWidgetItem *item = ui->listWidgetDevices->item(i);
        if (item->checkState() == Qt::Checked) {
            selectedDevices.append(item->text());
        }
    }

    // 发射信号
    emit selectedDevicesChanged(selectedDevices);

    // 关闭窗口
    this->close();
}
