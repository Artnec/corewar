#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "unistd.h"
#include <dirent.h>
#include <sys/types.h>
#include <iomanip>

using namespace std;

int		find_diference(int cycle, string a, string b)
{
	stringstream	buffer;
	stringstream	buffer2;
	char			buf[512];

	sprintf(buf, "./orig_corewar -d %d %s %s > orig_dump", cycle, a.c_str(), b.c_str());
	system(buf);
	sprintf(buf, "./corewar -dump %d  %s %s > dump", cycle, a.c_str(), b.c_str());
	system(buf);
	ifstream		org("orig_dump");
	ifstream		my("dump");
	buffer << org.rdbuf();
	buffer2 << my.rdbuf();
	string s1 = buffer.str();
	string s2 = buffer2.str();
	int t = 0;

	for (int i = 0; i < s1.size(); ++i)
	{
		if (t == 0 && s1[i] != s2[i])
		{
			i = 0;
			t = 1;
		}
		if (t == 1)
		{
			if (s1[i] != s2[i])
				cout << "\033[1;31m";
			cout << s1[i];
			if (s1[i] != s2[i])
				cout << "\033[0m";
		}
	}
	system("rm -f dump orig_dump");
	return (t);
}

int		main(int argc, char **argv)
{
	if (argc != 3)
	{
		cout << "Usage:  " << argv[0] << "  directory  dump_cycle" << endl;
		return 0;
	}
	int					cycle = atoi(argv[2]);
	vector<string>		files;
	struct dirent		*entry;
	char				name[512];
	DIR					*dir;
	int					len = strlen(argv[1]) + 1;

	dir = opendir(argv[1]);
	if (dir == NULL)
	{
		cout << "Error: bad directory name\n" << endl;
		return (0);
	}
	while ((entry = readdir(dir)))
	{
		int len = strlen(entry->d_name);
		if (entry->d_name[0] == '.' || len < 5 || strcmp(entry->d_name + len - 4, ".cor"))
			continue ;
		files.push_back(argv[1] + string("/") + entry->d_name);
	}
	closedir(dir);
	for (auto n = files.begin(); n != files.end() - 1; ++n)
	{
		for(auto i = n + 1; i != files.end(); ++i)
		{
			string s1 = *n, s2 = *i;
			if (find_diference(cycle, *n, *i) == 1)
			{
				cout << left << setw(25) << setfill(' ') << s1.erase(0, len) << left <<
				setw(25) << setfill(' ') << s2.erase(0, len) << "  are diferent" << endl;
				exit(0);
			}
			cout << left << setw(25) << setfill(' ') << s1.erase(0, len) << left <<
			setw(25) << setfill(' ') << s2.erase(0, len) << "  are identical" << endl;

		}
	}
	return 0;
}
