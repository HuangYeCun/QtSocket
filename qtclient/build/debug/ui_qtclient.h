/********************************************************************************
** Form generated from reading UI file 'qtclient.ui'
**
** Created by: Qt User Interface Compiler version 5.14.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTCLIENT_H
#define UI_QTCLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtClient
{
public:
    QTextEdit *textEdit_info;
    QGroupBox *groupBox;
    QLabel *label_filename;
    QPushButton *pushButton_openFile;
    QPushButton *pushButton_sendFile;
    QProgressBar *progressBar_file;
    QLineEdit *lineEdit_filepath;
    QLabel *label_filename_2;
    QPushButton *pushButton_conn_file;
    QPushButton *pushButton_disconn_file;
    QGroupBox *groupBox_2;
    QPushButton *pushButton_conn;
    QPushButton *pushButton_disconn;
    QPushButton *pushButton_send;
    QLineEdit *lineEdit_info;
    QGroupBox *groupBox_3;
    QLabel *label_server;
    QLineEdit *lineEdit_ip;

    void setupUi(QWidget *QtClient)
    {
        if (QtClient->objectName().isEmpty())
            QtClient->setObjectName(QString::fromUtf8("QtClient"));
        QtClient->resize(877, 534);
        textEdit_info = new QTextEdit(QtClient);
        textEdit_info->setObjectName(QString::fromUtf8("textEdit_info"));
        textEdit_info->setGeometry(QRect(20, 100, 461, 291));
        groupBox = new QGroupBox(QtClient);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(510, 120, 361, 221));
        label_filename = new QLabel(groupBox);
        label_filename->setObjectName(QString::fromUtf8("label_filename"));
        label_filename->setGeometry(QRect(10, 70, 81, 21));
        pushButton_openFile = new QPushButton(groupBox);
        pushButton_openFile->setObjectName(QString::fromUtf8("pushButton_openFile"));
        pushButton_openFile->setGeometry(QRect(110, 120, 71, 31));
        pushButton_sendFile = new QPushButton(groupBox);
        pushButton_sendFile->setObjectName(QString::fromUtf8("pushButton_sendFile"));
        pushButton_sendFile->setGeometry(QRect(200, 120, 71, 31));
        progressBar_file = new QProgressBar(groupBox);
        progressBar_file->setObjectName(QString::fromUtf8("progressBar_file"));
        progressBar_file->setGeometry(QRect(90, 170, 261, 23));
        progressBar_file->setValue(0);
        lineEdit_filepath = new QLineEdit(groupBox);
        lineEdit_filepath->setObjectName(QString::fromUtf8("lineEdit_filepath"));
        lineEdit_filepath->setGeometry(QRect(90, 70, 261, 31));
        label_filename_2 = new QLabel(groupBox);
        label_filename_2->setObjectName(QString::fromUtf8("label_filename_2"));
        label_filename_2->setGeometry(QRect(10, 170, 71, 21));
        pushButton_conn_file = new QPushButton(groupBox);
        pushButton_conn_file->setObjectName(QString::fromUtf8("pushButton_conn_file"));
        pushButton_conn_file->setGeometry(QRect(60, 20, 101, 31));
        pushButton_disconn_file = new QPushButton(groupBox);
        pushButton_disconn_file->setObjectName(QString::fromUtf8("pushButton_disconn_file"));
        pushButton_disconn_file->setGeometry(QRect(170, 20, 91, 31));
        groupBox_2 = new QGroupBox(QtClient);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(20, 400, 471, 131));
        pushButton_conn = new QPushButton(groupBox_2);
        pushButton_conn->setObjectName(QString::fromUtf8("pushButton_conn"));
        pushButton_conn->setGeometry(QRect(40, 30, 91, 31));
        pushButton_disconn = new QPushButton(groupBox_2);
        pushButton_disconn->setObjectName(QString::fromUtf8("pushButton_disconn"));
        pushButton_disconn->setGeometry(QRect(150, 30, 91, 31));
        pushButton_send = new QPushButton(groupBox_2);
        pushButton_send->setObjectName(QString::fromUtf8("pushButton_send"));
        pushButton_send->setGeometry(QRect(380, 70, 75, 31));
        lineEdit_info = new QLineEdit(groupBox_2);
        lineEdit_info->setObjectName(QString::fromUtf8("lineEdit_info"));
        lineEdit_info->setGeometry(QRect(20, 70, 341, 31));
        groupBox_3 = new QGroupBox(QtClient);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(30, 20, 441, 71));
        label_server = new QLabel(groupBox_3);
        label_server->setObjectName(QString::fromUtf8("label_server"));
        label_server->setGeometry(QRect(10, 30, 91, 31));
        lineEdit_ip = new QLineEdit(groupBox_3);
        lineEdit_ip->setObjectName(QString::fromUtf8("lineEdit_ip"));
        lineEdit_ip->setGeometry(QRect(110, 30, 171, 31));

        retranslateUi(QtClient);

        QMetaObject::connectSlotsByName(QtClient);
    } // setupUi

    void retranslateUi(QWidget *QtClient)
    {
        QtClient->setWindowTitle(QCoreApplication::translate("QtClient", "QtClient", nullptr));
        groupBox->setTitle(QCoreApplication::translate("QtClient", "\346\226\207\344\273\266TCP", nullptr));
        label_filename->setText(QCoreApplication::translate("QtClient", "\346\226\207\344\273\266\350\267\257\345\276\204\357\274\232", nullptr));
        pushButton_openFile->setText(QCoreApplication::translate("QtClient", "\351\200\211\346\213\251\346\226\207\344\273\266", nullptr));
        pushButton_sendFile->setText(QCoreApplication::translate("QtClient", "\345\217\221\351\200\201\346\226\207\344\273\266", nullptr));
        label_filename_2->setText(QCoreApplication::translate("QtClient", "\344\274\240\350\276\223\350\277\233\345\272\246\357\274\232", nullptr));
        pushButton_conn_file->setText(QCoreApplication::translate("QtClient", "\350\277\236\346\216\245\346\234\215\345\212\241\345\231\250", nullptr));
        pushButton_disconn_file->setText(QCoreApplication::translate("QtClient", "\346\226\255\345\274\200\346\234\215\345\212\241\345\231\250", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("QtClient", "\346\266\210\346\201\257TCP", nullptr));
        pushButton_conn->setText(QCoreApplication::translate("QtClient", "\350\277\236\346\216\245\346\234\215\345\212\241\345\231\250", nullptr));
        pushButton_disconn->setText(QCoreApplication::translate("QtClient", "\346\226\255\345\274\200\346\234\215\345\212\241\345\231\250", nullptr));
        pushButton_send->setText(QCoreApplication::translate("QtClient", "\345\217\221\351\200\201", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("QtClient", "\346\234\215\345\212\241\345\231\250\344\277\241\346\201\257", nullptr));
        label_server->setText(QCoreApplication::translate("QtClient", "\346\234\215\345\212\241\345\231\250\345\234\260\345\235\200\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtClient: public Ui_QtClient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTCLIENT_H
