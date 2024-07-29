#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QFileInfo>
#include <QDebug>

class FileOrganizer : public QMainWindow {
    Q_OBJECT
    
public:
    FileOrganizer(QWidget *parent = nullptr) : QMainWindow(parent) {
        setWindowTitle("文件整理工具");
        
        // 创建选择文件夹按钮
        selectButton = new QPushButton("选择文件夹", this);
        selectButton->setGeometry(50, 50, 200, 30);
        connect(selectButton, &QPushButton::clicked, this, &FileOrganizer::selectDirectory);
        
        // 创建整理文件按钮
        organizeButton = new QPushButton("整理文件", this);
        organizeButton->setGeometry(50, 100, 200, 30);
        connect(organizeButton, &QPushButton::clicked, this, &FileOrganizer::organizeFiles);
        
        // 创建退出按钮
        exitButton = new QPushButton("退出", this);
        exitButton->setGeometry(50, 150, 200, 30);
        connect(exitButton, &QPushButton::clicked, this, &QApplication::quit);
    }
    
private slots:
    void selectDirectory() {
        QString folderPath = QFileDialog::getExistingDirectory(this, tr("选择文件夹"), QDir::homePath());
        if (!folderPath.isEmpty()) {
            selectedFolder = folderPath;
            qDebug() << "Selected directory: " << selectedFolder;
        }
    }
    
    void organizeFiles() {
        if (selectedFolder.isEmpty()) {
            QMessageBox::warning(this, "警告", "请先选择文件夹！");
            return;
        }
        
        QDir sourceDir(selectedFolder);
        QStringList files = sourceDir.entryList(QDir::Files);
        
        foreach (QString filename, files) {
            QString filePath = sourceDir.filePath(filename);
            QFileInfo fileInfo(filePath);
            QString folderName = fileInfo.baseName(); // 文件名作为文件夹名
            
            QString folderPath = sourceDir.filePath(folderName);
            if (!QDir(folderPath).exists()) {
                QDir().mkdir(folderPath);
            }
            
            if (QFile::exists(folderPath + "/" + filename)) {
                qDebug() << "File already exists: " << filename;
                continue;
            }
            
            if (!QFile::rename(filePath, folderPath + "/" + filename)) {
                qDebug() << "Failed to move file: " << filename;
            } else {
                qDebug() << "Moved " << filename << " to " << folderName;
            }
        }
        
        QMessageBox::information(this, "完成", "文件整理完成！");
    }
    
private:
    QPushButton *selectButton;
    QPushButton *organizeButton;
    QPushButton *exitButton;
    QString selectedFolder;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    FileOrganizer organizer;
    organizer.resize(300, 250);
    organizer.show();
    return app.exec();
}

#include "main.moc"
