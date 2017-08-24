#include "project.h"

ControlShapeWidget::ControlShapeWidget(QGridLayout* layout)
: _cur(0)
{
	_labels.resize(MAX_SIZE);
	_spinBoxs.resize(MAX_SIZE);
	_sliders.resize(MAX_SIZE);
	_checkBoxs.resize(MAX_SIZE - 2);
	//���ø�ѡ��,ѡ����ʾ·��
	QHBoxLayout* checkBoxLayout = new QHBoxLayout;
	for (int i = 0; i < MAX_SIZE - 2; i++)
	{
		QString num = QString("path") + QString::number(i + 1);
		_checkBoxs[i] = new QCheckBox(num);
		_checkBoxs[i]->setChecked(true);
		checkBoxLayout->addWidget(_checkBoxs[i]);
	}
	layout->addLayout(checkBoxLayout, 0, 0, 1, 3);
	
	for (int i = 0; i < MAX_SIZE; ++i)
	{
		_labels[i] = new QLabel;
		_spinBoxs[i] = new QSpinBox;
		_sliders[i] = new QSlider(Qt::Horizontal);
		layout->addWidget(_labels[i], i+1, 0, 1, 1);
		layout->addWidget(_spinBoxs[i], i+1, 1, 1, 1);
		layout->addWidget(_sliders[i], i+1, 2, 1, 1);
	}
	setAllWidgetsInvisible();
}

void ControlShapeWidget::spinBoxValueChanged(int val)
{
	QSpinBox* p = qobject_cast<QSpinBox*>(sender()); //��ȡ�ź�Դ
	int i = 0;
	for (; i < _cur; i++)
	{
		if (_spinBoxs[i] == p)
			break;
	}
	QString adj = _labels[i]->text();
	emit changeShapeArg(adj, (double)val); //�����ź�
}

void ControlShapeWidget::sliderValueChanged(int val)
{
	QSlider* p = qobject_cast<QSlider*>(sender()); //��ȡ�ź�Դ
	int i = 0;
	for (; i < _cur; i++)
	{
		if (_sliders[i] == p)
			break;
	}
	QString adj = _labels[i]->text();
	emit changeShapeArg(adj, (double)val); //�����ź�
}

void ControlShapeWidget::setAllWidgetsInvisible()
{
	for (int i = 0; i < MAX_SIZE; ++i)
	{
		_spinBoxs[i]->setVisible(false);
		_labels[i]->setVisible(false);
		_sliders[i]->setVisible(false);
		if (i < MAX_SIZE - 2)
			_checkBoxs[i]->setVisible(false);
	}
	_cur = 0;
}

void ControlShapeWidget::setOneWidgetVisible(const QString& arg, double value, double min, double max)
{
	_labels[_cur]->setText(arg);
	QFont font;
	font.setPointSize(12);
	_labels[_cur]->setFont(font);
	_sliders[_cur]->setRange(min, max);
	_sliders[_cur]->setValue(value);
	_spinBoxs[_cur]->setRange(min, max);
	_spinBoxs[_cur]->setValue(value);
	connect(_sliders[_cur], SIGNAL(valueChanged(int)), _spinBoxs[_cur], SLOT(setValue(int)));
	connect(_spinBoxs[_cur], SIGNAL(valueChanged(int)), _sliders[_cur], SLOT(setValue(int)));
	connect(_sliders[_cur], SIGNAL(valueChanged(int)), this, SLOT(sliderValueChanged(int)));
	connect(_spinBoxs[_cur], SIGNAL(valueChanged(int)), this, SLOT(spinBoxValueChanged(int)));

	_spinBoxs[_cur]->setVisible(true);
	_labels[_cur]->setVisible(true);
	_sliders[_cur]->setVisible(true);
	_cur++;
}

void ControlShapeWidget::setCheckBoxsVisible(int size)
{
	for (int i = 0; i < size; i++)
	{
		_checkBoxs[i]->setVisible(true);
		_checkBoxs[i]->setChecked(true);
		connect(_checkBoxs[i], SIGNAL(stateChanged(int)), this, SLOT(checkBoxChanged(int)));
	}
}

void ControlShapeWidget::checkBoxChanged(int flag)
{
	QCheckBox* p = qobject_cast<QCheckBox*>(sender());
	int i = 0;
	for (; i < MAX_SIZE; i++)
	{
		if (_checkBoxs[i] == p)
			break;
	}
	emit setOnePathVisible(i, flag);
}

/********************************************************/

