#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "Memory.h"

using namespace std;

char *GAME_TITLE = "FortniteClient-Win64-Shipping_EAC.exe";

void force_load()
{
	LoadLibrary("sechost.dll");
	LoadLibrary("user32.dll");

	Memory *memory = new Memory();
	HANDLE hProcess;
	DWORD PID;

	PID = memory->GetProcessByName(GAME_TITLE);
	hProcess = OpenProcess(
		PROCESS_ALL_ACCESS,
		FALSE,
		PID);

	DWORD EAC_x86_a = memory->GetModuleBase32("EasyAntiCheat_x64.dll", memory->GetProcessByName(GAME_TITLE));

		

	WriteProcessMemory(hProcess, (LPVOID)(EAC_x86_a + 0x1A21C), "\xEB\x15", 2, NULL);//26840
	WriteProcessMemory(hProcess, (LPVOID)(EAC_x86_a + 0x18FB0), "\x90\x90", 2, NULL);//


	DWORD EXIT_PROCESS = (DWORD)&ExitProcess;
	DWORD calc = 0;
	BYTE call[5];

	calc = EXIT_PROCESS - (EAC_x86_a + 0x1A237) - 5;

	call[0] = 0xE8;
	memcpy(&call[1], &calc, 4);
	WriteProcessMemory(hProcess, (LPVOID)(EAC_x86_a + 0x1A237), call, 5, NULL);

}


int main()
{
	Memory *memory = new Memory();
	printf("Waiting for FortniteClient-Win64-Shipping_EAC.exe\n");
	for (;;)
	{
		if (memory->GetProcessByName(GAME_TITLE) > 0)
		{
			printf("1");
			if (memory->GetModuleBase32("EasyAntiCheat_x86.dll", memory->GetProcessByName(GAME_TITLE)) != 0)
			{
				printf("2");
				break;
			}
				
		}

		Sleep(100);
	}
	Sleep(50);
	force_load();

	return 0;
}
