#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QMenu>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QTemporaryDir>
#include <QIODevice>
#include <QProcess>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // 连接检测函数
    bool checkDeviceConnection(const QString& deviceName);

    // 新增槽函数，用于接收选中的设备列表，将访问权限改为 public
    void addSelectedDevices(const QStringList& selectedDevices);
    QStringList getConnectedDevices() const;

public slots:
    void removeDisconnectedDevices(const QStringList& devices);

private:
    void initStatusBar();
    void initTreeWidget(); // 新增初始化树形列表函数

private slots:
    void slot_stsbtn_clicked();
    void slot_stsbtn_clicked2();
    void slot_treeWidget_contextMenu(const QPoint &pos);
    void on_action_connect_device_triggered();
    void on_action_disconnect_device_triggered();

    void on_action_update_triggered();

private:
    Ui::MainWindow *ui;
    // 存储连接的设备列表
    QStringList connectedDevices;
    QPixmap* connectIco;                // 图片：已连接
    QPixmap* disconnectIco;             // 图片：断开连接
    //QLabel* labelStsInfo;               // 状态栏提示信息
    //QLabel* labelStsIP;            // IP信息
    QLabel* labelStsIco;           // 状态图标
    QLabel* labelStsStatus;        // 状态信息
    QPushButton* pBtnStsConnect;	// 重连按钮
    QPushButton* pBtnStsConnect2;
    QProcess *updateProcess; // 添加 QProcess 成员变量
};
#endif // MAINWINDOW_H
