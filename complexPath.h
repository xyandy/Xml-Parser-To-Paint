#ifndef COMPLEX_PATH_H
#define COMPLEX_PATH_H

#include "head.h"


class ComplexPath
{

public:
	ComplexPath();
	~ComplexPath();
	bool isPathShown();
	void setPathShown(bool flag);
	void setFill(const QString& fill);
	QString getFill() const;
	void setStroke(const QString& stroke);
	QString getStroke() const;
	QPainterPath& getPath();
	const QPainterPath& getPath() const;
private:
	QPainterPath _path;
	bool _isShown;
	QString _fill;
	QString _stroke;
};


#endif