#pragma once

#include "Enums.h"
#include "Position.h"

#include <QPushButton>

class GridButton : public QPushButton
{
	Q_OBJECT

public:
	GridButton(Position boardPosition, PieceType pieceType = PieceType::none, PieceColor pieceColor = PieceColor::none);

	void UpdatePiece();
	void UpdateBackgroundColor();

	void SetPiece(std::pair<PieceType, PieceColor> newPiece);
	void SetHighlighted(bool highlighted);
	void SetSelected(bool selected);

signals:
	void Clicked(const Position& position);

private:
	void paintEvent(QPaintEvent* event) override;

	void mouseReleaseEvent(QMouseEvent* event) override;

private:
	Position m_position;
	
	PieceType m_pieceType;
	PieceColor m_pieceColor;
	
	bool m_highlighted;
	bool m_selected;
};
