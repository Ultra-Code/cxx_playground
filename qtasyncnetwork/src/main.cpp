#include <QCoreApplication>
#include <QDebug>
#include <QString>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtWidgets/QMainWindow>
#include <memory>

class MainWindow : QMainWindow
{
};

auto printHTML(const QString& html) -> void
{
    qDebug() << html << "\n";
    qDebug() << "Done\n";
}
auto main(int argc, char** argv) -> int
{
    const QCoreApplication a(argc, argv);
    qDebug() << "Start\n";
    auto manager{ QNetworkAccessManager{} };
    const auto request{ QNetworkRequest(QUrl("http://www.google.com")) };
    auto* reply{ manager.get(request) };

    const auto html{ std::make_unique<QString>() };
    QObject::connect(reply, &QNetworkReply::readyRead,
                     [reply, &html]() { html->append(QString(reply->readAll())); });
    QObject::connect(reply, &QNetworkReply::downloadProgress,
                     [reply](qint64 byte_recieved, qint64 byte_total) {
                         qDebug() << "Progress: " << byte_recieved << "bytes /"
                                  << byte_total << "bytes";
                     });
    QObject::connect(reply, &QNetworkReply::finished,
                     [&]() { printHTML(html->toHtmlEscaped()); });
    a.exec();
}

