// test-console.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "SFWExport.h"
#include <string.h>

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cerr << "Missing path" << std::endl;
		return 1;
	}

	auto monitor_path = argv[1];
	auto monitor_path_length = strlen(monitor_path);
	std::cout << "Monitoring Path: " << monitor_path << std::endl;

	auto native_interface = NativeInterface_Create(monitor_path);

	auto continueFlag = true;
	while (continueFlag)
	{
		auto const bufferSize = 2;
		auto buffer = new SFW_Event[bufferSize];

		int eventCount;
		NativeInterface_GetEvents(native_interface, &buffer, &eventCount);
		for (auto i = 0; i < eventCount; i++)
		{
			auto evt = buffer[i];
			switch (evt.type)
			{
			case CREATED:
				std::cout << "Created: ";
				break;

			case DELETED:
				std::cout << "Deleted: ";
				break;

			case MODIFIED:
				std::cout << "Modified: ";
				break;

			case RENAMED:
				std::cout << "Renamed: ";
				break;
			}

			auto event_directory_char = evt.directory;
			auto event_directory = std::string(event_directory_char, strlen(event_directory_char));
			auto base_directory = "." + event_directory.substr(monitor_path_length);

			std::cout << base_directory << "\\" << evt.fileA;
			if (evt.fileB)
			{
				std::cout << " -> " << base_directory << "\\" << evt.fileB;
			}
			std::cout << std::endl;
		}

		std::cout << "Press any key or 'q' to quit: ";
		auto inputChar = std::cin.get();
		if (inputChar == 'q' || inputChar == 'Q')
		{
			continueFlag = false;
		}
	}

	NativeInterface_Delete(native_interface);

	return 0;
}
