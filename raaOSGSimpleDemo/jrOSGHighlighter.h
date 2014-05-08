#pragma once

#include <osg\Node>

class jrOSGHighlighter {
public:
	jrOSGHighlighter(void);
	virtual ~jrOSGHighlighter(void);

	virtual void highlight(osg::Node* node, const std::string &name, const osg::Vec4 &colour);
	virtual void highlightRed(osg::Node* node, const std::string &name);
	virtual void highlightGreen(osg::Node* node, const std::string &name);


	virtual void unhighlight(osg::Node* node);
};
