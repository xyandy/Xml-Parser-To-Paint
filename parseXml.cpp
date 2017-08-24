#include "ParseXml.h"

static QHash<QString, int> initOperationMap()
{
	enum {
		MulDiv = 1, AddSub, AddDiv, IfElse, Abs, At2, Cat2,
		Cos, Max, Min, Mod, Pin, Sat2, Sin, Sqrt, Tan, Val,
	};
	QHash<QString, int> opMap;
	opMap["*/"] = MulDiv;
	opMap["+-"] = AddSub;
	opMap["+/"] = AddDiv;
	opMap["?:"] = IfElse;
	opMap["abs"] = Abs;
	opMap["at2"] = At2;
	opMap["cat2"] = Cat2;

	opMap["cos"] = Cos;
	opMap["max"] = Max;
	opMap["min"] = Min;
	opMap["mod"] = Mod;
	opMap["pin"] = Pin;
	opMap["sat2"] = Sat2;
	opMap["sin"] = Sin;
	opMap["sqrt"] = Sqrt;
	opMap["tan"] = Tan;
	opMap["val"] = Val;
	return opMap;
}

QHash<QString, int> Fmla::_opMap(initOperationMap()); //静态对象类外初始化

Fmla::Fmla()
{}

Fmla::Fmla(const QString& fmla)
{
	initOperationMap();
	QStringList list = fmla.split(QRegExp("\\s+"));
	_operation = _opMap[list.at(0)];

	for (int i = 1; i < (int)list.size(); i++)
	{
		QString temp = list.at(i);
		_args.push_back(temp);
	}
}

int Fmla::getFmlaOPeration() const
{
	return _operation;
}

QVector<QString> Fmla::getFmlaArgs() const
{
	return _args;
}

////////////////////////////////////////////////////

NameFmlas::NameFmlas()
{
	initSimpleTypeMap();
	initNameMap();
}

void NameFmlas::setGdLst(QVector<QPair<QString, QString>> gdLst)
{
	QVector<QPair<QString, QString>>::iterator it = gdLst.begin();
	while (it != gdLst.end())
	{
		Fmla fmla(it->second);
		QPair<QString, Fmla> pair;
		pair.first = it->first;
		pair.second = fmla;

		_gdLst.push_back(pair);
		++it;
	}
}

void NameFmlas::setAvLst(QVector<QPair<QString, double>> avLst)
{
	QVector<QPair<QString, double>>::iterator it = avLst.begin();
	while (it != avLst.end())
	{
		QPair<QString, double> pair;
		pair.first = it->first;
		pair.second = it->second;
		_avLst.push_back(pair);
		++it;
	}
}

void NameFmlas::setAhLst(Range range)
{
	_ahLst = range;
}

Range NameFmlas::getAhLst()
{
	return _ahLst;
}

void NameFmlas::initSimpleTypeMap()
{
	_simpleTypeMap["hc"] = "*/ w 1.0 2.0";
	_simpleTypeMap["hd2"] = "*/ h 1.0 2.0";
	_simpleTypeMap["hd3"] = "*/ h 1.0 3.0";
	_simpleTypeMap["hd4"] = "*/ h 1.0 4.0";
	_simpleTypeMap["hd5"] = "*/ h 1.0 5.0";
	_simpleTypeMap["hd6"] = "*/ h 1.0 6.0";
	_simpleTypeMap["hd8"] = "*/ h 1.0 8.0";
	_simpleTypeMap["ls"] = "max w h";
	_simpleTypeMap["ss"] = "min w h";
	_simpleTypeMap["ss2"] = "*/ ss 1.0 2.0";
	_simpleTypeMap["ss4"] = "*/ ss 1.0 4.0";
	_simpleTypeMap["ss6"] = "*/ ss 1.0 6.0";
	_simpleTypeMap["ss8"] = "*/ ss 1.0 8.0";
	_simpleTypeMap["ss16"] = "*/ ss 1.0 16.0";
	_simpleTypeMap["ss32"] = "*/ ss 1.0 32.0";
	_simpleTypeMap["vc"] = "*/ h 1.0 2.0";
	_simpleTypeMap["wd2"] = "*/ w 1.0 2.0";
	_simpleTypeMap["wd3"] = "*/ w 1.0 3.0";
	_simpleTypeMap["wd4"] = "*/ w 1.0 4.0";
	_simpleTypeMap["wd5"] = "*/ w 1.0 5.0";
	_simpleTypeMap["wd6"] = "*/ w 1.0 6.0";
	_simpleTypeMap["wd8"] = "*/ w 1.0 8.0";
	_simpleTypeMap["wd10"] = "*/ w 1.0 10.0";
}

