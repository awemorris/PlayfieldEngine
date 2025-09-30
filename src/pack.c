/* -*- coding: utf-8; tab-width: 8; indent-tabs-mode: t; -*- */

/*
 * Copyright (c) 2025, Awe Morris. All rights reserved.
 */

int command_archive(int argc, char *argv[]);

#ifdef _WIN32
#include <windows.h>
#endif

int main(int argc, char *argv[])
{
#ifdef _WIN32
	if (argc == 1)
	{
		MessageBoxW(NULL,
			    L"Please drop files on this application to make an archive file.",
			    L"Playfield Engine Archiver",
			    MB_OK | MB_ICONINFORMATION);
		return 1;
	}
	else
	{
		MessageBoxW(NULL,
			    L"Playfield Archiver will make an archive file. This will take a while.",
			    L"Playfield Engine Archiver",
			    MB_OK | MB_ICONINFORMATION);
	}
#endif

	int ret = command_archive(argc, argv);

#ifdef _WIN32
	if (ret == 0)
	{
		MessageBoxW(NULL,
			    L"Done making the assets.pak file.",
			    L"Playfield Engine Archiver",
			    MB_OK | MB_ICONINFORMATION);
	}
	else
	{
		MessageBoxW(NULL,
			    L"Error(s) on making the assets.pak file. See the console.",
			    L"Playfield Engine Archiver",
			    MB_OK | MB_ICONINFORMATION);
	}
#endif

	return ret;
}
