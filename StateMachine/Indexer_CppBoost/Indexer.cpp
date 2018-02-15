#include <iostream>
#include <boost/filesystem.hpp>
#include "Indexer.h"

/*
** This class uses boost library for file system operations
** This library is choosen because it supports cross-platforms support and compatibility with C++ 11 standards
** 
*/

Indexer::Indexer()
{

}

Indexer::~Indexer()
{
	mdir.clear();
}
/*
** This method will list the files of give type (extension)
** It will iterate through the path vector and prints the files matching the given extension type
*/
void Indexer::listFiles(const string& type)
{
	try
	{
		for (vec::const_iterator it(mdir.begin()); it != mdir.end(); ++it)
		{
			if (it->extension() == "." + type)
				cout << "Dir:: " << it->branch_path() << " File:: " << it->filename() << "  Size:: " << it->size() << '\n';
		}
	}
	catch (fs::filesystem_error e)
	{
		cout << "FileSystem Exception occured from Boost lib : " << e.what() << endl;
	}
	catch (exception e)
	{
		cout << "Exception occured: " << e.what() << endl;
	}

}

/*
** This method will iterate through the directory using recursive_directory_iterator
** Then it will store all the paths in a path vector named files
** Please not that, Windows 7 x64, Win32 binary built with Visual Studio 2010, Recursive iteration fails 
** when iterating a directory that contains a child directory for which the user does not have permission to access 
** (Ref: https://svn.boost.org/trac/boost/ticket/6821)
*/
void Indexer::processDirectory(const string& drive)
{
	try
	{
		for (fs::recursive_directory_iterator dir_end, dir(drive); dir != dir_end; ++dir)
		{
			fs::path _path(*dir);

			if (!fs::is_directory(_path))
			{
				mdir.push_back(_path);
			}
			else
			{
				cout << "Checking" << endl;
			}

		}
	}
	catch (fs::filesystem_error e)
	{
		cout << e.what() << endl;
	}
	catch (exception e)
	{
		cout << "Exception occured in processDirectory: " << e.what() << endl;
	}
}


int main(int argc, char* argv[])
{
	Indexer ix;

	ix.processDirectory("E:\\Softwares\\Engineering\\C++");
	ix.listFiles("exe");


	return 0;
}