#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <fstream>
#include "ChangeEndianess.h"
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

using namespace std;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QByteArray data = (QApplication::applicationDirPath() + "\\countries.apg").toLatin1();
    ifstream *reader = new ifstream(data.data(), ifstream::in);
    reader->seekg(0, ios::beg);
    reader->read((char*)&countryCount, 4);
    ChangeEndianess::ReverseArray(&countryCount, 1, 4);

    countryNames = new string[countryCount];

    for (int i = 0; i < countryCount; i++)
    {
        unsigned char strLen;
        reader->read((char*)&strLen, 1);
        char *countryName = new char[strLen + 1];
        countryName[strLen] = 0;
        reader->read(countryName, strLen);

        string name(countryName);
        countryNames[i] = name;
    }

    reader->close();
    delete reader;

    srand(time(NULL));

    generateWord();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_generateBtn_clicked()
{
    generateWord();
}

std::string MainWindow::getWord(const char firstLetter, const char *filePath)
{
    QByteArray data = (QApplication::applicationDirPath() + QString::fromAscii(filePath)).toLatin1();
    ifstream reader(data, ifstream::in);
    reader.seekg((firstLetter - 65) * 8, ios::beg);
    if (firstLetter > 'X')
        reader.seekg(-8, ios::cur);

    if (firstLetter == 'W')
        qDebug("HOLD THE PHONE");

    int wordCount;
    reader.read((char*)&wordCount, 4);
    ChangeEndianess::ReverseArray(&wordCount, 1, 4);

    int entryAddr;
    reader.read((char*)&entryAddr, 4);
    ChangeEndianess::ReverseArray(&entryAddr, 1, 4);

    char **words = new char*[wordCount];
    reader.seekg(entryAddr, ios::beg);

    for (int i = 0; i < wordCount; i++)
    {
        unsigned char wordLength;
        reader.read((char*)&wordLength, 1);
        char *word = new char[wordLength + 1];
        word[wordLength] = 0;
        reader.read(word, wordLength);
        words[i] = word;
    }

    int wordIndex = rand() % wordCount;

    for (int i = 0; i < wordCount; i++)
        if (i != wordIndex)
            delete[] words[i];

    string toReturn(words[wordIndex]);

    delete words;

    return toReturn;
}

void MainWindow::generateWord()
{
    int randCountryIndex = rand() % countryCount;

    string noun = getWord(toupper(countryNames[randCountryIndex][0]), "\\nouns.apg");
    string verb = getWord(toupper(countryNames[randCountryIndex][0]), "\\verbs.apg");

    QString noun_q = QString::fromStdString(noun);
    QString verb_q = QString::fromStdString(verb);
    QString country_q = QString::fromStdString(countryNames[randCountryIndex]);
    ui->phraseLbl->setText(country_q + " " + noun_q + " " + verb_q);
}























