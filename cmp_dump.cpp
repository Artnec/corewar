#include <iostream>
#include <vector>
#include "unistd.h"
#include <dirent.h>
#include <sys/types.h>

using namespace std;

int		find_diference(char *comand1, char *comand2)
{
	char			output1[32768] = {0};
	char			output2[32768] = {0};
	FILE			*fp1 = popen(comand1, "r");
	FILE			*fp2 = popen(comand2, "r");

	int size = fread(output1, 1, 32768, fp1);
	pclose(fp1);
	fread(output2, 1, 32768, fp2);
	pclose(fp2);
	int t = 0;
	for (int i = 0; i < size; ++i)
	{
		if (t == 0 && output1[i] != output2[i])
		{
			i = 0;
			t = 1;
		}
		if (t == 1)
		{
			if (output1[i] != output2[i])
				printf("\033[1;31m");
			printf("%c", output1[i]);
			if (output1[i] != output2[i])
				printf("\033[0m");
		}
	}
	return (t);
}

int		comapare_one_bot(int cycle, string a)
{
	char			buf[512];
	char			buf2[512];

	sprintf(buf, "./orig_corewar -d %d %s", cycle, a.c_str());
	sprintf(buf2, "./corewar -dump %d %s", cycle, a.c_str());
	return (find_diference(buf, buf2));
}

int		comapare_two_bots(int cycle, string a, string b)
{
	char			buf[512];
	char			buf2[512];

	sprintf(buf, "./orig_corewar -d %d %s %s", cycle, a.c_str(), b.c_str());
	sprintf(buf2, "./corewar -dump %d %s %s", cycle, a.c_str(), b.c_str());
	return (find_diference(buf, buf2));
}

int		comapare_three_bots(int cycle, string a, string b, string c)
{
	char			buf[512];
	char			buf2[512];

	sprintf(buf, "./orig_corewar -d %d %s %s %s", cycle, a.c_str(), b.c_str(), c.c_str());
	sprintf(buf2, "./corewar -dump %d %s %s %s", cycle, a.c_str(), b.c_str(), c.c_str());
	return (find_diference(buf, buf2));
}

int		comapare_four_bots(int cycle, string a, string b, string c, string d)
{
	char			buf[512];
	char			buf2[512];

	sprintf(buf, "./orig_corewar -d %d %s %s %s %s", cycle, a.c_str(), b.c_str(), c.c_str(), d.c_str());
	sprintf(buf2, "./corewar -dump %d %s %s %s %s", cycle, a.c_str(), b.c_str(), c.c_str(), d.c_str());
	return (find_diference(buf, buf2));
}

int		main(int argc, char **argv)
{
	int					bots_num;
	if (argc != 4 || (bots_num = atoi(argv[2])) < 1 || bots_num > 4)
	{
		printf("Usage:  %s  directory  bots_num[1-4]  dump_cycle\n", argv[0]);
		return 0;
	}
	int					cycle = atoi(argv[3]);
	vector<string>		files;
	struct dirent		*entry;
	char				name[512];
	DIR					*dir;
	int					len = strlen(argv[1]) + 1;

	dir = opendir(argv[1]);
	if (dir == NULL)
	{
		printf("Error: bad directory name\n");
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
	for (auto n = files.begin(); n != files.end(); ++n)
	{
		string s1 = *n;
		const char *cs1 = s1.erase(0, len).c_str();
		if (bots_num == 1)
		{
			if (comapare_one_bot(cycle, *n) == 1)
			{
				printf("%30s \033[0;31m ERROR \033[0m\n", cs1);
				// return 0;
			}
			else
				printf("%30s \033[0;32m OK \033[0m\n", cs1);
		}
		else
		{
			for(auto i = files.begin(); i != files.end(); ++i)
			{
				string s2 = *i;
				const char *cs2 = s2.erase(0, len).c_str();
				if (bots_num == 2)
				{
					if (comapare_two_bots(cycle, *n, *i) == 1)
					{
						printf("%30s %30s \033[0;31m ERROR \033[0m\n", cs1, cs2);
						// return 0;
					}
					else
						printf("%30s %30s \033[0;32m OK \033[0m\n", cs1, cs2);
				}
				else
				{
					for(auto j = files.begin(); j != files.end(); ++j)
					{
						string s3 = *j;
						const char *cs3 = s3.erase(0, len).c_str();
						if (bots_num == 3)
						{
							if (comapare_three_bots(cycle, *n, *i, *j) == 1)
							{
								printf("%30s %30s %30s\033[0;31m ERROR \033[0m\n", cs1, cs2, cs3);
								// return 0;
							}
							else
								printf("%30s %30s %30s\033[0;32m OK \033[0m\n", cs1, cs2, cs3);
						}
						else
						{
							for(auto k = files.begin(); k != files.end(); ++k)
							{
								string s4 = *k;
								const char *cs4 = s4.erase(0, len).c_str();
								if (comapare_four_bots(cycle, *n, *i, *j, *k) == 1)
								{
									printf("%30s %30s %30s %30s\033[0;31m ERROR \033[0m\n", cs1, cs2, cs3, cs4);
									// return 0;
								}
								else
									printf("%30s %30s %30s %30s\033[0;32m OK \033[0m\n", cs1, cs2, cs3, cs4);
							}
						}
					}
				}
			}
		}
	}
	return 0;
}
