#include "GridButton.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPainter>

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
		backColor = "#491B1D";
	if (!defaultColorBlack && !m_Highlighted)
		backColor = "#D2C4B5";
	if (!defaultColorBlack && m_Highlighted)
		backColor = "#491B1D";

	if (m_Selected)
		backColor = "#491B1D";

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

void GridButton::paintEvent(QPaintEvent* event)
{
	QPushButton::paintEvent(event);
	QPainter painter(this);
	QColor penColor;
	QFont font = painter.font();

	font.setBold(true);
	painter.setFont(font);

	bool defaultColorBlack = (m_Position.first + m_Position.second) % 2;
	defaultColorBlack == true ? penColor = "#D2C4B5" : penColor = "#7A6C5D";

	int textX = 5;
	int textY = 5;

	painter.setRenderHint(QPainter::TextAntialiasing, true);
	painter.setPen(penColor);

	if (m_Position.first == 7)
	{
		painter.drawText(textX, textY, width() - 2 * textX, height() - 2 * textY, Qt::AlignBottom | Qt::AlignRight, QChar((char)'a' + m_Position.second));
	}
	if (m_Position.second == 0)
	{
		painter.drawText(textX, textY, width() - 2 * textX, height() - 2 * textY, Qt::AlignTop | Qt::AlignLeft, QString::number(8 - m_Position.first));
	}
}

GridButton::GridButton(const std::pair<int, int>& boardPosition, PieceType pieceType, PieceColor pieceColor, QWidget* parent)
	: m_Position(boardPosition), m_PieceType(pieceType), m_PieceColor(pieceColor), m_Highlighted(false), m_Selected(false)
{
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	updateBackgroundColor();

	updatePiece();
}