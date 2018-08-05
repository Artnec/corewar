#include <iostream>
#include <vector>
#include "unistd.h"
#include <dirent.h>
#include <sys/types.h>

using namespace std;

int		find_diference(char *comand1, char *comand2, int v_flag)
{
	char			output1[32768] = {0};
	char			output2[32768] = {0};
	FILE			*fp1 = popen(comand1, "r");
	FILE			*fp2 = popen(comand2, "r");

	int size = fread(output1, 1, 32768, fp1);
	pclose(fp1);
	int size2 = fread(output2, 1, 32768, fp2);
	pclose(fp2);
	int t = (size != size2) || (strcmp(output1, output2) != 0);
	if (v_flag == 0)
		return (t);
	if (t == 1)
	{
		for (int i = 0; i < size; ++i)
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

int		comapare_one_bot(int cycle, string a, int v_flag)
{
	char			buf[512];
	char			buf2[512];

	sprintf(buf, "./orig_corewar -d %d %s", cycle, a.c_str());
	sprintf(buf2, "./corewar -dump %d %s", cycle, a.c_str());
	return (find_diference(buf, buf2, v_flag));
}

int		comapare_two_bots(int cycle, string a, string b, int v_flag)
{
	char			buf[512];
	char			buf2[512];

	sprintf(buf, "./orig_corewar -d %d %s %s", cycle, a.c_str(), b.c_str());
	sprintf(buf2, "./corewar -dump %d %s %s", cycle, a.c_str(), b.c_str());
	return (find_diference(buf, buf2, v_flag));
}

int		comapare_three_bots(int cycle, string a, string b, string c, int v_flag)
{
	char			buf[512];
	char			buf2[512];

	sprintf(buf, "./orig_corewar -d %d %s %s %s", cycle, a.c_str(), b.c_str(), c.c_str());
	sprintf(buf2, "./corewar -dump %d %s %s %s", cycle, a.c_str(), b.c_str(), c.c_str());
	return (find_diference(buf, buf2, v_flag));
}

int		comapare_four_bots(int cycle, string a, string b, string c, string d, int v_flag)
{
	char			buf[512];
	char			buf2[512];

	sprintf(buf, "./orig_corewar -d %d %s %s %s %s", cycle, a.c_str(), b.c_str(), c.c_str(), d.c_str());
	sprintf(buf2, "./corewar -dump %d %s %s %s %s", cycle, a.c_str(), b.c_str(), c.c_str(), d.c_str());
	return (find_diference(buf, buf2, v_flag));
}

int		main(int argc, char **argv)
{
	int					d;
	int					cycle;
	int					bots_num = 0;
	int					e_flag = 0;
	int					v_flag = 0;

	if (argc == 4)
	{
		bots_num = atoi(argv[2]);
		cycle = atoi(argv[3]);
		d = 1;
	}
	else if (argc == 5)
	{
		e_flag = (!strcmp(argv[1], "-e") || !strcmp(argv[1], "-ev") || !strcmp(argv[1], "-ve")) ? 1 : 0;
		v_flag = (!strcmp(argv[1], "-v") || !strcmp(argv[1], "-ev") || !strcmp(argv[1], "-ve")) ? 1 : 0;
		bots_num = atoi(argv[3]);
		cycle = atoi(argv[4]);
		d = 2;
	}
	else if (argc == 6)
	{
		e_flag = (!strcmp(argv[1], "-e") || !strcmp(argv[2], "-e")) ? 1 : 0;
		v_flag = (!strcmp(argv[1], "-v") || !strcmp(argv[2], "-v")) ? 1 : 0;
		bots_num = atoi(argv[4]);
		cycle = atoi(argv[5]);
		d = 3;
	}
	if (bots_num < 1 || bots_num > 4 || (argc == 5 && e_flag == 0 && v_flag == 0)
		|| (argc == 6 && (e_flag == 0 || v_flag == 0)))
	{
		printf("Usage:  %s  [-e -v | -ev]  directory  bots_num[1-4]  dump_cycle\n        -e to "
			"exit after first error\n        -v to visually display difference\n", argv[0]);
		return 0;
	}
	vector<string>		files;
	struct dirent		*entry;
	DIR					*dir;
	int					len = strlen(argv[d]) + 1;

	dir = opendir(argv[d]);
	if (dir == NULL)
	{
		printf("Error: bad directory name\n");
		return 0;
	}
	while ((entry = readdir(dir)))
	{
		int l = strlen(entry->d_name);
		if (entry->d_name[0] == '.' || l < 5 || strcmp(entry->d_name + l - 4, ".cor"))
			continue ;
		files.push_back(argv[d] + string("/") + entry->d_name);
	}
	closedir(dir);
	for (auto n = files.begin(); n != files.end(); ++n)
	{
		string s1 = *n;
		const char *cs1 = s1.erase(0, len).c_str();
		if (bots_num == 1)
		{
			if (comapare_one_bot(cycle, *n, v_flag) == 1)
			{
				if (v_flag == 0)
					printf("%-30s ERROR\n", cs1);
				else
					printf("%-30s \033[0;31m ERROR \033[0m\n", cs1);
				if (e_flag == 1)
					return 0;
			}
			else
			{
				if (v_flag == 0)
					printf("%-30s OK\n", cs1);
				else
					printf("%-30s \033[0;32m OK \033[0m\n", cs1);
			}
		}
		else
		{
			for (auto i = files.begin(); i != files.end(); ++i)
			{
				string s2 = *i;
				const char *cs2 = s2.erase(0, len).c_str();
				if (bots_num == 2)
				{
					if (comapare_two_bots(cycle, *n, *i, v_flag) == 1)
					{
						if (v_flag == 0)
							printf("%-30s %-30s ERROR\n", cs1, cs2);
						else
							printf("%-30s %-30s \033[0;31m ERROR \033[0m\n", cs1, cs2);
						if (e_flag == 1)
							return 0;
					}
					else
					{
						if (v_flag == 0)
							printf("%-30s %-30s OK\n", cs1, cs2);
						else
							printf("%-30s %-30s \033[0;32m OK \033[0m\n", cs1, cs2);
					}
				}
				else
				{
					for (auto j = files.begin(); j != files.end(); ++j)
					{
						string s3 = *j;
						const char *cs3 = s3.erase(0, len).c_str();
						if (bots_num == 3)
						{
							if (comapare_three_bots(cycle, *n, *i, *j, v_flag) == 1)
							{
								if (v_flag == 0)
									printf("%-30s %-30s %-30s ERROR\n", cs1, cs2, cs3);
								else
									printf("%-30s %-30s %-30s\033[0;31m ERROR \033[0m\n", cs1, cs2, cs3);
								if (e_flag == 1)
									return 0;
							}
							else
							{
								if (v_flag == 0)
									printf("%-30s %-30s %-30s OK\n", cs1, cs2, cs3);
								else
									printf("%-30s %-30s %-30s\033[0;32m OK \033[0m\n", cs1, cs2, cs3);
							}
						}
						else
						{
							for (auto k = files.begin(); k != files.end(); ++k)
							{
								string s4 = *k;
								const char *cs4 = s4.erase(0, len).c_str();
								if (comapare_four_bots(cycle, *n, *i, *j, *k, v_flag) == 1)
								{
									if (v_flag == 0)
										printf("%-30s %-30s %-30s %-30s ERROR\n", cs1, cs2, cs3, cs4);
									else
										printf("%-30s %-30s %-30s %-30s\033[0;31m ERROR \033[0m\n", cs1, cs2, cs3, cs4);
									if (e_flag == 1)
										return 0;
								}
								else
								{
									if (v_flag == 0)
										printf("%-30s %-30s %-30s %-30s OK\n", cs1, cs2, cs3, cs4);
									else
										printf("%-30s %-30s %-30s %-30s\033[0;32m OK \033[0m\n", cs1, cs2, cs3, cs4);
								}
							}
						}
					}
				}
			}
		}
	}
	return 0;
}
