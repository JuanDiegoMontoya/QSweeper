#pragma once
#include "Mine.h"

class MineFactory
{
public:
	struct MineSettings
	{
		
	};

	template<class MineType, typename ... Ts>
	std::unique_ptr<Mine> MakeMine(Ts ... args)
	{
		static_assert(std::is_base_of<Mine, MineType>);
		return make_unique<MineType>(args);
	}

	std::unique_ptr<Mine> asd()
	{
		return MakeMine<Mine, glm::vec2, float>(glm::vec2(0), 1.2f);
	}

private:

};