#include "Application/Application.hpp"

#ifdef DEBUG
int main()
#else
#include <Windows.h>
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PWSTR pCmdLine, _In_ int nCmdShow)
#endif // !NDEBUG
{
	Application app;
	app.run();
	return 0;
}