#ifndef PARSE_XML_H
#define PARSE_XML_H

#include "head.h"
#include "readXml.h"
#include "complexPath.h"

class Fmla
{
public:
	Fmla();
	Fmla(const QString& fm1a);
	int getFmlaOPeration() const ;
	QVector<QString> getFmlaArgs() const;
private:
	static QHash<QString, int> _opMap;
private:
	int _operation;
	QVector<QString> _args;
};

class NameFmlas
{
	enum {
		MulDiv = 1, AddSub, AddDiv, IfElse, Abs, At2, Cat2,
		Cos, Max, Min, Mod, Pin, Sat2, Sin, Sqrt, Tan, Val,
	};
public:
	NameFmlas();
	void setGdLst(QVector<QPair<QString, QString>> gdLst);
	void setAvLst(QVector<QPair<QString, double>> avLst);
	void setAvLst(const QString& adj, double val);
	void setAhLst(Range range);
	Range getAhLst();
	QVector<QPair<QString, double>> getAvLst() const; 

	double getValue(const QString& s);
	void parseAllNameFmla();
private:
	void initSimpleTypeMap();//初始化_simpleTypeMap
	void initNameMap(); //初始化_nameMap
	double calculateFormula(const Fmla& fmla);//计算formula
private:
	QVector<QPair<QString, Fmla>> _gdLst;
	QVector<QPair<QString, double>> _avLst; //保存图形变化的参数
	Range _ahLst;//参数变化的范围

	QMap<QString, QString> _simpleTypeMap; //保存预先定义的常量
	QMap<QString, double> _nameMap; //保存name fmla已经解析的值
};


class ParseXml
{
public:
	ParseXml();
	ParseXml(const QString& filePath, const QString& shapeName);
	QVector<ComplexPath>& painterPath(); //传递路径
	QVector<QPair<QString, double>> controlShapeArg();
	void setControlShapeArg(const QString& adj, double val);
	double getValue(const QString& s); 
	Range shapeArgRange();
	void parseXmlStructure(); //解析xml结构将路径保存在_complexPathLst
	void setPathVisible(int path, int shown);
private:
	double convertEllipseAngle(double angle, double wr, double hr);
private:
	QVector<ComplexPath> _complexPathLst; //保存图形路径
private:
	QString _filePath; 
	QString _shapeName; 

	//下面三者是从文件中提取出来，需要解析出具体数值
	NameFmlas _nameFmla;
	QVector<Path> _pathLst; //路径参数
};


#endif