#pragma once
#include <stdio.h>
using namespace std;
namespace fs = boost::filesystem;

typedef vector<fs::path> vec;


class Indexer
{
public:
	Indexer();
	~Indexer();

	void processDirectory(const string& drive);
	void listFiles(const string& type);

private:
	vec mdir;

};