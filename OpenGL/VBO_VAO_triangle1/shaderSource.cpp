#include <fstream>
#include <iostream>

std::string		get_shaderSource(const std::string& ShaderFile)
{
	std::ifstream file;
	std::string line;;
	std::string output;

	file.open((ShaderFile).c_str());
	if(file.is_open())
	{
		while(file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cout << "Wrong shader file\n" << std::endl;
		exit(1);
	}
	return (output);
}
