#ifndef DISCONNECTWINDOW_H
#define DISCONNECTWINDOW_H

#include <QWidget>

namespace Ui {
class disconnectwindow;
}

class disconnectwindow : public QWidget
{
    Q_OBJECT

public:
    explicit disconnectwindow(QWidget *parent = nullptr);
    ~disconnectwindow();

signals:
    // 定义信号，用于发送要断开的设备列表
    void devicesToDisconnect(const QStringList& devices);

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
    Ui::disconnectwindow *ui;
    void showConnectedDevices(const QStringList& devices);
    void refreshConnectedDeviceList();
};

#endif // DISCONNECTWINDOW_H
