#include "GridButton.h"
#include <QVBoxLayout>
#include <QLabel>

void GridButton::mouseReleaseEvent(QMouseEvent* event)
{
	QPushButton::mouseReleaseEvent(event);
	emit(Clicked(m_Position));
}

void GridButton::updatePiece()
{
	std::string imagePath = "res/";

	switch (m_PieceColor)
	{
	case PieceColor::none:
		imagePath += "empty";
		break;
	case PieceColor::Black:
		imagePath += "b";
		break;
	case PieceColor::White:
		imagePath += "w";
		break;
	}

	switch (m_PieceType)
	{
	case PieceType::none:
		break;
	case PieceType::King:
		imagePath += "k";
		break;
	case PieceType::Rook:
		imagePath += "r";
		break;
	case PieceType::Bishop:
		imagePath += "b";
		break;
	case PieceType::Queen:
		imagePath += "q";
		break;
	case PieceType::Knight:
		imagePath += "h";
		break;
	case PieceType::Pawn:
		imagePath += "p";
		break;
	default:
		break;
	}

	imagePath += ".png";

	QPixmap pixmap(QString::fromStdString(imagePath));
	QIcon ButtonIcon(pixmap);
	setIcon(ButtonIcon);
	setIconSize(pixmap.rect().size());
}

void GridButton::updateBackgroundColor()
{
	bool defaultColorBlack = (m_Position.first + m_Position.second) % 2;
	QString backColor = "";

	if (defaultColorBlack && !m_Highlighted)
		backColor = "#7A6C5D";
	if (defaultColorBlack && m_Highlighted)
		backColor = "#C17C74";
	if (!defaultColorBlack && !m_Highlighted)
		backColor = "#DDC9B4";
	if (!defaultColorBlack && m_Highlighted)
		backColor = "#C17C74";

	if (m_Selected)
		backColor = "#2A3D45";

	setStyleSheet("background-color: " + backColor + "; border: none;");
}

void GridButton::setPiece(std::pair<PieceType, PieceColor> newPiece)
{
	m_PieceType = newPiece.first;
	m_PieceColor = newPiece.second;

	updatePiece();
}

void GridButton::setHighlighted(bool highlighted)
{
	m_Highlighted = highlighted;
	updateBackgroundColor();
}

void GridButton::setSelected(bool selected)
{
	m_Selected = selected;
	updateBackgroundColor();
}

GridButton::GridButton(const std::pair<int, int>& boardPosition, PieceType pieceType, PieceColor pieceColor, QWidget* parent)
	: m_Position(boardPosition), m_PieceType(pieceType), m_PieceColor(pieceColor), m_Highlighted(false), m_Selected(false)
{
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	updateBackgroundColor();

	updatePiece();

	int row = m_Position.first + 1;
	int col = m_Position.second + 1;

	QLabel* topLabel = new QLabel;
	topLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
	topLabel->setStyleSheet("background-color: rgba(0, 0, 0, 0);");

	QLabel* bottomLabel = new QLabel;
	bottomLabel->setAlignment(Qt::AlignBottom | Qt::AlignRight);
	bottomLabel->setStyleSheet("background-color: rgba(0, 0, 0, 0);");

	if (m_Position.first == 7 && m_Position.second == 0) {
		QString topTileNumber = QString::number(row);
		QString bottomTileNumber = QChar('A' + col - 1);
		topLabel->setText(topTileNumber);
		bottomLabel->setText(bottomTileNumber);
	}
	else if (m_Position.second == 0) {
		topLabel->setText(QString::number(row));
	}
	else if (m_Position.first == 7) {
		bottomLabel->setText(QChar('A' + col - 1));
	}

	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->addWidget(topLabel);
	layout->addWidget(this); 
	layout->addWidget(bottomLabel);
	layout->setContentsMargins(0, 0, 0, 0); 
	layout->setSpacing(0); 

	setLayout(layout);
}