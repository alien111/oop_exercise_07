#pragma once

#ifndef D_COMMANDREMOVE_H
#define D_COMMANDREMOVE_H 1

#include "Command.h"
#include <memory>

#include "rectangle.h"
#include "rhombus.h"
#include "trapezoid.h"
#include "brokenLine.h"
#include "circle.h"
#include "polygon.h"
#include "Document.h"

struct CommandRemove : Command {

	Document * doc__;

	int index__;
	std::unique_ptr<figure> figure__;

	CommandRemove(int index, std::unique_ptr<figure> figure_, Document * doc) : index__(index), figure__(figure_), doc__(doc) {}

	void undo() {
		if (index__ > (doc__ -> figures).size() - 1) 
			(doc__ -> figures).push_back(std::move(figure__));
		else 
			(doc__ -> figures).insert((doc__ -> figures).begin() + index__, std::move(figure__));
	}
	
};

#endif