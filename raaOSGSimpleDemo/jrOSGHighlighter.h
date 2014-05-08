#pragma once

#include <osg\Node>

class jrOSGHighlighter {
public:
	jrOSGHighlighter(void);
	virtual ~jrOSGHighlighter(void);

	virtual void highlight(osg::Node* node, const osg::Vec4 &colour);
	virtual void highlightRed(osg::Node* node);
	virtual void highlightGreen(osg::Node* node);


	virtual void unhighlight(osg::Node* node);
};