void NameFmlas::initNameMap()
{
	_nameMap["3cd8"] = 8100000.0;
	_nameMap["5cd8"] = 13500000.0;
	_nameMap["7cd8"] = 18900000.0;
	_nameMap["3cd4"] = 16200000.0;
	_nameMap["cd2"] = 10800000.0;
	_nameMap["cd4"] = 5400000.0;
	_nameMap["cd8"] = 2700000.0;
	_nameMap["l"] = 0;
	_nameMap["t"] = 0;
	//设置默认值h,w
	_nameMap["h"] = 200;
	_nameMap["w"] = 200;
	_nameMap["b"] = _nameMap["h"];
	_nameMap["r"] = _nameMap["w"];
}

double NameFmlas::getValue(const QString& s)
{
	bool ok = true;
	double x = s.toDouble(&ok);
	if (ok) //解析数字成功！
		return x;

	if (_nameMap.find(s) == _nameMap.end())
	{
		QString str = _simpleTypeMap[s];
		Fmla fmla(str);
		return calculateFormula(fmla);
	}
	else
		return _nameMap[s];
}

double NameFmlas::calculateFormula(const Fmla& fmla)
{
	int op = fmla.getFmlaOPeration();
	QVector<QString> v = fmla.getFmlaArgs();
	
	//需要设定adj范围
	bool needSetRange = false;

	if (v.size() >= 2 && v[1].contains("adj"))
		needSetRange = true;

	QVector<double> arr;
	for (int i = 0; i < (int)v.size(); i++)
	{
		QString temp = v[i];
		double xx = getValue(temp);
		arr.push_back(xx);
	}
	int sz = arr.size();
	//MulDiv = 1, AddSub, AddDiv, IfElse, Abs, At2, Cat2,
	//Cos, Max, Min, Mod, Pin, Sat2, Sin, Sqrt, Tan, Val,
	double ret = 0.0;

	switch (op)
	{
		case MulDiv:
			{
				if (sz != 3)
					return 0.0;
				double ret = ((arr[0] * arr[1]) / arr[2]);
				return ret;
			}
			break;
		case AddSub:
			{						
			   if (sz != 3)
				   return 0.0;
			   double ret = ((arr[0] + arr[1]) - arr[2]);
			   return ret;
			}
			break;
		case AddDiv:
			{
				if (sz != 3)
					return 0.0;
				double ret = ((arr[0] + arr[1]) / arr[2]);
				return ret;
			}
			break;
		case IfElse:
			{
				if (sz != 3)
					return 0.0;
				if (arr[0] > 0)
					return arr[1];
				else
					return arr[2];
			}
			break;
		case Abs:
			{
				if (sz != 1)
					return 0.0;
				return (arr[0] > 0) ? arr[0] : -arr[0];
			}
			break;
		case At2:
			{
				if (sz != 2)
					return 0.0;
				double ret = qRadiansToDegrees(qAtan2(arr[1], arr[0])) * 60000;
				return ret;
			}
			break;
		case Cat2:
			{
				 if (sz != 3)
					 return 0.0;
				 double x = arr[0];
				 double yInRadians = qDegreesToRadians(arr[1] / 60000);
				 double zInRadians = qDegreesToRadians(arr[2] / 60000);
				 double ret = x * qCos(qAtan2(zInRadians, yInRadians));
				 return ret;
			}
			break;
		case Cos:
			{
				if (sz != 2)
					return 0.0;
				double x = arr[0];
				double yInRadians = qDegreesToRadians(arr[1] / 60000);
				return x * qCos(yInRadians);
			}
			break;
		case Max:
			{
				if (sz != 2)
					return 0.0;
				return arr[0] > arr[1] ? arr[0] : arr[1];
			}
			break;
		case Min:
			{
				if (sz != 2)
					return 0.0;
				return arr[0] < arr[1] ? arr[0] : arr[1];
			}
			break;
		case Mod:
			{
				if (sz != 3)
					return 0.0;
				return sqrt(arr[0] * arr[0] + arr[1] * arr[1] + arr[2] * arr[2]);
			}
			break;
		case Pin:
			{
				if (sz != 3)
					return 0.0;
				if (needSetRange)
				{
					QPair<QString, QString> pair;
					pair.first = QString::number(arr[0]);
					pair.second = QString::number(arr[2]);
					_ahLst._range[v[1]] = pair;
				}

				if (arr[1] < arr[0])
					return arr[0];
				else if (arr[1] > arr[2])
					return arr[2];
				else
					return arr[1];
			}
			break;
		case Sat2:
			{
				if (sz != 3)
					return 0.0;
				double x = arr[0];
				double yInRadians = qDegreesToRadians(arr[1] / 60000);
				double zInRadians = qDegreesToRadians(arr[2] / 60000);
				return arr[0] * qSin(qAtan2(arr[2], arr[1]));
			}
			break;
		case Sin:
			{
				if (sz != 2)
					return 0.0;
				double x = arr[0];
				double yInRadians = qDegreesToRadians(arr[1] / 60000);
				return x * qSin(yInRadians);
			}
			break;
		case Sqrt:
			{
				 if (sz != 1)
					 return 0.0;
				 double ret = sqrt(arr[0]);
				 return ret;
			}
			break;	
		case Tan:
			{
				if (sz != 2)
					return 0.0;
				double x = arr[0];
				double yInRadians = qDegreesToRadians(arr[1] / 60000);
			    return x * qTan(yInRadians);
			}
			break;
		case Val:
			{
				if (sz != 1)
					return 0.0;
				return arr[0];
			}
			break;
		default:
			break;
	} //end of case

	return ret;
}

