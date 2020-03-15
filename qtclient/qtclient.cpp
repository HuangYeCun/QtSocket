#include "qtclient.h"
#include "ui_qtclient.h"

#include <QFileDialog>
#include <QJsonParseError>
#include <QJsonObject>
#include <QFile>

QtClient::QtClient(QWidget* parent)
    : QWidget(parent),
      ui(new Ui::QtClient),
      totalBytes_(0),
      bytesWritten_(0),
      bytestoWrite_(0),
      filenameSize_(0),
      bytesReceived_(0),
      perDataSize_(64 * 1024),
      filesize_(0) {
  ui->setupUi(this);

  InitMessageTCP();
  InitFileTcp();

  ui->lineEdit_ip->setText("127.0.0.1");
  // ui->lineEdit_port->setText("6666");

  connect(ui->pushButton_openFile, SIGNAL(clicked()), this, SLOT(SelectFile()));
  connect(ui->pushButton_sendFile, SIGNAL(clicked()), this, SLOT(SendFile()));
}

QtClient::~QtClient() {
  if (pMessageSocket_) {
    delete pMessageSocket_;
    pMessageSocket_ = Q_NULLPTR;
  }

  delete ui;
}

void QtClient::InitMessageTCP() {
  pMessageSocket_ = new QTcpSocket(this);
  connect(ui->pushButton_conn, SIGNAL(clicked()), this, SLOT(ConnectServer()));
  connect(ui->pushButton_disconn, SIGNAL(clicked()), this,
          SLOT(DisconnectServer()));
  connect(ui->pushButton_send, SIGNAL(clicked()), this, SLOT(SendMessage()));
}

void QtClient::ConnectServer() {
  pMessageSocket_->abort();
  pMessageSocket_->connectToHost(ui->lineEdit_ip->text(), 6666);
  if (pMessageSocket_->waitForConnected()) {
    qDebug("Message Server Connected!");
    ui->textEdit_info->append("Message Server Connected!");
  }
  connect(pMessageSocket_, SIGNAL(readyRead()), this, SLOT(ReceiveMessage()));
}

void QtClient::DisconnectServer() {
  pMessageSocket_->disconnectFromHost();
  if (pMessageSocket_->state() == QAbstractSocket::UnconnectedState ||
      pMessageSocket_->waitForDisconnected()) {
    qDebug("Message Server Disconnected!");
    ui->textEdit_info->append("Message Server Disconnected!");
  }
}

void QtClient::ReceiveMessage() {
  /////获取当前时间
  current_datetime_ = QDateTime::currentDateTime();
  str_datetime_ = current_datetime_.toString("yyyy-MM-dd hh:mm:ss") + "\n";
  ////接收数据
  QByteArray array = pMessageSocket_->readAll();
  ////显示
  QString str = "Server " + str_datetime_ + QString::fromLocal8Bit(array);
  this->ui->textEdit_info->append(str);

  //传输的消息为Json包含fileName
  QJsonParseError parseJsonErr;
  QJsonDocument document = QJsonDocument::fromJson(
      QString::fromLocal8Bit(array).toUtf8(), &parseJsonErr);
  if (!(parseJsonErr.error == QJsonParseError::NoError)) {
    qDebug() << tr("解析json文件错误！");
    return;
  }
  QJsonObject jsonObject = document.object();
  QString filename = jsonObject["filename"].toString();
  this->ui->textEdit_info->append("filename: " + filename);
  qDebug() << "jsonObject[Name]==" << jsonObject["filename"].toString();

  QString filepath = "ServerData/";
  filepath += filename;
  filesize_ = GetFilesize(filepath);
  QString send_data = "Filesize&" + QString::number(filesize_);

  pMessageSocket_->write(send_data.toStdString().c_str());

  //  QString array_str(array);
  //  if (array_str.contains("fileinfo")) {
  //    int index = array_str.indexOf("&");
  //    QString filename = "ServerData/";
  //    filename += array_str.mid(index + 1);
  //    qint64 filesize = GetFilesize(filename);
  //    QString send_data = "Filesize&" + QString::number(filesize);

  //    pMessageSocket_->write(send_data.toStdString().c_str());
  //  }
}

void QtClient::SendMessage() {
  ////发送数据
  pMessageSocket_->write(ui->lineEdit_info->text().toLocal8Bit());
  ////显示
  current_datetime_ = QDateTime::currentDateTime();
  str_datetime_ = current_datetime_.toString("yyyy-MM-dd hh:mm:ss");

  QString str = ui->lineEdit_info->text();
  str = "You " + str_datetime_ + "\n" + str;
  ui->textEdit_info->append(str);
}

void QtClient::InitFileTcp() {
  pFileSocket_ = new QTcpSocket(this);

  connect(ui->pushButton_conn_file, SIGNAL(clicked()), this,
          SLOT(ConnectFileServer()));
  connect(ui->pushButton_disconn_file, SIGNAL(clicked()), this,
          SLOT(DisconnectFileServer()));
}

void QtClient::ConnectFileServer() {
  pFileSocket_->abort();
  pFileSocket_->connectToHost(ui->lineEdit_ip->text(), 8888);
  if (pFileSocket_->waitForConnected()) {
    qDebug("File Server Connected!");
    ui->textEdit_info->append("File Server Connected!");
  }
  ////文件传送进度更新
  connect(pFileSocket_, SIGNAL(bytesWritten(qint64)), this,
          SLOT(UpdateFileProgress(qint64)));
  connect(pFileSocket_, SIGNAL(readyRead()), this, SLOT(UpdateFileProgress()));
}

