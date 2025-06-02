#ifndef UPDATE_H
#define UPDATE_H

#include <QWidget>
#include <QProcess>

QT_BEGIN_NAMESPACE
namespace Ui { class UpdateWidget; }
QT_END_NAMESPACE

class UpdateWidget : public QWidget
{
    Q_OBJECT

public:
    UpdateWidget(QWidget *parent = nullptr);
    ~UpdateWidget();

private slots:
    void on_startUpdateButton_clicked();
    void on_cancelButton_clicked();
    void on_closeButton_clicked();
    void updateProgress(int value, const QString &message);
    void updateLog(const QString &message);
    void onUpdateFinished(int exitCode, QProcess::ExitStatus exitStatus);

private:
    void checkForUpdates();  // 新增：检查更新的函数

    Ui::UpdateWidget *ui;
    QProcess *updateProcess;
    bool isUpdating;
};
#endif // UPDATE_H
