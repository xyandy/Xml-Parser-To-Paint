#include "complexPath.h"


ComplexPath::ComplexPath()
: _fill("norm")
, _stroke("true")
, _isShown(true)
{
}

ComplexPath::~ComplexPath()
{

}

void ComplexPath::setPathShown(bool flag)
{
	_isShown = flag;
}

bool ComplexPath::isPathShown()
{
	return _isShown;
}

void ComplexPath::setFill(const QString& fill)
{
	_fill = fill;
}

QString ComplexPath::getFill() const 
{
	return _fill;
}

QString ComplexPath::getStroke() const 
{
	return _stroke;
}

void ComplexPath::setStroke(const QString& stroke)
{
	_stroke = stroke;
}

QPainterPath& ComplexPath::getPath()
{
	return _path;
}

const QPainterPath& ComplexPath::getPath() const
{
	return _path;
}