void NameFmlas::setAvLst(const QString& adj, double val)
{
	int size = _avLst.size();
	int i = 0;
	for (; i < size; i++)
	{
		if (_avLst[i].first == adj)
			break;
	}
	_avLst[i].second = val;
}

void NameFmlas::parseAllNameFmla()
{
	//设置默认的图形变化参数adj1，adj2等等   其中QVector<QPair<QString, double>> _avLst保存图形变化的参数
	int size = _avLst.size();
	for (int i = 0; i < size; i++)
	{
		QString name = _avLst[i].first;
		double fmlaValue = _avLst[i].second;
		_nameMap[name] = fmlaValue;
	}

	//解析复杂嵌套公式name-fmla    其中QVector<QPair<QString, Fmla>> _gdLst保存name-fmla
	size = _gdLst.size();
	for (int i = 0; i < size; i++)
	{
		QString name = _gdLst[i].first;
		if (name == "q10" || name == "q11")
		{
			int o = 0;
		}
		double fmlaValue = calculateFormula(_gdLst[i].second);
		_nameMap[name] = fmlaValue;
	}
#if 0
	//调试用
	QMap<QString, double>::iterator it11 = _nameMap.begin();
	while (it11 != _nameMap.end())
	{
		qDebug() << it11.key() << " : " << it11.value();
		++it11;
	}
#endif 
}

QVector<QPair<QString, double>> NameFmlas::getAvLst() const
{
	return _avLst;
}

///////////////////////////////////////////////////

ParseXml::ParseXml()
{}

