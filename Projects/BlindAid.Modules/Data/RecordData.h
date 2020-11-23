#pragma once

#include "IData.h"

namespace Record
{
	class RecordData : public IData
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