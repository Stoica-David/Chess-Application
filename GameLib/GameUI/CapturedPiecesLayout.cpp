#include "CapturedPiecesLayout.h"

CapturedPiecesLayout::CapturedPiecesLayout(QWidget* parent /*= nullptr*/) : QWidget(parent)
{
	layout = new QGridLayout(this);
	layout->setSpacing(2);

	whiteLayout = new QHBoxLayout();
	blackLayout = new QHBoxLayout();

	layout->addLayout(whiteLayout, 0, 0);
	layout->addLayout(blackLayout, 1, 0);
}

void CapturedPiecesLayout::addWhitePiece(const QPixmap& pixmap)
{
	QLabel* pieceLabel = new QLabel(this);
	pieceLabel->setPixmap(pixmap);
	whiteLayout->addWidget(pieceLabel);
}

void CapturedPiecesLayout::addBlackPiece(const QPixmap& pixmap)
{
	QLabel* pieceLabel = new QLabel(this);
	pieceLabel->setPixmap(pixmap);
	blackLayout->addWidget(pieceLabel);
}
