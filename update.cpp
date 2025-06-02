#include "update.h"
#include "ui_update.h"
#include <QMessageBox>
#include <QDateTime>

UpdateWidget::UpdateWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UpdateWidget)
    , isUpdating(false)
{
    ui->setupUi(this);

    // 初始化更新进程
    updateProcess = new QProcess(this);
    connect(updateProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, &UpdateWidget::onUpdateFinished);
    connect(updateProcess, &QProcess::readyReadStandardOutput, [this]() {
        updateLog(updateProcess->readAllStandardOutput());
    });
    connect(updateProcess, &QProcess::readyReadStandardError, [this]() {
        updateLog(updateProcess->readAllStandardError());
    });

    // 设置初始UI状态
    ui->startUpdateButton->setEnabled(false);
    ui->cancelButton->setEnabled(false);
    ui->closeButton->setEnabled(false);

    // 自动开始检查更新
    checkForUpdates();
}

UpdateWidget::~UpdateWidget()
{
    delete ui;
}

void UpdateWidget::checkForUpdates()
{
    updateProgress(0, "正在检查更新...");
    updateLog("开始检查软件更新...");

    // 启动检查更新的进程（实际应用中应替换为真实的检查更新逻辑）
    updateProcess->start("python", QStringList() << "check_update.py");
}

void UpdateWidget::on_startUpdateButton_clicked()
{
    if (isUpdating) {
        return;
    }

    // 确认对话框
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "确认更新", "确定要开始更新吗？",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply != QMessageBox::Yes) {
        return;
    }

    // 开始更新
    isUpdating = true;
    ui->startUpdateButton->setEnabled(false);
    ui->cancelButton->setEnabled(true);
    ui->closeButton->setEnabled(false);

    updateProgress(0, "准备更新...");
    updateLog("开始下载更新文件...");

    // 启动更新进程（实际应用中应替换为真实的更新逻辑）
    updateProcess->start("python", QStringList() << "update_script.py");
}

void UpdateWidget::on_cancelButton_clicked()
{
    if (!isUpdating) {
        close();
        return;
    }

    // 确认取消
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "取消更新", "确定要取消更新吗？",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply != QMessageBox::Yes) {
        return;
    }

    // 停止更新
    if (updateProcess->state() == QProcess::Running) {
        updateProcess->terminate();
        if (!updateProcess->waitForFinished(3000)) {
            updateProcess->kill();
        }
    }

    updateProgress(0, "更新已取消");
    isUpdating = false;
    ui->startUpdateButton->setEnabled(true);
    ui->cancelButton->setEnabled(false);
    ui->closeButton->setEnabled(true);
}

void UpdateWidget::on_closeButton_clicked()
{
    close();
}

void UpdateWidget::updateProgress(int value, const QString &message)
{
    ui->progressBar->setValue(value);
    ui->statusLabel->setText(message);
}

void UpdateWidget::updateLog(const QString &message)
{
    QString timeStamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    ui->logTextEdit->append("[" + timeStamp + "] " + message.trimmed());
}

void UpdateWidget::onUpdateFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    // 判断是检查更新完成还是实际更新完成
    if (!isUpdating) {
        // 检查更新完成
        if (exitStatus == QProcess::NormalExit && exitCode == 0) {
            // 解析检查更新的输出，判断是否有更新
            QString output = updateProcess->readAllStandardOutput();
            if (output.contains("update_available")) {
                updateProgress(100, "有可用更新");
                updateLog("发现新版本！您可以开始更新。");
                ui->startUpdateButton->setEnabled(true);
                ui->closeButton->setEnabled(true);
            } else {
                updateProgress(100, "已是最新版本");
                updateLog("您的软件已是最新版本，无需更新。");
                ui->closeButton->setEnabled(true);
                QMessageBox::information(this, "更新检查", "您的软件已是最新版本！");
            }
        } else {
            updateProgress(0, "检查更新失败");
            updateLog(QString("检查更新过程失败，错误码：%1").arg(exitCode));
            ui->closeButton->setEnabled(true);
            QMessageBox::critical(this, "更新检查失败", "无法获取最新更新信息！");
        }
    } else {
        // 实际更新完成
        isUpdating = false;

        if (exitStatus == QProcess::NormalExit && exitCode == 0) {
            updateProgress(100, "更新完成");
            updateLog("更新成功完成！");
            QMessageBox::information(this, "更新完成", "软件已成功更新到最新版本！");
        } else {
            updateProgress(0, "更新失败");
            updateLog(QString("更新过程失败，错误码：%1").arg(exitCode));
            QMessageBox::critical(this, "更新失败", "软件更新过程中发生错误！");
        }

        ui->startUpdateButton->setEnabled(false);
        ui->cancelButton->setEnabled(false);
        ui->closeButton->setEnabled(true);
    }
}
