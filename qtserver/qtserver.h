#ifndef QTSERVER_H
#define QTSERVER_H

#include <QWidget>

#include <QString>
#include <QFile>
#include <QTcpServer>
#include <QDateTime>

QT_BEGIN_NAMESPACE
namespace Ui {
class QtServer;
}
QT_END_NAMESPACE

class QtServer : public QWidget {
  Q_OBJECT

 public:
  QtServer(QWidget *parent = nullptr);
  ~QtServer();

signals:
  void ContinueWrite(qint64 num);

 private slots:
  void SendMessage();
  void AcceptConnection();
  ////接收客户端发送的数据
  void ReceiveData();

  void AcceptFileConnection();
  void UpdateFileProgress();
  void DisplayError(QAbstractSocket::SocketError socketError);

  ///选择发送的文件
  void SelectFile();
  void QueryFileInfo();
  void SendFile();
  ////更新文件传送进度
  void UpdateFileProgress(qint64);

 private:
  Ui::QtServer *ui;

  QTcpServer *message_server;
  QTcpSocket *message_socket;
  QTcpServer *fileserver;
  QTcpSocket *filesocket;

  //////传送文件相关变量
  qint64 total_bytes_;     //文件总字节数
  qint64 bytes_received_;  //接收的字节数
  qint64 bytes_to_write_;  //尚未发送的字节数
  qint64 bytes_written_;   //已发送的字节数
  qint64 filename_size_;
  QString filename_;
  ///每次发送数据大小
  qint64 per_datasize_;
  QFile *localfile_;
  ////本地缓冲区
  QByteArray inblock_;
  QByteArray outblock_;

  ////系统时间
  QDateTime current_date_time;
  QString str_date_time;

  qint64 bytes_another;  //接收端已经接收的字节数
};
#endif  // QTSERVER_H
