#include "qtserver.h"
#include "ui_qtserver.h"

#include <QTcpSocket>
#include <QFileDialog>
#include <QJsonObject>
#include <QJsonDocument>

QtServer::QtServer(QWidget *parent) : QWidget(parent), ui(new Ui::QtServer) {
  ui->setupUi(this);

  message_socket = new QTcpSocket(this);
  message_server = new QTcpServer(this);
  ///开启监听
  message_server->listen(QHostAddress::Any, 6666);
  connect(message_server, SIGNAL(newConnection()), this,
          SLOT(AcceptConnection()));
  connect(ui->pushButton_send, SIGNAL(clicked()), this, SLOT(SendMessage()));

  ///文件传送套接字
  this->filesocket = new QTcpSocket(this);
  this->fileserver = new QTcpServer(this);
  this->fileserver->listen(QHostAddress::Any, 8888);
  connect(this->fileserver, SIGNAL(newConnection()), this,
          SLOT(AcceptFileConnection()));

  //// 文件传送相关变量初始化
  bytes_received_ = 0;
  total_bytes_ = 0;
  filename_size_ = 0;

  bytes_another = 0;

  connect(ui->pushButton_openFile, SIGNAL(clicked()), this, SLOT(SelectFile()));
  connect(ui->pushButton_sendFile, SIGNAL(clicked()), this, SLOT(SendFile()));
  // connect(ui->pushButton_sendFile, SIGNAL(clicked()), this,
  // SLOT(QueryFileInfo()));
}

QtServer::~QtServer() { delete ui; }

void QtServer::AcceptConnection() {
  ////返回一个socket连接
  message_socket = message_server->nextPendingConnection();
  connect(message_socket, SIGNAL(readyRead()), this, SLOT(ReceiveData()));
}

void QtServer::AcceptFileConnection() {
  bytes_written_ = 0;
  ///每次发送数据大小为64kb
  per_datasize_ = 64 * 1024;
  this->filesocket = this->fileserver->nextPendingConnection();
  ///接受文件
  connect(filesocket, SIGNAL(readyRead()), this, SLOT(UpdateFileProgress()));
  //  connect(filesocket, SIGNAL(error(QAbstractSocket::SocketError)), this,
  //          SLOT(UpdateFileProgress(qint64)));
  //  connect(filesocket, SIGNAL(bytesWritten(qint64)), this,
  //          SLOT(DisplayError(QAbstractSocket::SocketError socketError)));
}

void QtServer::SendMessage() {
  ////发送数据
  message_socket->write(ui->lineEdit_info->text().toLocal8Bit());
  ////显示
  current_date_time = QDateTime::currentDateTime();
  str_date_time = current_date_time.toString("yyyy-MM-dd hh:mm:ss");

  QString str = ui->lineEdit_info->text();
  str = "You " + str_date_time + "\n" + str;
  ui->textEdit_info->append(str);
}

void QtServer::ReceiveData() {
  /////获取当前时间
  current_date_time = QDateTime::currentDateTime();
  str_date_time = current_date_time.toString("yyyy-MM-dd hh:mm:ss") + "\n";

  ////接收数据
  QByteArray array = message_socket->readAll();  //从通信套接字中取出内容

  ////显示
  QString str = "Client " + str_date_time + QString::fromLocal8Bit(array);
  this->ui->textEdit_info->append(str);

  QString array_str(array);
  if (array_str.contains("Filesize")) {
    int index = array_str.indexOf("&");
    bytes_another = array_str.mid(index + 1).toInt();
  }
}

void QtServer::UpdateFileProgress() {
  QDataStream in_file(filesocket);
  in_file.setVersion(QDataStream::Qt_5_6);

  ///如果接收到的数据小于16个字节，保存到来的文件头结构
  if (bytes_received_ <= sizeof(qint64) * 2) {
    if ((filesocket->bytesAvailable() >= (sizeof(qint64)) * 2) &&
        (filename_size_ == 0)) {
      in_file >> total_bytes_ >> filename_size_;
      bytes_received_ += sizeof(qint64) * 2;
    }
    if ((filesocket->bytesAvailable() >= filename_size_) &&
        (filename_size_ != 0)) {
      in_file >> filename_;
      bytes_received_ += filename_size_;
      ////接收的文件放在指定目录下
      filename_ = "ClientData/" + filename_;
      localfile_ = new QFile(filename_);
      if (!localfile_->open(QFile::WriteOnly)) {
        qDebug() << "Server::open file error!";
        return;
      }
    } else {
      return;
    }
  }
  /////如果接收的数据小于总数据，则写入文件
  if (bytes_received_ < total_bytes_) {
    bytes_received_ += filesocket->bytesAvailable();
    inblock_ = filesocket->readAll();
    localfile_->write(inblock_);
    inblock_.resize(0);
  }
  ////更新进度条显示
  this->ui->progressBar_file->setMaximum(total_bytes_);
  this->ui->progressBar_file->setValue(bytes_received_);
  ////数据接收完成时
  if (bytes_received_ == total_bytes_) {
    this->ui->textEdit_info->append("Receive file successfully!");
    bytes_received_ = 0;
    total_bytes_ = 0;
    filename_size_ = 0;
    localfile_->close();
    // filesocket->close();
  }
}

