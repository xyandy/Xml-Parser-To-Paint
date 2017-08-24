#include "readXml.h"


ReadXml::ReadXml(const QString& filePath, const QString& shapeName)
: _filePath(filePath)
, _shapeName(shapeName)
{
	readXmlFile();
}


bool ReadXml::readXmlFile()
{
	QFile file(_filePath);
	QDomDocument doc;
	QString error;
	int row = 0, column = 0;
	if (!doc.setContent(&file, false, &error, &row, &column))
	{
		QMessageBox::information(NULL, QString("title"), QString("read file failed"));
		file.close();
		return false;
	}
	file.close();
	if (doc.isNull())
	{
		QMessageBox::information(NULL, QString("title"), QString("document is null!"));
		return false;
	}

	////获取xml节点,定位到需要解析的图形
	QDomElement superElement = doc.documentElement();
	QDomNodeList shapeList = superElement.childNodes();
	int shapeCount = shapeList.count();

	QDomElement rootElement;
	for (int i = 0; i < shapeCount; ++i)
	{
		QDomNode node = shapeList.item(i);
		QDomElement nodeElement = node.toElement();
		QString nodeElementTagName = nodeElement.tagName();
		if (nodeElementTagName == _shapeName)
		{
			rootElement = nodeElement;
			break;
		}
	}
	//已经定位到_shapeName，获取路径参数
	QDomNodeList list = rootElement.childNodes();
	int count = list.count();
	for (int i = 0; i < count; ++i)
	{
		QDomNode node = list.item(i);
		QDomElement nodeElement = node.toElement();

		QString nodeElementTagName = nodeElement.tagName();

		if (nodeElementTagName == "avLst" || nodeElementTagName == "gdLst")
		{
			QDomNodeList childList = nodeElement.childNodes();
			int childListCount = childList.count();

			for (int j = 0; j < childListCount; ++j)
			{
				QDomNode childNode = childList.item(j);
				QDomElement childNodeElement = childNode.toElement();
				if (childNodeElement.hasAttribute("name") && childNodeElement.hasAttribute("fmla"))
				{
					QString nameValue = childNodeElement.attributeNode("name").value();
					QString fmlaValue = childNodeElement.attributeNode("fmla").value();
		
					if (nodeElementTagName == "avLst")
					{
						QPair<QString, double> pair;
						QStringList list = fmlaValue.split(QRegExp("\\s+"));
						double num = list.at(1).toDouble();
						pair.first = nameValue;
						pair.second = num;
						_avLst.push_back(pair);
					}
					else if (nodeElementTagName == "gdLst")
					{
						QPair<QString, QString> pair;
						pair.first = nameValue;
						pair.second = fmlaValue;
						_gdLst.push_back(pair);
					}
				}
			}
		}
		//else if (nodeElementTagName == "ahLst")
		//{
		//	// QHash<QString, QVector<QString>> _ahLst;
		//	QDomNodeList childList = nodeElement.childNodes();
		//	int childListCount = childList.count();
		//	for (int j = 0; j < childListCount; j++) 
		//	{
		//		QDomNode childNode = childList.item(j);
		//		QDomElement childNodeElement = childNode.toElement();
		//		if (childNodeElement.tagName() == "ahXY")
		//		{
		//			if (childNodeElement.hasAttribute("gdRefX"))
		//			{
		//				QVector<QString> minMax(2, "");
		//				minMax[0] = childNodeElement.attributeNode("minX").value();
		//				minMax[1] = childNodeElement.attributeNode("maxX").value();
		//				QString key = childNodeElement.attributeNode("gdRefX").value();
		//				_ahLst._range[key].first = minMax[0];
		//				_ahLst._range[key].second = minMax[1];

		//			}
		//			if (childNodeElement.hasAttribute("gdRefY"))
		//			{
		//				QVector<QString> minMax(2, "");
		//				minMax[0] = childNodeElement.attributeNode("minY").value();
		//				minMax[1] = childNodeElement.attributeNode("maxY").value();
		//				QString key = childNodeElement.attributeNode("gdRefY").value();
		//				_ahLst._range[key].first = minMax[0];
		//				_ahLst._range[key].second = minMax[1];
		//			}
		//		}
		//		else if (childNodeElement.tagName() == "ahPolar")
		//		{
		//			if (childNodeElement.hasAttribute("gdRefR"))
		//			{
		//				QVector<QString> minMax(2, "");
		//				minMax[0] = childNodeElement.attributeNode("minR").value();
		//				minMax[1] = childNodeElement.attributeNode("maxR").value();
		//				QString key = childNodeElement.attributeNode("gdRefR").value();
		//				_ahLst._range[key].first = minMax[0];
		//				_ahLst._range[key].second = minMax[1];
		//			}
		//			if (childNodeElement.hasAttribute("gdRefAng"))
		//			{
		//				QVector<QString> minMax(2, "");
		//				minMax[0] = childNodeElement.attributeNode("minAng").value();
		//				minMax[1] = childNodeElement.attributeNode("maxAng").value();
		//				QString key = childNodeElement.attributeNode("gdRefAng").value();
		//				_ahLst._range[key].first = minMax[0];
		//				_ahLst._range[key].second = minMax[1];
		//			}
		//		}
		//	}
		//}
		else if (nodeElementTagName == "pathLst")
		{
			QDomNodeList childList = nodeElement.childNodes();
			int childListCount = childList.count();
			for (int j = 0; j < childListCount; j++) //path
			{
				QDomNode childNode = childList.item(j);
				QDomElement childNodeElement = childNode.toElement();
				//path的下一层，可以得到坐标

				if (childNodeElement.tagName() == "path")
				{
					//调整坐标系
					Path path;
					if (childNodeElement.hasAttribute("w"))
					{
						QString w = childNodeElement.attributeNode("w").value();
						path._w = w;
					}
					if (childNodeElement.hasAttribute("h"))
					{
						QString h = childNodeElement.attributeNode("h").value();
						path._h = h;
					}
					//检查fill，stroke属性
					if (childNodeElement.hasAttribute("fill"))
					{
						QString fill = childNodeElement.attributeNode("fill").value();
						path._fill = fill;
					}
					else
					{
						path._fill = "norm";
					}
					if (childNodeElement.hasAttribute("stroke"))
					{
						QString stroke = childNodeElement.attributeNode("stroke").value();
						path._stroke = stroke;
					}
					else
					{
						path._stroke = "true";
					}

					//具体要绘制什么图形，moveTo，lnTo等等
					QDomNodeList xyList = childNodeElement.childNodes();
					int xyListCount = xyList.count();
					
					for (int k = 0; k < xyListCount; ++k)
					{
						QDomNode labelNode = xyList.item(k);
						QDomElement labelNodeElement = labelNode.toElement();
						QString labelTagName = labelNodeElement.tagName();

						if (labelTagName == "moveTo" || labelTagName == "lnTo")
						{
							QDomElement xy = labelNodeElement.firstChildElement();
							QString x = xy.attributeNode("x").value();
							QString y = xy.attributeNode("y").value();
							QVector<QString> whatPath(3, "");
							whatPath[0] = labelTagName;
							whatPath[1] = x;
							whatPath[2] = y;
							path._differentPath.push_back(whatPath);
						}
						else if (labelTagName == "arcTo")
						{
							QString wR = labelNodeElement.attributeNode("wR").value();
							QString hR = labelNodeElement.attributeNode("hR").value();
							QString stAng = labelNodeElement.attributeNode("stAng").value();
							QString swAng = labelNodeElement.attributeNode("swAng").value();
							QVector<QString> whatPath(5, "");
							whatPath[0] = labelTagName;
							whatPath[1] = wR;
							whatPath[2] = hR;
							whatPath[3] = stAng;
							whatPath[4] = swAng;
							path._differentPath.push_back(whatPath);
						}
						else if (labelTagName == "cubicBezTo" || labelTagName == "quadBezTo")
						{
							int size = 5;
							if (labelTagName == "cubicBezTo")
								size = 7;
							QVector<QString> whatPath(size, "");
							whatPath[0] = labelTagName;
							int k = 1;
							QDomNodeList cubicList = labelNodeElement.childNodes();
							int cubicListCount = cubicList.count();
							for (int j = 0; j < cubicListCount; j++)
							{
								QDomNode cubicNode = cubicList.item(j);
								QDomElement cubicNodeElement = cubicNode.toElement();
								QString x = cubicNodeElement.attributeNode("x").value();
								QString y = cubicNodeElement.attributeNode("y").value();
								whatPath[k++] = x;
								whatPath[k++] = y;
							}
							path._differentPath.push_back(whatPath);
						}
						else if (labelTagName == "close")
						{
							QVector<QString> whatPath;
							whatPath.push_back("close");
							path._differentPath.push_back(whatPath);
						}
					}
					_pathLst.push_back(path);
				} // if (childNodeElement.tagName() == "path")
			}
		}
	}
	return true;
}

QVector<QPair<QString, double>> ReadXml::getAvLst() const
{
	return _avLst;
}

QVector<QPair<QString, QString>> ReadXml::getGdLst() const
{
	return _gdLst;
}

Range ReadXml::getAhLst() const
{
	return _ahLst;
}

QVector<Path> ReadXml::getPathLst() const
{
	return _pathLst;
}