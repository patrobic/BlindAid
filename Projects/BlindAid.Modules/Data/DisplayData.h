#pragma once

#include "IData.h"

namespace Display
{
	class DisplayData : public IData
	{
	public:
		void Clear() {}
		bool Valid()
		{
			return true;
		}

	private:

	};
}