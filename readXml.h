#ifndef READ_XML_H
#define READ_XML_H

#include "head.h"

struct Path
{
	QString _fill;
	QString _stroke;
	QString _w;
	QString _h;
	QVector<QVector<QString>> _differentPath;
};

struct Range
{
	QHash<QString, QPair<QString, QString>> _range;
	QPair<QString, QString> _pos;
};

class ReadXml
{
public:
	ReadXml(const QString& filePath, const QString& shapeName);
	QVector<QPair<QString, double>> getAvLst() const;
	QVector<QPair<QString, QString>> getGdLst() const;
	Range getAhLst() const;
	QVector<Path> getPathLst() const;
private:
	bool readXmlFile();

private:
	QVector<QPair<QString, double>> _avLst;
	QVector<QPair<QString,QString>> _gdLst;
	Range _ahLst;
	QVector<Path> _pathLst;
	QString _filePath; //文件位置
	QString _shapeName; // 图形名字
};

#endif 