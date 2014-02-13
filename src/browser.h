#ifndef BROWSER_H
#define BROWSER_H

#include <QMainWindow>
#include <QWebView>
#include <QWebFrame>
#include <QDir>

namespace Ui {
class Browser;
}

class NetworkInterface;

class Browser : public QMainWindow
{
    Q_OBJECT

public:
    explicit Browser(QWidget *parent = 0);
    ~Browser();

    QVariant execute(const QString& code);
    void loadurl(const QUrl &url);

private slots:
    void urlChanged(const QUrl &url);

private:
    Ui::Browser *ui;
    QWebView *view;
    NetworkInterface *n;
};

#endif // BROWSER_H

