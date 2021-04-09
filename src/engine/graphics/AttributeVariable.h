#pragma once
#ifndef ATTRIBUTEVARIABLE_H_
#define ATTRIBUTEVARIABLE_H_

namespace LittleEngine 
{
	struct AttributeVariable
	{
		int			 id;
		unsigned int count;
		unsigned int offset;
		unsigned int stride;

		AttributeVariable()													: id(0),  count(0),     offset(0), stride(0)	{}
		AttributeVariable(int id, unsigned int count, unsigned int stride)	: id(id), count(count), offset(0), stride(stride)	{};
	};
}

#endif
