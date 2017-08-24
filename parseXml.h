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
	void initSimpleTypeMap();//��ʼ��_simpleTypeMap
	void initNameMap(); //��ʼ��_nameMap
	double calculateFormula(const Fmla& fmla);//����formula
private:
	QVector<QPair<QString, Fmla>> _gdLst;
	QVector<QPair<QString, double>> _avLst; //����ͼ�α仯�Ĳ���
	Range _ahLst;//�����仯�ķ�Χ

	QMap<QString, QString> _simpleTypeMap; //����Ԥ�ȶ���ĳ���
	QMap<QString, double> _nameMap; //����name fmla�Ѿ�������ֵ
};


class ParseXml
{
public:
	ParseXml();
	ParseXml(const QString& filePath, const QString& shapeName);
	QVector<ComplexPath>& painterPath(); //����·��
	QVector<QPair<QString, double>> controlShapeArg();
	void setControlShapeArg(const QString& adj, double val);
	double getValue(const QString& s); 
	Range shapeArgRange();
	void parseXmlStructure(); //����xml�ṹ��·��������_complexPathLst
	void setPathVisible(int path, int shown);
private:
	double convertEllipseAngle(double angle, double wr, double hr);
private:
	QVector<ComplexPath> _complexPathLst; //����ͼ��·��
private:
	QString _filePath; 
	QString _shapeName; 

	//���������Ǵ��ļ�����ȡ��������Ҫ������������ֵ
	NameFmlas _nameFmla;
	QVector<Path> _pathLst; //·������
};


#endif