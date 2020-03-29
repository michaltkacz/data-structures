#pragma once
#include "menu_type.h"

class text_user_interface
{
public:

	void print() const;
	bool program_runs() const;

private:
	bool program_runs_ = true;


};