Project::Project(QWidget *parent)
: QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowTitle("MainWindow");
	resize(1000, 800);
	//setWindowFlags(Qt::WindowCloseButtonHint);

	//���ԭ���Ĳ���
	QWidget *centralWidget = new QWidget;
	this->setCentralWidget(centralWidget);
	
	//���û�ͼ�����
	_leftWindow = new PaintWindow;
	QHBoxLayout* leftLayout = new QHBoxLayout;
	leftLayout->addWidget(_leftWindow);
	
	//��������壬���ϵ���������ѡ��ͼ�ο򣬿���ͼ����״��ͼ��ƽ������
	QVBoxLayout* rightLayout = new QVBoxLayout;

	//ͼ��ѡ���
	QHBoxLayout* chooseShape = new QHBoxLayout;
	QLabel* chooselabel = new QLabel("choose shape");
	QFont font;
	font.setPointSize(15);
	chooselabel->setFont(font);
	QPalette pe;
	pe.setColor(QPalette::WindowText, Qt::red);
	chooselabel->setPalette(pe);
	_comboBox = new QComboBox;
	_comboBox->addItem("   "); //�źŻ��Ƶȶ�ȡ���ļ���������
	chooseShape->addWidget(chooselabel);
	chooseShape->addWidget(_comboBox);
	rightLayout->addLayout(chooseShape);

	//����ͼ����״
	QGridLayout* _controlShape = new QGridLayout;
	_csw = new ControlShapeWidget(_controlShape);
	connect(_csw, SIGNAL(changeShapeArg(const QString&, double)), this, SLOT(changeShape(const QString&, double))); //spinbox��slide�źŲ�
	connect(_csw, SIGNAL(setOnePathVisible(int, bool)), this, SLOT(showPath(int, bool))); //checkBox�źŲ�

	rightLayout->addLayout(_controlShape);

	//ͼ��ƽ������
	QVBoxLayout* translateShape = new QVBoxLayout;
	QHBoxLayout* smallLayout[SIZE];

	QLabel* labels[SIZE];
	for (int i = 0; i < SIZE; i++)
	{
		labels[i] = new QLabel;
		smallLayout[i] = new QHBoxLayout;	
		smallLayout[i]->addWidget(labels[i]);

		if (i != SIZE - 1)
		{
			_spinBox[i] = new QSpinBox;
			_slider[i] = new QSlider(Qt::Horizontal);
			_spinBox[i]->setRange(-200, 200);
			_slider[i]->setRange(-200, 200);
			connect(_slider[i], SIGNAL(valueChanged(int)), _spinBox[i], SLOT(setValue(int)));
			connect(_spinBox[i], SIGNAL(valueChanged(int)), _slider[i], SLOT(setValue(int)));
			smallLayout[i]->addWidget(_spinBox[i]);
			smallLayout[i]->addWidget(_slider[i]);
		}
		else
		{
			_expandBox = new QComboBox;
			_expandBox->addItem("1.0");
			_expandBox->addItem("0.25");
			_expandBox->addItem("0.50");
			_expandBox->addItem("0.75");
			_expandBox->addItem("2.0");
			_expandBox->addItem("3.0");
			smallLayout[i]->addWidget(_expandBox);
		}
		translateShape->addLayout(smallLayout[i]);
	}
	//QFont font;
	font.setPointSize(12);
	labels[0]->setText(tr("up-down"));
	labels[0]->setFont(font);
	labels[1]->setText(tr("left-right"));
	labels[1]->setFont(font);
	labels[2]->setText(tr("shrink-expand")); 
	labels[2]->setFont(font);

	//ƽ������
	connect(_slider[0], SIGNAL(valueChanged(int)), this, SLOT(upDownTranslation(int))); //����ƽ��
	connect(_slider[1], SIGNAL(valueChanged(int)), this, SLOT(leftRightTranslation(int))); //����ƽ��
	connect(_expandBox, SIGNAL(activated(const QString &)), this, SLOT(shrinkExpandTranslation(const QString&)));//��С�任
	rightLayout->addLayout(translateShape);

	//���ò���
	QHBoxLayout* mainLayout = new QHBoxLayout;
	mainLayout->addLayout(leftLayout);
	rightLayout->setStretchFactor(chooseShape, 2);
	rightLayout->setStretchFactor(_controlShape, 4);
	rightLayout->setStretchFactor(translateShape, 3);

	mainLayout->addLayout(rightLayout);
	//���ñ��� 5:2
	mainLayout->setStretchFactor(leftLayout, 5);
	mainLayout->setStretchFactor(rightLayout, 2);
	centralWidget->setLayout(mainLayout);

	//��Ӳ˵�����������
	QAction* openAction = new QAction(tr("Open the file"), this);
	QMenu* file = menuBar()->addMenu(tr("File"));
	file->addAction(openAction);
	
	QToolBar* toolBar = addToolBar(tr("File"));
	toolBar->addAction(openAction);
	connect(openAction, SIGNAL(triggered()), this, SLOT(fillComboBox()));
}

void Project::upDownTranslation(int dy)
{
	_leftWindow->setY(dy);
	_leftWindow->update();
}

void Project::leftRightTranslation(int dx)
{
	_leftWindow->setX(dx);
	_leftWindow->update();
}

