#include "MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->run_button_, SIGNAL(clicked()), this, SLOT(loadRegExp()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadRegExp()
{
    const QString regex_pattern = ui->regex_line_edit_->text();
    const QString check_text = ui->check_text_line_edit_->text();

    ui->result_text_browser_->clear();

    if(regex_pattern.isEmpty())
    {
        QStringList message_list("Failed");
        message_list << QString("RegExp field is empty.\nNothing to do.");
        ui->result_text_browser_->setText(message_list.join("\n"));
    }
    else if(check_text.isEmpty())
    {
        QStringList message_list("Failed");
        message_list << QString("CheckText field is empty.\nNothing to do.");
        ui->result_text_browser_->setText(message_list.join("\n"));
    }
    else
    {
        const QRegExp regex(regex_pattern);

        int pos = regex.indexIn(check_text);

        if(pos == -1)
        {
            QStringList message_list("Failed");
            message_list << QString("RegExp does not match CheckText.");
            ui->result_text_browser_->setText(message_list.join("\n"));
        }
        else
        {
            QStringList captures = regex.capturedTexts().mid(1);
            pos += regex.capturedTexts().value(0).count();
            while((pos = regex.indexIn(check_text, pos)) != -1)
            {
                captures << regex.capturedTexts().mid(1);
                pos += regex.capturedTexts().value(0).count();
            }


            QStringList message_list("Success");
            message_list << "RegExp matches Check Text";
            const int capture_count = captures.count();
            if(capture_count == 0)
            {
                message_list << QString("There are no captures.");
            }
            else
            {
                if(capture_count == 1)
                {
                    message_list << QString("There is 1 capture.");
                }
                else
                {
                    message_list << QString("There are %1 captures").arg(capture_count);
                }
                message_list << "\"" + captures.join("\"\n\"") + "\"";
            }

            ui->result_text_browser_->setText(message_list.join("\n"));
        }
    }
}
