#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>

class TitleBar : public QWidget
{
	Q_OBJECT

public:
	explicit TitleBar(QWidget* parent = nullptr);

signals:
	void minimizeButtonClicked();
	void closeButtonClicked();

protected:
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;

private:
	void createLayout();

	QPoint m_lastPos;
};

#endif // TITLEBAR_H
