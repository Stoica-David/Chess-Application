#include "TitleBar.h"
#include "GridButton.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QMouseEvent>

TitleBar::TitleBar(QWidget* parent) : QWidget(parent)
{
	m_mousePressed = false;
	createLayout();

	// Set the title bar's background color and size
	setStyleSheet("background-color: #000; height: 30px;");

	//QWidget::window()->setProperty("windowTitleBarColor", QColor(139, 69, 19));
}

void TitleBar::createLayout()
{
	// Create the buttons
	QPushButton* minimizeButton = new QPushButton("-");
	QPushButton* closeButton = new QPushButton("X");

	// Set button styles
	minimizeButton->setObjectName("minimizeButton");
	closeButton->setObjectName("closeButton");

	// Set the fixed height for buttons (same as title bar height)
	minimizeButton->setFixedHeight(40);
	closeButton->setFixedHeight(40);
	minimizeButton->setFixedWidth(40);
	closeButton->setFixedWidth(40);

	minimizeButton->setStyleSheet("margin: 0;");
    closeButton->setStyleSheet("margin: 0;");

	// Connect button signals to slots
	connect(minimizeButton, &QPushButton::clicked, this, &TitleBar::minimizeButtonClicked);
	connect(closeButton, &QPushButton::clicked, this, &TitleBar::closeButtonClicked);

	// Create the right layout for pushing buttons to the right
	QHBoxLayout* rightLayout = new QHBoxLayout;
	rightLayout->addWidget(minimizeButton);
	rightLayout->addWidget(closeButton);
	rightLayout->setSpacing(5);
	rightLayout->setContentsMargins(0, 0, 0, 0); // Add margin on the right

	// Create the main layout
	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	mainLayout->setSpacing(5);
	mainLayout->setContentsMargins(0, 0, 0, 0);
	mainLayout->addStretch();
	mainLayout->addLayout(rightLayout);
	setLayout(mainLayout);

	// Apply styles to the buttons
	setStyleSheet(
		"QPushButton#minimizeButton, QPushButton#closeButton {"
		"   color: white;"
		"   background-color: black;"
		"   border: none;"
		"   font-size: 16px;"
		"   padding: 0px;"
		"   outline: none;"
		"}"
		"QPushButton#minimizeButton:hover, QPushButton#closeButton:hover {"
		"   background-color: #555;"
		"}"
		"QPushButton#minimizeButton:pressed, QPushButton#closeButton:pressed {"
		"   background-color: #222;"
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
	if (m_mousePressed)
	{
		this->parentWidget()->move(event->globalPos() - m_lastMousePos);
	}
}
