/********************************************************************************
** Form generated from reading UI file 'project.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROJECT_H
#define UI_PROJECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProjectClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ProjectClass)
    {
        if (ProjectClass->objectName().isEmpty())
            ProjectClass->setObjectName(QStringLiteral("ProjectClass"));
        ProjectClass->resize(600, 400);
        menuBar = new QMenuBar(ProjectClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        ProjectClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ProjectClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ProjectClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(ProjectClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        ProjectClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(ProjectClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ProjectClass->setStatusBar(statusBar);

        retranslateUi(ProjectClass);

        QMetaObject::connectSlotsByName(ProjectClass);
    } // setupUi

    void retranslateUi(QMainWindow *ProjectClass)
    {
        ProjectClass->setWindowTitle(QApplication::translate("ProjectClass", "Project", 0));
    } // retranslateUi

};

namespace Ui {
    class ProjectClass: public Ui_ProjectClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROJECT_H
