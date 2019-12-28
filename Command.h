#pragma once

#ifndef D_COMMAND_H
#define D_COMMAND_H 1

struct Command {

	virtual ~Command() = default;

	virtual void undo() = 0;

};

#endif