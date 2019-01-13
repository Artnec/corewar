#include <iostream>
#include <vector>
#include <dirent.h>

using namespace std;

#define BUF_SIZE	32768

static bool		v_flag;
static bool		e_flag;
char			cmd_buf1[512];
char			cmd_buf2[512];

static bool		find_diference(char *comand1, char *comand2)
{
	char			output1[BUF_SIZE];
	char			output2[BUF_SIZE];
	FILE			*fp1 = popen(comand1, "r");
	FILE			*fp2 = popen(comand2, "r");

	int size1 = fread(output1, 1, BUF_SIZE - 1, fp1);
	output1[size1] = '\0';
	pclose(fp1);

	int size2 = fread(output2, 1, BUF_SIZE - 1, fp2);
	output2[size2] = '\0';
	pclose(fp2);

	bool ret = (size1 != size2) || (strcmp(output1, output2) != 0);
	if (v_flag == true && ret == true)
	{
		for (int i = 0; i < size1; ++i)
		{
			if (output1[i] != output2[i])
				printf("\033[1;31m");
			printf("%c", output1[i]);
			if (output1[i] != output2[i])
				printf("\033[0m");
		}
	}
	return (ret);
}

static bool		comapare_one_bot(int cycle, const string &a)
{
	sprintf(cmd_buf1, "./orig_corewar -d %d %s", cycle, a.c_str());
	sprintf(cmd_buf2, "./corewar -dump %d %s", cycle, a.c_str());
	return (find_diference(cmd_buf1, cmd_buf2));
}

static bool		comapare_two_bots(int cycle, const string &a, const string &b)
{
	sprintf(cmd_buf1, "./orig_corewar -d %d %s %s", cycle, a.c_str(), b.c_str());
	sprintf(cmd_buf2, "./corewar -dump %d %s %s", cycle, a.c_str(), b.c_str());
	return (find_diference(cmd_buf1, cmd_buf2));
}

static bool		comapare_three_bots(int cycle, const string &a, const string &b, const string &c)
{
	sprintf(cmd_buf1, "./orig_corewar -d %d %s %s %s", cycle, a.c_str(), b.c_str(), c.c_str());
	sprintf(cmd_buf2, "./corewar -dump %d %s %s %s", cycle, a.c_str(), b.c_str(), c.c_str());
	return (find_diference(cmd_buf1, cmd_buf2));
}

static bool		comapare_four_bots(int cycle, const string &a, const string &b, const string &c, const string &d)
{
	sprintf(cmd_buf1, "./orig_corewar -d %d %s %s %s %s", cycle, a.c_str(), b.c_str(), c.c_str(), d.c_str());
	sprintf(cmd_buf2, "./corewar -dump %d %s %s %s %s", cycle, a.c_str(), b.c_str(), c.c_str(), d.c_str());
	return (find_diference(cmd_buf1, cmd_buf2));
}

static void		print_res_exit_on_error(bool result)
{
	const char *res[2] = {"OK", "ERROR"};
	if (v_flag == true)
		printf("\033[0;3%dm %s \033[0m\n", result == true ? 1 : 2, res[result]);
	else
		printf(" %s \n", res[result]);
	if (e_flag == true && result == true)
		exit(0);
}

static void		get_file_names(vector<string> &file_names, const char *dir_name)
{
	DIR *dir = opendir(dir_name);
	if (dir == NULL)
	{
		printf("Error: bad directory name\n");
		exit(1);
	}

	struct dirent	*entry;
	while ((entry = readdir(dir)))
	{
		int l = strlen(entry->d_name);
		if (entry->d_name[0] == '.' || l < 5 || strcmp(entry->d_name + l - 4, ".cor"))
			continue ;
		file_names.push_back(dir_name + string("/") + entry->d_name);
	}
	closedir(dir);
}

static void		print_usage_exit(const char *prog_name)
{
	printf("Usage:  %s  [-e -v | -ev]  directory  bots_num[1-4]  dump_cycle\n        -e to "
		"exit after first error\n        -v to visually display difference\n", prog_name);
	exit(0);
}

int		main(int argc, char **argv)
{
	if (argc < 4 || argc > 6)
		print_usage_exit(argv[0]);

	else if (argc == 5)
	{
		if (!strcmp(argv[1], "-e") || !strcmp(argv[1], "-ev") || !strcmp(argv[1], "-ve"))
			e_flag = true;
		if (!strcmp(argv[1], "-v") || !strcmp(argv[1], "-ev") || !strcmp(argv[1], "-ve"))
			v_flag = true;
		if (e_flag == false && v_flag == false)
			print_usage_exit(argv[0]);
	}
	else if (argc == 6)
	{
		if (!strcmp(argv[1], "-e") || !strcmp(argv[2], "-e"))
			e_flag = true;
		if (!strcmp(argv[1], "-v") || !strcmp(argv[2], "-v"))
			v_flag = true;
		if (e_flag == false || v_flag == false)
			print_usage_exit(argv[0]);
	}

	int bots_num = atoi(argv[argc - 2]);
	int cycle = atoi(argv[argc - 1]);
	if (bots_num < 1 || bots_num > 4 || cycle < 0)
		print_usage_exit(argv[0]);

	int dir_idx = argc - 3;
	vector<string>	file_names;
	get_file_names(file_names, argv[dir_idx]);

	int dir_name_len = strlen(argv[dir_idx]) + 1;
	for (const string &s1 : file_names)
	{
		const string &f1 = s1.substr(dir_name_len);
		if (bots_num == 1)
		{
			bool res = comapare_one_bot(cycle, s1);
			printf("%-30s", f1.c_str());
			print_res_exit_on_error(res);
		}
		else
		{
			for (const string &s2 : file_names)
			{
				const string &f2 = s2.substr(dir_name_len);
				if (bots_num == 2)
				{
					bool res = comapare_two_bots(cycle, s1, s2);
					printf("%-30s %-30s", f1.c_str(), f2.c_str());
					print_res_exit_on_error(res);
				}
				else
				{
					for (const string &s3 : file_names)
					{
						const string &f3 = s3.substr(dir_name_len);
						if (bots_num == 3)
						{
							bool res = comapare_three_bots(cycle, s1, s2, s3);
							printf("%-30s %-30s %-30s", f1.c_str(), f2.c_str(), f3.c_str());
							print_res_exit_on_error(res);
						}
						else
						{
							for (const string &s4 : file_names)
							{
								const string &f4 = s4.substr(dir_name_len);
								bool res = comapare_four_bots(cycle, s1, s2, s3, s4);
								printf("%-30s %-30s %-30s %-30s", f1.c_str(), f2.c_str(), f3.c_str(), f4.c_str());
								print_res_exit_on_error(res);
							}
						}
					}
				}
			}
		}
	}
	return 0;
}
