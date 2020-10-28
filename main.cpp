#include <iostream>
#include "memory.hpp"
#include "ifexist.hpp"
Injector inj;
DWORD pid;
LPVOID ntOpenFile = GetProcAddress(LoadLibraryW(L"ntdll"), "NtOpenFile");

void bypass()
{
	if (ntOpenFile) {
		char originalBytes[5];
		memcpy(originalBytes, ntOpenFile, 5);
		WriteProcessMemory(inj.process, ntOpenFile, originalBytes, 5, NULL);
	}
	else
	{
		std::cout << "Unable to bypass :(\n";
		Sleep(2000);
		exit(-1);
	}
}

void Backup()
{
	if (ntOpenFile) {
		char originalBytes[5];
		memcpy(originalBytes, ntOpenFile, 5);
		WriteProcessMemory(inj.process, ntOpenFile, originalBytes, 0, NULL);
	}
	else
	{
		std::cout << "Unable to backup :(\n";
		Sleep(2000);
		exit(-1);
	}
}

int oth()
{
    int s{};
	system("cls"); system("color D");	int t{};   std::cout << "1) Continue to injection\n2) Exit\n3) How to use\n command: "; std::cin >> t;

	system("cls"); switch (t)
	{
	case 1:
		std::cout << "1) csgo\n2) tf2\n command: "; std::cin >> s;

		if (s == 1)
		{

			inj.hwndproc = FindWindowA(0, "Counter-Strike: Global Offensive");


			GetWindowThreadProcessId(inj.hwndproc, &pid);
			inj.process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

			inj.clientDLL = inj.GetModule(pid, "client_panorama.dll");

			if (DoesFileExist("cs.dll")) {
				bypass();

				if (inj.inject(pid, "cs.dll")) {
					std::cout << "\ninjected" << std::endl;
					Backup(); Sleep(1500); return 0;
				}
				else
				{
					std::cout << "\ninjection failed" << std::endl; Backup(); Sleep(2000); return 0;
				}

			}
			else
			{
				std::cout << "\ncannot find dll";
				Sleep(1500); oth();
			}
		
		}
		else if (s == 2)
		{
			inj.hwndproc = FindWindowA(0, "Team Fortress 2");

			GetWindowThreadProcessId(inj.hwndproc, &pid);
			inj.process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

			inj.clientDLL = inj.GetModule(pid, "client.dll");

			if (DoesFileExist("tf.dll")) {
				bypass();

				if (inj.inject(pid, "tf.dll")) {
					std::cout << "\ninjected" << std::endl;
					Backup(); Sleep(1500); return 0;
				}
				else
				{
					std::cout << "\ninjection failed" << std::endl; Backup(); Sleep(2000); return 0;
				}

			}
			else
			{
				std::cout << "\ncannot find dll";
				Sleep(1500); oth();
			}
		}
		else
		{
			std::cout << "unknown command"; Sleep(1500); oth();
		}

		break;

	case 2:		return 0;		break;

	case 3:
		MessageBoxA(NULL, (LPCSTR)"1. Make sure the dll you want to inject is in the same folder as the injector\n2. If you want inject dll to csgo name the dll as *cs*, for tf2 *tf*.\n3. Select function 1.\n4. Select game\n5. Enjoy!\nFor any bug report/questions about injector please contact me at discord (kvetinka#2020).\nInjector made by admin = kvetinka#2020", (LPCSTR)"help", MB_OK); Sleep(100); oth();
		break;

	default:
		std::cout << "unknown command"; Sleep(1500); oth();
		break;
	}
	s,t = 0;
}

int main()
{
	SetConsoleTitleA("injector by kvetinka#9031"); oth();
}
