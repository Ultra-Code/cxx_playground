#include "main.moc"
#include <QKeyEvent>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QtWidgets>
#include <memory>

class ui_mainwindow
{
    std::unique_ptr<QWidget> centralWidget{};
    std::unique_ptr<QLineEdit> lineEdit{};

   public:
    auto setupUI(QMainWindow* mainwindow) -> void
    {
        if (mainwindow->objectName().isEmpty())
        {
            mainwindow->setObjectName(QString::fromUtf8("My MainWindow"));
            constexpr std::uint16_t height{ 400 };
            constexpr std::uint16_t width{ 400 };
            mainwindow->resize(width, height);
        }
        centralWidget = std::make_unique<QWidget>(mainwindow);
        centralWidget->setObjectName(QString::fromUtf8("My Central Widget"));
        lineEdit = std::make_unique<QLineEdit>(centralWidget.get());
        lineEdit->setObjectName(QString::fromUtf8("My LineEdit"));
        constexpr std::uint16_t left{ 40 }, top{ 80 }, width{ 180 }, height{ 30 };
        lineEdit->setGeometry(QRect(left, top, width, height));
    }
};
namespace Ui
{
    class MainWindow : public ui_mainwindow
    {
    };
} // namespace Ui

class MainWindow : public QMainWindow
{
    Q_OBJECT

    std::unique_ptr<Ui::MainWindow> ui{};


   public:
    explicit MainWindow(QWidget* parent = nullptr)
        : QMainWindow{ parent }
        , ui{ std::make_unique<Ui::MainWindow>() }
    {
        ui->setupUI(this);
    }
    virtual ~MainWindow() override{};
};

auto main(int argc, char** argv) -> int
{
    const auto app{ QApplication(argc, argv) };
    auto window{ MainWindow() };
    window.show();
    return app.exec();
}
