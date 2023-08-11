#include "GridButton.h"

#include "Position.h"

#include <QPainter>

void GridButton::UpdatePiece()
{
	std::string imagePath = ":/Images/res/";

	switch (m_pieceColor)
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

	switch (m_pieceType)
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
	setIconSize(pixmap.rect().size() * 0.8);
}

void GridButton::UpdateBackgroundColor()
{
	bool defaultColorBlack = (m_position.x + m_position.y) % 2;
	QString backColor = "";

	if (defaultColorBlack && !m_highlighted)
		backColor = "#7A6C5D";
	if (defaultColorBlack && m_highlighted)
		backColor = "#E2DE84";
	if (!defaultColorBlack && !m_highlighted)
		backColor = "#D2C4B5";
	if (!defaultColorBlack && m_highlighted)
		backColor = "#E2DE84";

	if (m_selected)
		backColor = "#E2DE84";

	setStyleSheet("background-color: " + backColor + "; border: none;");
}

void GridButton::SetPiece(std::pair<PieceType, PieceColor> newPiece)
{
	m_pieceType = newPiece.first;
	m_pieceColor = newPiece.second;

	UpdatePiece();
}

void GridButton::SetHighlighted(bool highlighted)
{
	m_highlighted = highlighted;
	UpdateBackgroundColor();
}

void GridButton::SetSelected(bool selected)
{
	m_selected = selected;
	UpdateBackgroundColor();
}

void GridButton::paintEvent(QPaintEvent* event)
{
	QPushButton::paintEvent(event);
	QPainter painter(this);
	QColor penColor;
	QFont font = painter.font();

	font.setBold(true);
	painter.setFont(font);

	bool defaultColorBlack = (m_position.x + m_position.y) % 2;
	defaultColorBlack == true ? penColor = "#D2C4B5" : penColor = "#7A6C5D";

	int textX = 2;
	int textY = 2;

	painter.setRenderHint(QPainter::TextAntialiasing, true);
	painter.setPen(penColor);

	if (m_position.x == 7)
	{
		painter.drawText(textX, textY, width() - 2 * textX, height() - 2 * textY, Qt::AlignBottom | Qt::AlignRight, QChar((char)'a' + m_position.y));
	}
	if (m_position.y == 0)
	{
		painter.drawText(textX, textY, width() - 2 * textX, height() - 2 * textY, Qt::AlignTop | Qt::AlignLeft, QString::number(8 - m_position.x));
	}
}

GridButton::GridButton(Position boardPosition, PieceType pieceType, PieceColor pieceColor)
	: m_position(boardPosition)
	, m_pieceType(pieceType)
	, m_pieceColor(pieceColor)
	, m_highlighted(false)
	, m_selected(false)
{
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	UpdateBackgroundColor();

	UpdatePiece();
}

void GridButton::mouseReleaseEvent(QMouseEvent* event)
{
	QPushButton::mouseReleaseEvent(event);
	emit(Clicked(m_position));
}