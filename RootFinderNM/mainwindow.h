/***************************************************************************
 *                                                                         *
 *   Copyright (C) 17.09.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include <QSlider>
#include <QLCDNumber>
#include <QLabel>
#include <QToolBar>
#include <QIcon>
#include <QAction>
#include <QMessageBox>
#include "Widgets/solverwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QToolBar* toolBar = nullptr;
    QVBoxLayout* mainLayout = nullptr;
    SolverWidget* solverWidget;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showDeveloperInfo();

private:
    Ui::MainWindow *ui;
    void createToolBar();
};
#endif // MAINWINDOW_H
