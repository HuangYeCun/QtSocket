#ifndef QTCLIENT_H
#define QTCLIENT_H

#include <QWidget>
#include <QString>
#include <QTcpSocket>
#include <QFile>
#include <QDateTime>

QT_BEGIN_NAMESPACE
namespace Ui {
class QtClient;
}
QT_END_NAMESPACE

class QtClient : public QWidget {
  Q_OBJECT

 public:
  QtClient(QWidget *parent = nullptr);
  ~QtClient();

  void InitMessageTCP();
  void InitFileTcp();
  // void newConnect();

 private:
  qint64 GetFilesize(const QString &filename);

 private slots:

  /********************消息传输**********************/
  ////连接服务器
  void ConnectServer();
  ////与服务器断开连接
  void DisconnectServer();
  ////接收服务器发送的数据
  void ReceiveMessage();
  ////向服务器发送数据
  void SendMessage();

  /********************文件传输**********************/
  void ConnectFileServer();
  void DisconnectFileServer();

  ////浏览文件
  void SelectFile();
  ////发送文件
  void SendFile();
  ////更新文件发送进度
  void UpdateFileProgress(qint64);
  ////更新文件接收进度
  void UpdateFileProgress();

 private:
  Ui::QtClient *ui;

  QTcpSocket *pMessageSocket_ = Q_NULLPTR;  //传输信息tcpSocket
  QTcpSocket *pFileSocket_ = Q_NULLPTR;     //传输文件tcpSocket

  ///文件传送
  QFile *pLocalFile_ = Q_NULLPTR;
  ///文件大小
  qint64 totalBytes_;     //文件总字节数
  qint64 bytesWritten_;   //已发送的字节数
  qint64 bytestoWrite_;   //尚未发送的字节数
  qint64 filenameSize_;   //文件名字的字节数
  qint64 bytesReceived_;  //接收的字节数
  ///每次发送数据大小
  qint64 perDataSize_;  ///文件传送相关变量初始化，每次发送数据大小为64kb
  QString filename_;
  ///数据缓冲区
  QByteArray inBlock_;
  QByteArray outBlock_;

  ////系统时间
  QDateTime current_datetime_;
  QString str_datetime_;

  //  QMap<QString, qint64> file_map_;
  qint64 filesize_;
};
#endif  // QTCLIENT_H
