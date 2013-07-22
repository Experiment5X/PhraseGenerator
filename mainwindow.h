#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>

using std::ifstream;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_generateBtn_clicked();

private:
    Ui::MainWindow *ui;
    std::string *countryNames;
    int countryCount;

    std::string getWord(const char firstLetter, const char *filePath);
    void generateWord();

};

#endif // MAINWINDOW_H
