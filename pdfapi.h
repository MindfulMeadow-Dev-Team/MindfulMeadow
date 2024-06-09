#ifndef PDFAPI_H
#define PDFAPI_H

#include <QObject>
#include <QMutex>
#include <QStringList>
#include <QPrinter>
#include <QPageSize>
#include <QTextDocument>
#include <QTextBlock>
class PdfAPI : public QObject
{
    Q_OBJECT
private:
    explicit PdfAPI(QObject *parent = 0);
    static PdfAPI *_instance;
    QStringList html;

public:
    static PdfAPI *Instance() {
        static QMutex mutex;
        if (!_instance) {
            QMutexLocker locker(&mutex);
            if (!_instance) {
                _instance = new PdfAPI;
            }
        }
        return _instance;
    }
    /**
     * @brief SavePdf 将数据保存成PDF表格
     * @param fileName 文件名
     * @param title 表格标题
     * @param subTitle 表格副标题
     * @param columnNames 列名
     * @param columnWidths 列宽
     * @param content 数据内容
     * @param landscape 纸张是否横向
     * @param check  是否给某列加特殊样式
     * @param pageSize 纸张类型
     */
    void SavePdf(QString fileName, QString title, QString subTitle,
                 QList<QString> columnNames, QList<int> columnWidths,
                 QStringList content, bool landscape, bool check,
                 QPageSize pageSize = QPageSize(QPageSize::A3));

    void SavePdf(QString fileName, QString title,
                 QList<QString> columnNames, QList<int> columnWidths,
                 QStringList subTitle1, QStringList subTitle2,
                 QStringList content, bool landscape, bool check,
                 QPageSize pageSize = QPageSize(QPageSize::A3));

};

#endif // PDFAPI_H

