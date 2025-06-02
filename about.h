#ifndef ABOUT_H
#define ABOUT_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class AboutWidget; }
QT_END_NAMESPACE

class AboutWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AboutWidget(QWidget *parent = nullptr);
    ~AboutWidget();

private:
    Ui::AboutWidget *ui;
};

#endif // ABOUT_H
