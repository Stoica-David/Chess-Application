#include "TitleBar.h"

TitleBar::TitleBar(QWidget* parent) : QWidget(parent)
{
	m_mousePressed = false;
	createLayout();

	// Set the title bar's background color and size
	setStyleSheet("background-color: #964B00; height: 30px;");
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

	// Create the left layout for dragging
	QHBoxLayout* leftLayout = new QHBoxLayout;
	leftLayout->addWidget(minimizeButton);
	leftLayout->addWidget(closeButton);

	// Create the right layout for pushing buttons to the right
	QHBoxLayout* rightLayout = new QHBoxLayout;
	rightLayout->addStretch();
	rightLayout->addLayout(leftLayout);
	rightLayout->setSpacing(0);
	rightLayout->setContentsMargins(0, 0, 10, 0); // Add margin on the right

	// Create the main layout
	QHBoxLayout* mainLayout = new QHBoxLayout(this);
	mainLayout->setSpacing(0);
	mainLayout->setContentsMargins(0, 0, 0, 0);
	mainLayout->addLayout(rightLayout);
	setLayout(mainLayout);

	// Apply styles to the buttons
	setStyleSheet(
		"QPushButton#minimizeButton, QPushButton#closeButton {"
		"   color: white;"
		"   background-color: transparent;"
		"   border: none;"
		"   font-size: 16px;"
		"   padding: 5px;"
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
