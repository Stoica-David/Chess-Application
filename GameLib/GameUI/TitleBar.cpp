#include "TitleBar.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QMouseEvent>

TitleBar::TitleBar(QWidget* parent) : QWidget(parent)
{
	createLayout();
}

void TitleBar::createLayout()
{
	// Create the buttons
	QPushButton* minimizeButton = new QPushButton("-");
	QPushButton* closeButton = new QPushButton("X");

	// Set button styles
	minimizeButton->setObjectName("minimizeButton");
	closeButton->setObjectName("closeButton");

	// Connect button signals to slots
	connect(minimizeButton, &QPushButton::clicked, this, &TitleBar::minimizeButtonClicked);
	connect(closeButton, &QPushButton::clicked, this, &TitleBar::closeButtonClicked);

	// Create the layout
	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->addWidget(minimizeButton);
	layout->addWidget(closeButton);
	layout->setContentsMargins(0, 0, 0, 0);
	setLayout(layout);

	// Apply styles to the buttons
	setStyleSheet(
		"QPushButton#minimizeButton, QPushButton#closeButton {"
		"   color: white;"
		"   background-color: #000;"
		"   border: none;"
		"   font-size: 16px;"
		"   padding: 5px;"
		"   outline: none;"
		"	align: right;"
		"}"
		"QPushButton#minimizeButton:hover, QPushButton#closeButton:hover {"
		"   background-color: #000;"
		"}"
	);
}

void TitleBar::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_mousePressed = true;
		m_lastMousePos = event->globalPos() - this->parentWidget()->geometry().topLeft();
	}
}

void TitleBar::mouseMoveEvent(QMouseEvent* event)
{
	if (event->buttons() & Qt::LeftButton)
	{
		QPoint diff = event->globalPos() - m_lastPos;
		parentWidget()->move(parentWidget()->x() + diff.x(), parentWidget()->y() + diff.y());
		m_lastPos = event->globalPos();
	}
}
