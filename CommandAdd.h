#pragma once

#ifndef D_COMMANDADD_H
#define D_COMMANDADD_H 1

#include "Command.h"
#include <memory>

#include "rectangle.h"
#include "rhombus.h"
#include "trapezoid.h"
#include "brokenLine.h"
#include "circle.h"
#include "polygon.h"
#include "Document.h"

struct CommandAdd : Command {


	int index__;
	Document * doc__ = new Document();

	CommandAdd(int index, Document * doc) : index__(index), doc__(doc) {}

	void undo() {
		(doc__ -> figures).erase((doc__ -> figures).begin() + index__);
	}
	
};

#endif