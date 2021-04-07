#pragma once
#ifndef ATTRIBUTEVARIABLE_H_
#define ATTRIBUTEVARIABLE_H_

namespace LittleEngine 
{
	struct AttributeVariable
	{
		unsigned int id;
		unsigned int count;
		unsigned int offset;

		AttributeVariable()										: id(0),  count(0),     offset(0)	{}
		AttributeVariable(unsigned int id, unsigned int count)	: id(id), count(count), offset(0)	{};
	};
}

#endif
