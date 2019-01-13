#pragma once

#ifdef _DEBUG
#define entry_point int main()
#else
#define entry_point int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
#endif
