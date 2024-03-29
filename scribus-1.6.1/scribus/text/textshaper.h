#ifndef TEXTSHAPER_H
#define TEXTSHAPER_H

#include <QList>
#include <QMap>
#include <QString>
#include <QStringList>

#include <unicode/uscript.h>

#include "itextsource.h"
#include "itextcontext.h"
#include "shapedtext.h"

class GlyphCluster;
class StoryText;
class PageItem;

using namespace icu;

class TextShaper
{
public:
	TextShaper(ITextContext* context, ITextSource& story, int firstChar, bool singlePar = false);
	TextShaper(ITextSource &story, int firstChar);

	ShapedText shape(int fromPos, int toPos);

private:
	struct TextRun {
		TextRun(int s, int l, int d)
			: start(s), len(l), dir(d), script(USCRIPT_INVALID_CODE)
		{ }

		TextRun(int s, int l, int d, UScriptCode sc)
			: start(s), len(l), dir(d), script(sc)
		{ }

		int start;
		int len;
		int dir;
		UScriptCode script;
	};

	struct FeaturesRun {
		FeaturesRun(int s, int l, QStringList f)
			: start(s), len(l), features(f)
		{
		}

		int start;
		int len;
		QStringList features;
	};

	void buildText(int fromPos, int toPos, QVector<int>& smallCaps);

	QList<TextRun> itemizeBiDi(int fromPos) const;
	QList<TextRun> itemizeScripts(const QList<TextRun> &runs) const;
	QList<TextRun> itemizeStyles(const QList<TextRun> &runs) const;
	QList<FeaturesRun> itemizeFeatures(const TextRun &run) const;

	ITextContext* m_context { nullptr };
	bool m_contextNeeded { false };
	ITextSource& m_story;
	int m_firstChar { 0 };
	bool m_singlePar { false };
	QString m_text;
	QMap<int, int> m_textMap;
};

#endif // TEXTSHAPER_H
