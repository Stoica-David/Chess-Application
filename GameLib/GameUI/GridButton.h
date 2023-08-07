#pragma once

#include "Enums.h"
#include "Position.h"

#include <QPushButton>

class GridButton : public QPushButton
{
	Q_OBJECT

public:
	GridButton(Position boardPosition, PieceType pieceType = PieceType::none, PieceColor pieceColor = PieceColor::none);

	void updatePiece();
	void updateBackgroundColor();

	void setPiece(std::pair<PieceType, PieceColor> newPiece);
	void setHighlighted(bool highlighted);
	void setSelected(bool selected);

signals:
	void Clicked(const std::pair<int, int>& position);

private:
	void paintEvent(QPaintEvent* event) override;

	void mouseReleaseEvent(QMouseEvent* event) override;

private:
	Position m_Position;
	
	PieceType m_PieceType;
	PieceColor m_PieceColor;
	
	bool m_Highlighted;
	bool m_Selected;
};
