#include <iostream>
#include <fstream>

class File
{
public:
    File(const char *filename) : m_handle(std::ifstream(filename)) {}
    ~File()
    {
        if (m_handle.is_open())
        {
            std::cout << "File is closed." << std::endl;
            m_handle.close();
        }
    }

    std::ifstream &getHandle()
    {
        return m_handle;
    }

private:
    std::ifstream m_handle;
};

int main()
{
    File myfile("example.txt");
    if (myfile.getHandle().is_open())
    {
        std::cout << "File is opened." << std::endl;
        // do some work with the file
    }
    else
    {
        std::cout << "Failed to open the file." << std::endl;
    }
    return 0;
}

// int main() {
//     std::ifstream myfile("example.txt"); // 换自己的文件路径
//     if (myfile.is_open()) {
//         std::cout << "File is opened." << std::endl;
//         // do some work with the file
//     }
//     else {
//         std::cout << "Failed to open the file." << std::endl;
//     }
//     myfile.close();
//     return 0;
// }