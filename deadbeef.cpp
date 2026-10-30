/*:::::
 *:::::Project   : [0xDEADBEEF]
 *:::::Author    : [Dev.Basil ]
 *:::::
 *:::::
 *:::::
 *:::::
 *:::::
 */
/*
  ▄▄▄▄         ▄▄▄▄   ▄▄▄▄▄▄   ▄▄   ▄▄▄▄   ▄▄▄▄▄  ▄▄▄▄▄▄ ▄▄▄▄▄▄ ▄▄▄▄▄▄
 ▄▀  ▀▄ ▄   ▄  █   ▀▄ █        ██   █   ▀▄ █    █ █      █      █
 █  ▄ █  █▄█   █    █ █▄▄▄▄▄  █  █  █    █ █▄▄▄▄▀ █▄▄▄▄▄ █▄▄▄▄▄ █▄▄▄▄▄
 █    █  ▄█▄   █    █ █       █▄▄█  █    █ █    █ █      █      █
  █▄▄█  ▄▀ ▀▄  █▄▄▄▀  █▄▄▄▄▄ █    █ █▄▄▄▀  █▄▄▄▄▀ █▄▄▄▄▄ █▄▄▄▄▄ █
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <dirent.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <thread>
#include <chrono>

// define
#define reset      "\033[0m "
#define red        "\033[31m"
#define green      "\033[32m"
#define yellow     "\033[33m"
#define blue        "\033[34m"
#define magenta    "\033[35m"
#define cyan       "\033[36m"
#define white      "\033[37m"
#define bg_black   "\033[40m"
#define bg_red     "\033[41m"
#define bg_green   "\033[42m"
#define bg_yellow  "\033[43m"
#define bg_blue    "\033[44m"
#define bg_magenta "\033[45m"
#define bg_cyan    "\033[46m"
#define bg_white   "\033[47m"

using namespace std;

struct Process {
    pid_t pid;
    std::string name;
    double mem_mb;
};
void printlogo () {
    {
        std::cout << bg_red;
        std::cout << " ▗▄▖      ▗▄▄  ▗▄▄▄▖  ▄  ▗▄▄  ▗▄▄▖ ▗▄▄▄▖▗▄▄▄▖▗▄▄▄▖" << std::endl;
        std::cout << " █▀█      ▐▛▀█ ▐▛▀▀▘ ▐█▌ ▐▛▀█ ▐▛▀▜▌▐▛▀▀▘▐▛▀▀▘▐▛▀▀▘" << std::endl;
        std::cout << "▐▌ ▐▌▝█ █▘▐▌ ▐▌▐▌    ▐█▌ ▐▌ ▐▌▐▌ ▐▌▐▌   ▐▌   ▐▌   " << std::endl;
        std::cout << "▐▌█▐▌ ▐█▌ ▐▌ ▐▌▐███  █ █ ▐▌ ▐▌▐███ ▐███ ▐███ ▐███ " << std::endl;
        std::cout << "▐▌ ▐▌ ▗█▖ ▐▌ ▐▌▐▌    ███ ▐▌ ▐▌▐▌ ▐▌▐▌   ▐▌   ▐▌   " << std::endl;
        std::cout << " █▄█  ▟▀▙ ▐▙▄█ ▐▙▄▄▖▗█ █▖▐▙▄█ ▐▙▄▟▌▐▙▄▄▖▐▙▄▄▖▐▌   " << std::endl;
        std::cout << " ▝▀▘ ▝▀ ▀▘▝▀▀  ▝▀▀▀▘▝▘ ▝▘▝▀▀  ▝▀▀▀ ▝▀▀▀▘▝▀▀▀▘▝▘   " << std::endl;
        std::cout << reset;
        {

            std::this_thread::sleep_for(std::chrono::milliseconds(800));
            std::cout << bg_yellow << "[0xDEADBEEF]" << reset << "The term |0xDEADBEEF| " << std::endl;
            std::cout << " is a hexadecimal value associated with computer memory."<< std::endl;
            std::cout << " For help with commands, use --help.\n"<< std::endl;
            std::cout  << red << "[information]" << reset << "Rerun the tool with the --help command." << std::endl;
        }
    }
};

bool  isNumber(const std::string& str) {
    {
        return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
    }
}

std::vector<Process> fetchSystemProcesses() {
    {
        std::vector<Process> plist;
        DIR* dir = opendir("/proc");
        if (!dir) return plist;
        struct dirent* entry;
        while ((entry = readdir(dir)) != nullptr) {
            {

                if (entry->d_type == DT_DIR && isNumber(entry->d_name)) {

                    pid_t pid = std::stoi(entry->d_name);
                    std::string fpath = "/proc/" + std::string(entry->d_name);

                    std::ifstream comm(fpath + "/comm");
                    std::string name = "Unknown";
                    if (comm) std::getline(comm, name);

                    std::ifstream status (fpath + "/status");
                    std::string line;
                    long mem_kp = 0;
                    while (std::getline(status, line)) {
                        {

                            if (line.rfind("VmRSS:" ,0)== 0) {

                                std::istringstream iss (line);
                                std::string key;
                                iss >> key >> mem_kp;
                                break;
                           }
                        }
                    }
                plist.push_back({pid, name, mem_kp / 1024.0});

                }
            }
        }

        closedir(dir);
        return plist;
    }
}
void executehelp () {
    std::cout << bg_blue <<  "     --scan      "   << bg_green << "  List active processes and RSS memory    \n" << reset;
    std::cout << bg_blue <<  "  --kill <PID>   "   << bg_green << "  Terminate task via SIGKILL (0xDEADBEEF) \n" << reset;
    std::cout << bg_blue <<  "  --top <COUNT>  "   << bg_green << "  Display top memory consumers            \n" << reset;
    std::cout << bg_blue <<  " --search <NAME> "   << bg_green << "  Find process ID by identifier           \n" << reset;
    std::cout << bg_blue <<  "  --info <PID>   "   << bg_green << "  Display process status block            \n" << reset;
    std::cout << bg_blue <<  "  --maps <PID>   "   << bg_green << "  Trace virtual memory segments           \n" << reset;
    std::cout << bg_blue <<  "  --fd <PID>     "   << bg_green << "  Audit open file descriptors and sockets \n" << reset;
}

void  executeScan() {
    {
        {// cout >> show running application                                                     // SCAN
            std::cout << bg_blue << "[+]" << reset << "Show running applications" << std::endl;
            this_thread::sleep_for(chrono::milliseconds(900));
            std::cout << bg_yellow <<"[=]" << red << "information" << reset << std::endl;
            {
                this_thread::sleep_for(std::chrono::milliseconds(600));
                cout << yellow << "PID   <>   SS   <>  NAME" << reset << endl; //  SS << >>Storage space
                this_thread::sleep_for(std::chrono::seconds(1)); // 1s
            }
        }
        auto list = fetchSystemProcesses();
        for (const auto& p : list) {
            {
                std::cout << p.pid << "\t"
                          << std::fixed << std::setprecision(2) << p.mem_mb <<"MB\t"
                          << p.name << "\n";
            }
        } // ** execoute(kill) pid_t
    }
    std::cout << blue <<"-------------------0xDEADBEEF--------------------" << reset <<std::endl;
}
// void
void executeKill (pid_t pid) {
    {
        if (kill(pid, SIGKILL) == 0) {
            std::cout << bg_red << "[+] PID" << reset << "terminated (0xDEADBEEF). \n";
        } else {
            std::cerr << bg_red << "[Error]" << reset << "terminate PID "<< pid << ".\n";
        }
    }
}

void executeTop(int count) {
    {
        auto list = fetchSystemProcesses();
        std::sort(list.begin() , list.end(), [](const Process& a, const Process& b){
             {
                 return a.mem_mb > b.mem_mb;
             }
        });
        for (int i = 0; i < std::min(count, (int)list.size()) ; ++i) {
            {
                std::cout << list[i].pid << "\t"
                          << std::fixed << std::setprecision(2) << list[i].mem_mb << "MB\t"
                          << list[i].name << "\n";
            }
        }
    }
}
void executeSearch(const std::string& query) {
    {
        auto list = fetchSystemProcesses();
        for (const auto & p : list){

           {
               if (p.name.find(query) != std::string::npos) {
                   std::cout << p.pid << "\t" << p.name << "\n";
               }
           }
        }
    }
}
void executeMaps (pid_t pid) {
    {

       std::ifstream file("/proc/" + std::to_string(pid) + "/maps");
       if (!file) return;
       std::string line;
       int limit = 0;
       while (std::getline(file, line) && limit < 25) {
          {
              std::cout << line << "\n";
              limit++;
           }
        }
    }
}
void executeFd(pid_t pid) {
    {
        std::string path = "/proc/" + std::to_string(pid) + "/fd";
        DIR* dir = opendir(path.c_str());
        if (!dir) return;
        struct dirent* entry;
        while ((entry = readdir (dir)) != nullptr) {
            {
                if(entry->d_name[0] != '.') {
                    char target[256];
                    std::string lnk = path + "/" + entry->d_name;
                    ssize_t len = readlink(lnk.c_str() , target, sizeof(target) - 1);
                    if (len != -1) {
                        target[len] = '\0';
                        std::cout << entry->d_name << " -> " << target << "\n";
                    }
                }
            }
        }
        closedir(dir);
    }
}
int main (int argc, char* argv[]) {
    {
        if (argc < 2) {
            printlogo();
            return 0;
        }
        std::string sw = argv [1];

        if (sw == "--scan") executeScan();
        else if (sw == "--kill" && argc == 3 && isNumber(argv[2])) executeKill(std::stoi(argv[2]));
        else if (sw == "--top"  && argc == 3 && isNumber(argv[2])) executeTop(std::stoi(argv[2]));
        else if (sw == "--search" && argc ==3) executeSearch(argv[2]);
        else if (sw == "--maps" && argc == 3 && isNumber(argv[2])) executeMaps(std::stoi (argv[2]));
        else if (sw == "--fd" && argc == 3 && isNumber(argv[2])) executeFd(std::stoi(argv[2]));
        else if (sw == "--help") executehelp ();
        else{
            std::cerr << "DEADBEEF: invalid option\n";
        }
        return 0;
    }
} 