void QtClient::DisconnectFileServer() {
  pFileSocket_->disconnectFromHost();
  if (pFileSocket_->state() == QAbstractSocket::UnconnectedState ||
      pFileSocket_->waitForDisconnected()) {
    qDebug("File Server Disconnected!");
    ui->textEdit_info->append("File Server Disconnected!");

    ui->textEdit_info->append("bytesReceived : " +
                              QString::number(bytesReceived_));
    ui->textEdit_info->append("totalBytes : " + QString::number(totalBytes_));
    ui->textEdit_info->append("filenameSize : " +
                              QString::number(filenameSize_));

    bytesReceived_ = 0;
    totalBytes_ = 0;
    filenameSize_ = 0;
    pLocalFile_->close();
  }
}

void QtClient::SelectFile() {
  ui->progressBar_file->setValue(0);
  filename_ =
      QFileDialog::getOpenFileName(this, "Open a file", "/", "files (*)");
  ui->lineEdit_filepath->setText(filename_);

  // qint64 file_size = GetFileSize(filename_);
}

void QtClient::SendFile() {
  pLocalFile_ = new QFile(filename_);
  if (!pLocalFile_->open(QFile::ReadOnly)) {
    ui->textEdit_info->append(tr("Client:open file error!"));
    return;
  }
  ///获取文件大小
  totalBytes_ = pLocalFile_->size();
  QDataStream sendout(&outBlock_, QIODevice::WriteOnly);
  sendout.setVersion(QDataStream::Qt_5_6);
  QString currentFileName =
      filename_.right(filename_.size() - filename_.lastIndexOf('/') - 1);

  qDebug() << sizeof(currentFileName);
  ////保留总代大小信息空间、文件名大小信息空间、文件名
  sendout << qint64(0) << qint64(0) << currentFileName;
  totalBytes_ += outBlock_.size();

  sendout.device()->seek(0);
  sendout << totalBytes_ << qint64((outBlock_.size() - sizeof(qint64) * 2));

  bytestoWrite_ = totalBytes_ - pFileSocket_->write(outBlock_);
  outBlock_.resize(0);
}

void QtClient::UpdateFileProgress(qint64 numBytes) {
  ////已经发送的数据大小
  bytesWritten_ += (int)numBytes;

  ////如果已经发送了数据
  if (bytestoWrite_ > 0) {
    outBlock_ = pLocalFile_->read(qMin(bytestoWrite_, perDataSize_));
    ///发送完一次数据后还剩余数据的大小
    bytestoWrite_ -= ((int)pFileSocket_->write(outBlock_));
    ///清空发送缓冲区
    outBlock_.resize(0);
  } else
    pLocalFile_->close();

  ////更新进度条
  ui->progressBar_file->setMaximum(totalBytes_);
  ui->progressBar_file->setValue(bytestoWrite_);

  ////如果发送完毕
  if (bytestoWrite_ == totalBytes_) {
    pLocalFile_->close();
    // fileSocket->close();
  }
}

void QtClient::UpdateFileProgress() {
  //两种情况：（1）初次接收；（2）断点续传

  QDataStream inFile(pFileSocket_);
  inFile.setVersion(QDataStream::Qt_5_6);

  ///如果接收到的数据小于16个字节，保存到来的文件头结构
  if (bytesReceived_ <= sizeof(qint64) * 2) {
    if ((pFileSocket_->bytesAvailable() >= (sizeof(qint64)) * 2) &&
        (filenameSize_ == 0)) {
      inFile >> totalBytes_ >> filenameSize_;

      bytesReceived_ += sizeof(qint64) * 2;
      //      qDebug() << "filenameSize_ is 0";
    }
    if ((pFileSocket_->bytesAvailable() >= filenameSize_) &&
        (filenameSize_ != 0)) {
      //      qDebug() << "filenameSize_ is not 0";

      inFile >> filename_;

      if (0 == filesize_) {
        bytesReceived_ += filenameSize_;
        filename_ = "ServerData/" + filename_;

        pLocalFile_ = new QFile(filename_);
        if (!pLocalFile_->open(QIODevice::WriteOnly)) {
          qDebug() << "Server::open file error!";
          return;
        }
      } else {
        bytesReceived_ += filenameSize_;
        bytesReceived_ += filesize_;
        filename_ = "ServerData/" + filename_;

        pLocalFile_ = new QFile(filename_);
        if (!pLocalFile_->open(QIODevice::Append)) {
          qDebug() << "Server::open file error!";
          return;
        }
      }

    } else
      return;
  }
  /////如果接收的数据小于总数据，则写入文件
  if (bytesReceived_ < totalBytes_) {
    bytesReceived_ += pFileSocket_->bytesAvailable();
    inBlock_ = pFileSocket_->readAll();
    pLocalFile_->write(inBlock_);
    inBlock_.resize(0);
  }

  ////更新进度条显示
  ui->progressBar_file->setMaximum(totalBytes_);
  ui->progressBar_file->setValue(bytesReceived_);

  ////数据接收完成时
  if (bytesReceived_ == totalBytes_) {
    ui->textEdit_info->append("Receive file successfully!");
    bytesReceived_ = 0;
    totalBytes_ = 0;
    filenameSize_ = 0;
    pLocalFile_->close();
    // fileSocket->close();
  }
}

qint64 QtClient::GetFilesize(const QString& filename) {
  QFile* localfile = new QFile(filename);

  qint64 filesize = localfile->size();
  delete localfile;
  return filesize;
  //  QFileInfo info(filename);
  //  if (!info.exists()) {
  //    qDebug() << filename << " Not exists";
  //    return 0;
  //  }

  //  return info.size();
}
