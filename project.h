#ifndef PROJECT_H
#define PROJECT_H

#include "head.h"
#include "parseXml.h"
#include "paintWindow.h"


class ControlShapeWidget : public QWidget
{
	enum { MAX_SIZE = 8 };
	Q_OBJECT
public:
	ControlShapeWidget(QGridLayout* layout);
	void setAllWidgetsInvisible();
	void setOneWidgetVisible(const QString& arg, double value, double min, double max);
	void setCheckBoxsVisible(int size);
signals:
	void changeShapeArg(const QString& adj, double value);
	void setOnePathVisible(int i, bool flag);
public slots:
	void spinBoxValueChanged(int val);
	void sliderValueChanged(int val);
	void checkBoxChanged(int flag);
private:
	QVector<QLabel*> _labels;
	QVector<QSpinBox*> _spinBoxs;
	QVector<QSlider*> _sliders;
	QVector<QCheckBox*> _checkBoxs;
	int _cur;
};


class Project : public QMainWindow
{
	enum { SIZE = 3 };
	Q_OBJECT
public:
	Project(QWidget *parent = 0);
//signals:
	
private slots:
	void fillComboBox();
	void showShape(const QString& name);
	void changeShape(const QString& adj, double val);
	void upDownTranslation(int dy);
	void leftRightTranslation(int dx);
	void shrinkExpandTranslation(const QString& times);
	void showPath(int i, bool flag);
private:
	Ui::ProjectClass ui;
	
	PaintWindow* _leftWindow;
	QComboBox* _comboBox; //选择图形下拉框
	QComboBox* _expandBox; //图形缩放
	QSpinBox* _spinBox[SIZE - 1];
	QSlider* _slider[SIZE - 1];
	
	ControlShapeWidget* _csw;
	QVector<QString> _shapeNames; //图形集合
	QString _filePath; //文件位置
	ParseXml _xmlStructure;
};

#endif // PROJECT_H
