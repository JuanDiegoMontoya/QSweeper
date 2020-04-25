#pragma once
#include "Mine.h"
#include "MineOptions.h"

class MineFactory
{
public:
	// User controlled mine type
	template<class MineType, typename ... Ts>
	typename std::enable_if<std::is_base_of<Mine, MineType>::value, std::unique_ptr<Mine>>::type
	MakeMine(Ts ... args)
	{
		return std::make_unique<MineType>(args...);
	}

	template<class MineType>
	typename std::enable_if<std::is_base_of<Mine, MineType>::value, std::unique_ptr<Mine>>::type
	MakeMine()
	{
		static_assert(0);
		return std::make_unique<MineType>(mineOptions);
	}

	std::unique_ptr<Mine> test1()
	{
		return MakeMine<SimpleMine>(glm::vec2(0), 1.2f);
	}

	std::unique_ptr<Mine> test2()
	{
		return MakeMine<SimpleMine>();
	}

private:
	MineOptions mineOptions;
};