#include "paintWindow.h"

PaintWindow::PaintWindow()
: _startX(DEFAULT_OFFSET)
, _startY(DEFAULT_OFFSET)
, _expandTimes(1)
{
	setAutoFillBackground(true);
	QPalette p = palette();
	p.setColor(QPalette::Window, Qt::white);
	setPalette(p);
}

PaintWindow::~PaintWindow()
{
}

void PaintWindow::mousePressEvent(QMouseEvent *event)
{
	qDebug() << event->pos();
}

void PaintWindow::paintEvent(QPaintEvent*)
{
	QPainter painter(this);
	painter.translate(_startX, _startY);
	painter.scale(_expandTimes, _expandTimes);

	int sz = _pathLst.size(); // QVector<ComplexPath>
	int k = 1;
	for (int i = 0; i < sz; ++i)
	{
		ComplexPath path = _pathLst[i];
		if (path.isPathShown())
			drawComplexPath(path, painter); //考虑fill，stroke属性
		//获取每点坐标
		//for (int j = 0; j < _pathLst[i].getPath().elementCount(); j++)
		//{
		//	int x = _pathLst[i].getPath().elementAt(j).x;
		//	int y = _pathLst[i].getPath().elementAt(j).y;
		//	//QString coordinate = QString("[%1](%2,%3)").arg(k++).arg(x).arg(y);
		//	QString coordinate = QString("%1").arg(k++);
		//	//painter.drawText(x, y, coordinate);
		//}
	}
}

void PaintWindow::drawComplexPath(const ComplexPath& path, QPainter& painter)
{
	QHash<QString, int> fillMap;
	fillMap["darken"] = 1;
	fillMap["darkenLess"] = 2;
	fillMap["lighten"] = 3;
	fillMap["lightenLess"] = 4;
	fillMap["none"] = 5;
	fillMap["norm"] = 6;
	painter.save();

	QPainterPath p = path.getPath();

	switch (fillMap[path.getFill()])
	{
	case 1:
		{
			QBrush brush(QColor(193, 210, 250).darker().darker());
			painter.fillPath(p, brush);
		}
		break;
	case 2:
		{
			QBrush brush(QColor(193, 210, 250).darker());
			painter.fillPath(p, brush);
		}
		break;
	case 3:
		{
			QBrush brush(QColor(193, 210, 250).lighter().lighter());
			painter.fillPath(p, brush);
		}
		break;
	case 4:
		{	
			QBrush brush(QColor(193, 210, 250).lighter());
			painter.fillPath(p, brush);
		}
		break;
	case 5:
		//norm   do nothing
		break;
	case 6:
		{
			QBrush brush(QColor(193, 210, 250));
			painter.fillPath(p, brush);
		}
		break;
	default:
		break;
	}

	if (path.getStroke() == "true")
	{
		painter.drawPath(p);
	}
	painter.restore();
}

void PaintWindow::clearPainterPath()
{
	_pathLst.clear();
}

void PaintWindow::setPainterPath(const QVector<ComplexPath>& pathLst)
{
	_pathLst = pathLst;
}

void PaintWindow::setX(int dx)
{
	_startX = DEFAULT_OFFSET + dx;
}

void PaintWindow::setY(int dy)
{
	_startY = DEFAULT_OFFSET + dy;
}

void PaintWindow::setExpandTimes(double expandTimes)
{
	_expandTimes = expandTimes;
}

