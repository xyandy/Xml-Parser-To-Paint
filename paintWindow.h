#ifndef PAINT_WINDOW_H
#define PAINT_WINDOW_H

#include "head.h"
#include "complexPath.h"


class PaintWindow : public QMainWindow
{
	Q_OBJECT
	enum { DEFAULT_OFFSET = 200 };
public:
	PaintWindow();
	~PaintWindow();
	void setPainterPath(const QVector<ComplexPath>& path);
	void clearPainterPath(); 
	void setX(int dx);
	void setY(int dy);
	void setExpandTimes(double expandTimes);
private:
	void paintEvent(QPaintEvent*);
	void mousePressEvent(QMouseEvent *event);

	void drawComplexPath(const ComplexPath& path, QPainter& painter);
private:
	QVector<ComplexPath> _pathLst;
	int _startX;
	int _startY;
	double _expandTimes;
};


#endif