#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <utility>


class Zipper {
public:
    Zipper() = default;

    void zipFile(const std::vector<std::string>& args);
    void unzipFile(const std::vector<std::string>& args);

private:
    std::string commandParser(const std::vector<std::string>& args);
};

std::string Zipper::commandParser(const std::vector<std::string>& args) {
    std::string path = "";
    std::string fullCommands = "powershell Compress-Archive ";
    std::vector<std::pair<std::string, std::string>> commands;

    if (args[0] == "--unzip") {
        fullCommands = "powershell Expand-Archive ";
    }

    for (size_t i = 1; i < args.size(); i++) {
        if (args[i] == "--path") {
            for (size_t j = i + 1;;j++) {
                if (args[j] == "--dest") {
                    commands.push_back(std::make_pair("-Path", path.substr(0, path.size() - 2)));
                    break;
                }
                else {
                    path += "\"" + args[j] + "\", ";
                }
            }
        }
        else if (args[i] == "--dest") {
            commands.push_back(std::make_pair("-DestinationPath", args[i + 1]));
        }
    }

    for (const auto& value : commands) {
        fullCommands += value.first + " " + value.second + " ";
    }
    std::cout << "[Command] -> " << fullCommands << std::endl;

    return fullCommands;
}

void Zipper::zipFile(const std::vector<std::string>& args) {
    std::cout << "---- START ZIP FILE ----" << std::endl;
    system(commandParser(args).c_str());

}

void Zipper::unzipFile(const std::vector<std::string>& args) {
    std::cout << "---- START UNIZP FILE ----" << std::endl;
    system(commandParser(args).c_str());
}

int main(int argc, char** argv) {

    try {
        if (argc < 2) {
            throw std::invalid_argument("Two Few Args Please Enter true arguments");
        }
        else {
            std::vector<std::string> args;
            Zipper zipObject;

            for (size_t index = 1; index < argc; index++) {
                args.push_back(argv[index]);
            }

            if (args[0] == "--zip") {
                zipObject.zipFile(args);
            }
            else if (args[0] == "--unzip") {
                zipObject.unzipFile(args);
            }
            else {
                throw std::invalid_argument("You should Enter --zip or --unzip arg for first argument");
            }
        }
    }
    catch(const std::invalid_argument& error) {
        std::cerr << "[Error] -> " << error.what() << std::endl;
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}