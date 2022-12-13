#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QBoxLayout>
#include <QGroupBox>
#include <QMainWindow>
#include "plot.h"
#include "Sliders/abstractslider.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QBoxLayout* lay = nullptr;
    Plot* plot = nullptr;
    AbstractSlider* deltaSlider = nullptr;
    QBoxLayout* sliderLay = nullptr;
    QGroupBox* sliderGroupBox;
    Ui::MainWindow *ui;
    void createGroupBox(QGroupBox *groupBox, QBoxLayout *lay, QString groupName, QBoxLayout* parentGroupBoxLay, const int stretch);

};
#endif // MAINWINDOW_H