void Project::shrinkExpandTranslation(const QString& times)
{
	double expandTimes = times.toDouble();
	_leftWindow->setExpandTimes(expandTimes);	
	_leftWindow->update();
}

void Project::fillComboBox()
{
	QString path = QFileDialog::getOpenFileName(this, tr("Open"), "C:/Users/xuyang/Desktop", tr("XML files (*.xml)"));
	if (path.isEmpty())
	{
		QMessageBox::information(NULL, tr("Notice"), tr("You did't select any file"));
	}
	else
	{
		_filePath = path;
		QFile file(path);
		QDomDocument doc;
		QString error;
		int row = 0, column = 0;
		if (!doc.setContent(&file, false, &error, &row, &column))
		{
			QMessageBox::information(NULL, tr("Notice"), tr("file loading failure"));
			file.close();
			return;
		}
		file.close();

		if (doc.isNull())
		{
			QMessageBox::information(NULL, QString("Notice"), QString("document is null"));
			return;
		}
		//��ȡxml�ڵ�,ֻ��ȡͼ������,���������
		QDomElement rootElement = doc.documentElement(); 
		if (rootElement.tagName() != "presetShapeDefinitons")
		{
			QMessageBox::information(NULL, QString("Notice"), QString("document is invalid"));
			return;
		}
		_shapeNames.resize(0);
		QDomNodeList list = rootElement.childNodes();
		int count = list.count();
		for (int i = 0; i < count; i++)
		{
			QDomNode node = list.item(i);
			QDomElement nodeElement = node.toElement();
			QString nodeElementTagName = nodeElement.tagName();
			_shapeNames.push_back(nodeElementTagName);
		}
		if (!_shapeNames.isEmpty())
		{
			QMessageBox::information(NULL, QString("Notice"), QString("file loading success"));
			//���comboBox
			_comboBox->clear();
			_comboBox->addItem("   ");

			int sz = _shapeNames.size();
			for (int i = 0; i < sz; i++)
			{
				_comboBox->addItem(_shapeNames[i]);
			}
			//�ź�
			connect(_comboBox, SIGNAL(activated(const QString &)), this, SLOT(showShape(const QString &)));
		}
		else
		{
			QMessageBox::information(NULL, QString("Notice"), QString("file loading failure"));
			return;
		}
	}
}

void Project::showShape(const QString& name)
{
	ParseXml xmlFile(_filePath, name);
	_xmlStructure = xmlFile;
	QVector<ComplexPath> painterPaths = _xmlStructure.painterPath();
	int pathSize = painterPaths.size();

#if 0
	qDebug() << pathSize << endl;
#endif

	_leftWindow->setPainterPath(painterPaths);
	
	//����֮ǰ���пؼ�
	_csw->setAllWidgetsInvisible();
	//��ʾ·������(��ѡ��)
	_csw->setCheckBoxsVisible(pathSize);
	
	//ͼ�ο��ƿ���ʾ�ؼ�

	QVector<QPair<QString, double>> controlShapeArg = _xmlStructure.controlShapeArg();
	Range shapeArgRange = _xmlStructure.shapeArgRange(); //ÿ������adj��Χ
	int controlArgSize = controlShapeArg.size(); //����adj����

	for (int i = 0; i < controlArgSize; i++)
	{
		QString arg = controlShapeArg[i].first;
		double value = controlShapeArg[i].second;
		if (shapeArgRange._range.find(arg) != shapeArgRange._range.end())
		{
			double min = _xmlStructure.getValue(shapeArgRange._range[arg].first);
			double max =  _xmlStructure.getValue(shapeArgRange._range[arg].second);
			if (min <= value && value <= max)
				_csw->setOneWidgetVisible(arg, value, min, max);
		}
	}
	_leftWindow->update();
}

void Project::changeShape(const QString& adj, double val)
{
	//�ı���״ǰ�Ȱ�֮ǰ����״���
	_leftWindow->clearPainterPath();
	_leftWindow->update();

	//�ı����
	_xmlStructure.setControlShapeArg(adj, val);

#if 0
	int size = _xmlStructure.controlShapeArg().size();
	for (int i = 0; i < size; i++)
	{
		qDebug() << _xmlStructure.controlShapeArg()[i].first << ":"
			<< _xmlStructure.controlShapeArg()[i].second;
	}
	qDebug() << endl;
#endif

	// �Ѿ�����ͼ�β���ֵ,���½����õ��µ�·��
	_xmlStructure.parseXmlStructure();

	//���½���ʱ����뱣֤����·��ȫ����ʾ��
	_csw->setCheckBoxsVisible(_xmlStructure.painterPath().size());

	_leftWindow->setPainterPath(_xmlStructure.painterPath());
	_leftWindow->update();
}

void Project::showPath(int i, bool flag)
{
	_xmlStructure.setPathVisible(i, flag);
	_leftWindow->setPainterPath(_xmlStructure.painterPath());
	_leftWindow->update();
}