ParseXml::ParseXml(const QString& filePath, const QString& shapeName)
: _filePath(filePath)
, _shapeName(shapeName)
{
	ReadXml xmlStructure(filePath, shapeName);
	_nameFmla.setAvLst(xmlStructure.getAvLst());
	_nameFmla.setGdLst(xmlStructure.getGdLst());
	_nameFmla.setAhLst(xmlStructure.getAhLst());  
	_pathLst = xmlStructure.getPathLst();
	parseXmlStructure();
}

void ParseXml::parseXmlStructure()
{
	//图形参数变化会导致很多fmla变化需要重新解析
	_nameFmla.parseAllNameFmla();

	//QVector<ComplexPath> _complexPathLst;
	//生成路径  路径保存在_complexPathLst 
	_complexPathLst.clear();
	//struct Path
	//{
	//	QString _fill;
	//	QString _stroke;
	//	QString _w;
	//	QString _h;
	//	QVector<QVector<QString>> _differentPath;
	//};
	int pathSize = _pathLst.size();
	for (int i = 0; i < pathSize; i++)
	{
		Path tempPath = _pathLst[i];
		ComplexPath cPath;
		//处理fill,stroke
		if (tempPath._fill != "")
			cPath.setFill(tempPath._fill);
		if (tempPath._stroke != "")
			cPath.setStroke(tempPath._stroke);
		//处理w，h，坐标系变换
		double wRatio = 1.0;
		double hRatio = 1.0;
		if (tempPath._w != "")
		{
			QString w = tempPath._w;
			bool ok = true;
			wRatio = _nameFmla.getValue("w") / w.toDouble(&ok);
		}
		if (tempPath._h != "")
		{
			QString h = tempPath._h;
			bool ok = true;
			hRatio = _nameFmla.getValue("h") / h.toDouble(&ok);
		}
		//绘制一条路径
		QVector<QVector<QString>> smallPath = tempPath._differentPath;
		int smallPathSize = smallPath.size();
		for (int j = 0; j < smallPathSize; j++)
		{
			if (smallPath[j][0] == "moveTo")
			{
				double x = getValue(smallPath[j][1]) * wRatio;
				double y = getValue(smallPath[j][2]) * hRatio;
				cPath.getPath().moveTo(x, y);
			}
			else if (smallPath[j][0] == "lnTo")
			{
				double x = getValue(smallPath[j][1]) * wRatio;
				double y = getValue(smallPath[j][2]) * hRatio;
				cPath.getPath().lineTo(x, y);
			}
			else if (smallPath[j][0] == "arcTo")
			{
				QString wR = smallPath[j][1];
				QString hR = smallPath[j][2];
				QString stAng = smallPath[j][3];
				QString swAng = smallPath[j][4];
				double wRLen = getValue(wR) * wRatio;
				double hRLen = getValue(hR) * hRatio;
				//注意qt和xml角度表示不同 1度=60000th
				double startAngle = getValue(stAng) / 60000;
				double swingAngle = getValue(swAng) / 60000;
				//注意qt和xml角度计算的不同，qt是逆时针，xml是顺时针
				swingAngle = -swingAngle;
				startAngle = 360 - startAngle;
				//保证startAngle在[0，360)
				startAngle -= ((int)startAngle / 360) * 360;
				if (startAngle < 0)
					startAngle += 360;
				double endAngle = startAngle + swingAngle;
#if 1
				//qDebug() << "before convert, startAngle = " << startAngle << ", endAngle = " << endAngle << ", swingAngle = " << swingAngle;
				//对于椭圆画弧的角度和圆形的角度计算不同，需要单独处理
				if (wRLen != hRLen && !qFuzzyCompare(swingAngle, qAbs(360))) //对于圆形 或者 椭圆旋转角swingAngle是360或者-360 不需要处理
				{
					endAngle = convertEllipseAngle(endAngle, wRLen, hRLen);
					startAngle = convertEllipseAngle(startAngle, wRLen, hRLen);

					double angle = endAngle - startAngle;
					if (angle > 0 && swingAngle < 0)
						swingAngle = angle - 360;
					else if (angle < 0 && swingAngle > 0)
						swingAngle = angle + 360;
					else
						swingAngle = angle;
				}
				//qDebug() << "before convert, startAngle = " << startAngle << ", endAngle = " << endAngle << ", swingAngle = " << swingAngle;
#endif 
				QPainterPath arcPath;
				QRectF rect(-wRLen, -hRLen, 2 * wRLen, 2 * hRLen);
				arcPath.arcMoveTo(rect, startAngle);
				QPointF beginPos = arcPath.currentPosition();
				arcPath.arcTo(rect, startAngle, swingAngle);

				double formX = cPath.getPath().currentPosition().x();
				double formY = cPath.getPath().currentPosition().y();
				double bx = beginPos.x();
				double by = beginPos.y();
				arcPath.translate(formX - bx, formY - by);
				//获取曲线上的所有点
				int arcPathSize = arcPath.elementCount();
				for (int i = 1; i < arcPathSize;)
				{
					QPointF c1 = arcPath.elementAt(i++);
					QPointF c2 = arcPath.elementAt(i++);
					QPointF endPoint = arcPath.elementAt(i++);
					cPath.getPath().cubicTo(c1, c2, endPoint);
				}
			}
			else if (smallPath[j][0] == "cubicBezTo")
			{
				QPointF points[3];
				int pi = 0;
				for (int i = 1; i < 7; )
				{
					double x = getValue(smallPath[j][i++]) * wRatio;
					double y = getValue(smallPath[j][i++]) * hRatio;
					points[pi].setX(x);
					points[pi].setY(y);
					pi++;
				}
				cPath.getPath().cubicTo(points[0], points[1], points[2]);
			}
			else if (smallPath[j][0] == "quadBezTo")
			{
				QPointF points[2];
				int pi = 0;
				for (int i = 1; i < 5;)
				{
					double x = getValue(smallPath[j][i++]) * wRatio;
					double y = getValue(smallPath[j][i++]) * hRatio;
					points[pi].setX(x);
					points[pi].setY(y);
					pi++;
				}
				cPath.getPath().quadTo(points[0], points[1]);
			}
			else if (smallPath[j][0] == "close")
			{
				cPath.getPath().closeSubpath();
			}
		}
		_complexPathLst.push_back(cPath);
	} //end of for()
}

