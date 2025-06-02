#include "about.h"  // 确保包含头文件
#include "ui_about.h"  // 如果需要访问UI元素

AboutWidget::AboutWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutWidget)
{
    ui->setupUi(this);

    // 设置窗口标志，使其成为独立窗口
    setWindowFlags(Qt::Window);

    // 设置窗口标题
    setWindowTitle("关于");

    // 确保窗口关闭时自动释放内存
    setAttribute(Qt::WA_DeleteOnClose);

    QPixmap logo(":/image/image/favicon_about.ico");
    ui->logoLabel->setPixmap(logo.scaled(ui->logoLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    // 设置应用名称
    ui->titleLabel->setText("ExistOS连接套件");

    // 设置版本号（实际应用中可从配置文件或程序中获取）
    ui->versionLabel->setText("版本号: 0.0.0");

    // 设置描述信息
    ui->descriptionLabel->setText("描述");

    // 设置版权信息
    ui->copyrightLabel->setText("© 2025 组织名称. 保留所有权利.");
    
}

AboutWidget::~AboutWidget()
{
    delete ui;
}
