#include <iostream>
#include <memory>

#include "OrangeEngineCore/Application.h"

class Game : public OrangeEngine::Application
{
	void onUpdate() override
	{

	}
};

int main(int argc, char** argv)
{
	auto game = std::make_unique<Game>();
	int returnCode = game->start(1024, 1024, "The coolest game ever!", argv);
	std::cin.get();
	return returnCode;
}