double ParseXml::getValue(const QString& s)
{
	return _nameFmla.getValue(s);
}

double ParseXml::convertEllipseAngle(double angle, double wR, double hR)
{
	//double temp1 = qTan(qDegreesToRadians(45.0));
	//double temp = qRadiansToDegrees(atan2(1, 1));
	if (angle > 360)
		angle -= ((int)angle / 360) * 360;
	if (angle < 0)
		angle += 360;

	double delta = 0;
	if (angle > 90 && angle <= 270)
	{
		delta = 180;
	}
	else if (angle > 270)
	{
		delta = 360;
	}
	if (wR != hR)
	{
		//tan p = a/b * tan q 其中q为已知angle，a为椭圆长轴，b为短轴
		double yStart = wR * qTan(qDegreesToRadians(angle));
		angle = delta + qRadiansToDegrees(qAtan2(yStart, hR));
	}
	return angle;
}

QVector<QPair<QString, double>> ParseXml::controlShapeArg()
{
	//return _avLst;
	return _nameFmla.getAvLst();
}

void ParseXml::setControlShapeArg(const QString& adj, double val)
{
	_nameFmla.setAvLst(adj, val);
}

Range ParseXml::shapeArgRange()
{
	return _nameFmla.getAhLst();
}

QVector<ComplexPath>& ParseXml::painterPath()
{
	return _complexPathLst;
}

void ParseXml::setPathVisible(int path, int shown)
{
	_complexPathLst[path].setPathShown(shown);
}