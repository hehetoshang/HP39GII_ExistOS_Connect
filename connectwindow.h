#ifndef CONNECTWINDOW_H
#define CONNECTWINDOW_H

#include <QWidget>
#include <QStringList>

namespace Ui {
class connectwindow;
}

class connectwindow : public QWidget
{
    Q_OBJECT

public:
    explicit connectwindow(QWidget *parent = nullptr);
    ~connectwindow();
    void showDevices(const QStringList& devices);
    // 声明新的刷新函数
    void refreshDeviceList();

    QStringList scan_device();

signals:
    // 定义信号，用于发送选中的设备列表
    void selectedDevicesChanged(const QStringList& selectedDevices);

private slots:
    // 全选复选框状态改变时的槽函数
    void on_checkBoxSelectAll_stateChanged(int state);
    // 刷新按钮点击时的槽函数
    void on_pushButtonRefresh_clicked();
    // 取消按钮点击时的槽函数
    void on_pushButtonCancel_clicked();
    // 确定按钮点击时的槽函数
    void on_pushButtonOK_clicked();

private:
    Ui::connectwindow *ui;
};

#endif // CONNECTWINDOW_H
