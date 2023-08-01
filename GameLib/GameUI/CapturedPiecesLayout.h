#pragma once

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QGridLayout>
#include <vector>

class CapturedPiecesLayout : public QWidget
{
public:
	CapturedPiecesLayout(QWidget* parent = nullptr);

	void addWhitePiece(const QPixmap& pixmap);

	void addBlackPiece(const QPixmap& pixmap);

private:
	QGridLayout* layout;
	QHBoxLayout* whiteLayout;
	QHBoxLayout* blackLayout;
};

