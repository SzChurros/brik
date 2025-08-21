#include <stdio.h>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>

std::vector<std::string> fetchfile(const char* path);
void writefile(const char* path, std::vector<std::string> data);
void help();

int main (int argc, char* argv[])
{
	if (argc != 2)
	{
		help();
		return -1;
	}

	std::vector<std::string> filecontent = fetchfile(argv[1]);
	if (filecontent[0] == "err:nofile")
	{	
		printf("file does not exist mate\n");
		return 1;
	}

	
	system("rm -r build");
	printf("removed old build folder\n");

	system("mkdir build");
	

	int crntln = 0;
	int temp = 0;

	bool compileonly = 0;
	bool cpp = 0;

	std::vector<std::string> tolink = {};

	std::string projectname = "";
	std::string command = "";

	if (filecontent[crntln++] == "compile")
	{
		compileonly = 1;	
	}
	else
	{
		system("rm -r bin");
		system("mkdir bin");
	}
	if (filecontent[crntln++] == "copy")
	{
		temp = stoi(filecontent[crntln++]);
		for (int i = 0; i < temp; i++)
		{
			std::string temp2 = filecontent[crntln++];
			command = "cp -r " + temp2 + " bin/" + temp2;
			system(command.c_str());
		}

		printf("copied folder(s)\n");
	}
	projectname = filecontent[crntln++];

	temp = stoi(filecontent[crntln++]);	

	
	for (int i = 0; i < temp; i++)
	{
		command = "mkdir build/" + filecontent[crntln++];

		system(command.c_str());
	}

	printf("remade folder structure\n");

	while(filecontent[crntln] != "endoffile")
	{
		if (filecontent[crntln] == "Cpp")
		{
			crntln++;
			cpp = 1;
			temp = stoi(filecontent[crntln++]);
			for (int i = 0; i < temp; i++)
			{
				std::string temp2 = filecontent[crntln++];
				command = "g++ -c " + temp2 + " -o build/" + temp2 + ".o";
				system(command.c_str());
				tolink.push_back("build/" + temp2 + ".o");
			}
		}
		else if (filecontent[crntln] == "C")
		{
			crntln++;
			temp = stoi(filecontent[crntln++]);
			for (int i = 0; i < temp; i++)
			{
				std::string temp2 = filecontent[crntln++];
				command = "gcc -c " + temp2 + " -o build/" + temp2 + ".o";
				system(command.c_str());
				tolink.push_back("build/" + temp2 + ".o");
			}
		}
		else if (filecontent[crntln] == "lib")
		{
			crntln++;
			temp = stoi(filecontent[crntln++]);
			for (int i = 0; i < temp; i++)
			{
				std::string temp2 = "thirdparty/" + filecontent[crntln++] + "/brik.lib";
				std::string crnt = "";
				std::fstream file(temp2);

				if (!file.is_open())
					return 2;

				while (getline(file, crnt))
				{
					tolink.push_back(crnt);
				}

				file.close();
			}
		}
	}

	if (compileonly)
	{
		std::vector<std::string> moddat = {};
		for (int i = 0; i < tolink.size(); i++)
		{
			moddat.push_back("thirdparty/" + projectname + "/" + tolink[i]);
		}
		writefile("brik.lib.txt", moddat);
		printf("built liblary\n");
	}
	else
	{
		if (cpp)
		{
			command = "g++ ";
		}
		else
		{
			command = "gcc ";
		}

		for (int i = 0; i < tolink.size(); i++)
		{
			command += tolink[i] + " ";
		}

		command += "-o bin/" + projectname;

		system(command.c_str());
		printf("built executable\n");
	}

	return 0;
}

void help()
{
	printf("please do:\n");
	printf("  brik [path to the brik.cfg from the target project]\n");
}

std::vector<std::string> fetchfile(const char* path)
{
	std::string crnt = "";
	std::vector<std::string> ret = {};
	std::fstream file(path);

	if (!file.is_open())
		return {"err:nofile"};

	while (getline(file, crnt))
	{
		ret.push_back(crnt);
	}

	file.close();
	return ret;
}

void writefile(const char* path, std::vector<std::string> data)
{
	std::string dat = "";

	for (int i = 0; i < data.size(); i++)
	{
		dat += data[i];
	}

	std::ofstream file(path);
	
	file << dat;

	file.close();
	return;
}
