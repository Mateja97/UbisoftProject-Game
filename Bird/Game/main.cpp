#include "precomp.h"
#include "Application.h"


int main(int argc, char* argv[]) {

	auto app = Game::CreateApplication();
	bool success = app->Init();

	if (!success) {
		std::cerr << "App failed to initialize!";
		return 1;
	}

	app->Run();
	bool success2 = app->Shutdown();

	if (!success2) {
		std::cerr << "App failed to shutdown correctly";
		return 1;
	}
	delete app;
	return 0;
}