void QtServer::DisplayError(QAbstractSocket::SocketError socketError) {
  qDebug() << message_socket->errorString();
  message_socket->close();
}

void QtServer::SelectFile() {
  filesocket->open(QIODevice::WriteOnly);
  ////文件传送进度更新
  connect(filesocket, SIGNAL(bytesWritten(qint64)), this,
          SLOT(UpdateFileProgress(qint64)));
  connect(filesocket, SIGNAL(readyRead()), this, SLOT(UpdateFileProgress()));

  connect(this, SIGNAL(ContinueWrite(qint64)), this,
          SLOT(UpdateFileProgress(qint64)));

  this->ui->progressBar_file->setValue(0);

  filename_ =
      QFileDialog::getOpenFileName(this, "Open a file", "/", "files (*)");
  ui->lineEdit_filepath->setText(filename_);

  QFileInfo file_info(filename_);
  QString file_name = file_info.fileName();
  QString tranfer_info = "fileinfo&" + file_name;

  QJsonObject json;
  json.insert("filename", file_name);
  //  json.insert("filesize", 0);
  message_socket->write(
      QString(QJsonDocument(json).toJson()).toStdString().c_str());
  //  message_socket->write(tranfer_info.toStdString().c_str());
}

void QtServer::QueryFileInfo() { message_socket->write("fileinfo"); }

void QtServer::SendFile() {
  localfile_ = new QFile(filename_);
  if (!localfile_->open(QFile::ReadOnly)) {
    return;
  }
  ///获取文件大小
  total_bytes_ = localfile_->size();
  QDataStream sendout(&outblock_, QIODevice::WriteOnly);
  // sendout.setVersion(QDataStream::Qt_4_8);
  sendout.setVersion(QDataStream::Qt_5_6);
  QString currentFileName =
      filename_.right(filename_.size() - filename_.lastIndexOf('/') - 1);

  ////保留总代大小信息空间、文件名大小信息空间、文件名
  sendout << qint64(0) << qint64(0) << currentFileName;
  //  total_bytes_ += outblock_.size();
  sendout.device()->seek(0);
  sendout << total_bytes_ << qint64((outblock_.size() - sizeof(qint64) * 2));

  bytes_to_write_ = total_bytes_ - filesocket->write(outblock_);
  outblock_.resize(0);
}

void QtServer::UpdateFileProgress(qint64 numBytes) {
  ////已经发送的数据大小
  bytes_written_ += (int)numBytes;

  //判断bytes_written_是否到达接收端已经接收的
  if (bytes_written_ <= bytes_another) {  //已经发送过
    ////更新进度条
    ui->progressBar_file->setMaximum(total_bytes_);
    ui->progressBar_file->setValue(bytes_another);

    outblock_ = localfile_->read(qMin(bytes_to_write_, per_datasize_));

    bytes_to_write_ -= qMin(bytes_to_write_, per_datasize_);
    outblock_.resize(0);

    UpdateFileProgress(qMin(bytes_to_write_, per_datasize_));
    // emit ContinueWrite(qMin(bytes_to_write_, per_datasize_));
    return;
  }

  ////如果已经发送了数据
  if (bytes_to_write_ > 0) {
    outblock_ = localfile_->read(qMin(bytes_to_write_, per_datasize_));
    ///发送完一次数据后还剩余数据的大小
    bytes_to_write_ -= ((int)filesocket->write(outblock_));
    ///清空发送缓冲区
    outblock_.resize(0);
  } else
    localfile_->close();

  ////更新进度条
  this->ui->progressBar_file->setMaximum(total_bytes_);
  this->ui->progressBar_file->setValue(bytes_written_);
  ////如果发送完毕
  if (bytes_written_ == total_bytes_) {
    localfile_->close();
    // filesocket->close();
  }
}
