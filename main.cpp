#include <Windows.h>
#include <iostream>
#include "memory.hpp"
#include "ifexist.hpp"

using namespace std;

Injector inj;

DWORD pid;

LPVOID ntOpenFile = GetProcAddress(LoadLibraryW(L"ntdll"), "NtOpenFile");

void bypass()
{

    int p = 21;
    int k = 45;
    int sw = 3;

    if (p > k)
    {
        system("cls");
        Sleep(1500);
        exit(0);
    }
    else
    {
        switch (sw)
        {
        case 3:
            int c = 135;
            int ca = 121;
            if (ca < c)
            {
                if (ntOpenFile) {
                    char originalBytes[5];
                    memcpy(originalBytes, ntOpenFile, 5);
                    WriteProcessMemory(inj.process, ntOpenFile, originalBytes, 5, NULL);
                }
                else
                {
                    cout << "Fatal error001!\n";
                    Sleep(1500);
                    exit(-1);
                }
            }
            break;
        }
    }
}

void Backup()
{
    int pw = 2;
    switch (pw)
    {
    case 2:
        if (ntOpenFile) {
            char originalBytes[5];
            memcpy(originalBytes, ntOpenFile, 5);
            WriteProcessMemory(inj.process, ntOpenFile, originalBytes, 0, NULL);
        }
        else
        {
            cout << "Fatal error002!\n";
            Sleep(2000);
            exit(-1);
        }
        break;
    }
}

void design()
{
	HANDLE console2 = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HWND console = GetConsoleWindow();
	RECT ConsoleRect;
	GetWindowRect(console, &ConsoleRect);
	MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 366, 184, TRUE);
	GetConsoleScreenBufferInfo(console2, &csbi);
	COORD scrollbar = {
		csbi.srWindow.Right - csbi.srWindow.Left + 1,
		csbi.srWindow.Bottom - csbi.srWindow.Top + 1
	};
	DeleteMenu(GetSystemMenu(GetConsoleWindow(), FALSE), SC_MAXIMIZE, MF_BYCOMMAND);
	SetConsoleScreenBufferSize(console2, scrollbar);
}

int main()
{
	int x = 22;
	int y = 11;

	if (x > y)
	{ 
	design();
	SetConsoleTitle("injector by kvetinka#2020");
	}
	int switcher = 1;
	int mainswitch;
	int select;

	switch (switcher)
	{
	case 1:
		system("color 0d");
		cout << "1. Continue to injection\n2. Exit\n3. How to use\n";
		cin >> mainswitch;

		if (mainswitch == 1)
		{
			system("cls");
			system("color 0d");
			cout << "1. csgo\n2. tf2\n";
			cin >> select;

			if (select == 1)
			{
				system("cls");
				inj.hwndproc = FindWindowA(0, "Counter-Strike: Global Offensive");


				GetWindowThreadProcessId(inj.hwndproc, &pid);
				inj.process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

				inj.clientDLL = inj.GetModule(pid, "client.dll");

				if (DoesFileExist("cdll.dll")) {
					bypass();

					if (inj.inject(pid, "cdll.dll")) {
						system("cls");
						system("color 0a");
						cout << "injection sucess!\n" << endl;
						Backup();
						Sleep(2000);
						return 0;
					}
					else
					{
						system("cls");
						system("color 0c");
						cout << "injection failed!\n" << endl;
						Backup();
						Sleep(2000);
						return 0;
					}
				}
				else
				{
					Sleep(1000);
					return 0;
				}

				return 0;			
			}
			else if (select == 2)
			{
				system("cls");
				inj.hwndproc = FindWindowA(0, "Team Fortress 2");


				GetWindowThreadProcessId(inj.hwndproc, &pid);
				inj.process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

				inj.clientDLL = inj.GetModule(pid, "client.dll");

				if (DoesFileExist("tdll.dll")) {
					bypass();

					if (inj.inject(pid, "tdll.dll")) {
						system("cls");
						system("color 0a");
						cout << "injection sucess!\n" << endl;
						Backup();
						Sleep(1500);
						return 0;
					}
					else
					{
						system("cls");
						system("color 0c");
						cout << "injection failed!\n" << endl;
						Backup();
						Sleep(1500);
						return 0;
					}

				}
				else
				{
					Sleep(1000);
					return 0;
				}
				return 0;
			}			
		}
		else if (mainswitch == 2)
		{
			return 0;
		}		
		else if (mainswitch == 3)
		{
			system("cls");
			int msgb;
				msgb = MessageBoxA(
				NULL,
				(LPCSTR)"1. Make sure the dll you want to inject is in the same folder as the injector\n2. If you want inject dll to csgo name dll as cdll, for tf2 tdll.\n3. Select function 1.\n4. Select game\n5. Enjoy!\nFor any bug report/questions about injector please contact me at discord (kvetinka#2020).\nInjector made by admin = kvetinka#2020",
				(LPCSTR)"how to use",
				MB_OK
			);
			main();
		}
		break;
	}
}
