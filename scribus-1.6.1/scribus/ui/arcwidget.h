/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/
#ifndef ARCWIDGET_H
#define ARCWIDGET_H

#include <QWidget>
#include "scribusapi.h"
#include "ui_arcwidgetbase.h"

struct ItemToolPrefs;

class SCRIBUS_API ArcWidget : public QWidget, Ui::ArcWidgetBase
{
	Q_OBJECT

	public:
		ArcWidget(QWidget* parent);
		~ArcWidget() {};

		void restoreDefaults(const ItemToolPrefs *prefsData);
		void saveGuiToPrefs(ItemToolPrefs *prefsData);

	protected slots:
		void updatePreview();

	protected:
		void connectSignals(bool);
};

#endif
