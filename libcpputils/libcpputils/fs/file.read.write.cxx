#include <filesystem>
#include <fstream>
#include <iostream>
// import<filesystem>;
// import<fstream>;
// import<iostream>;

auto
manipulate_file() noexcept -> void {
  namespace fs = std::filesystem;
  try {
    const auto path = fs::path("/home/ultracode/Repository/C++/MyFile.txt");
    std::ofstream outfile{path, std::ofstream::trunc};
    if (outfile.is_open()) {
      outfile << " This is a working version of the program \n";
      std::cout << "Text has been written to the file \n";
      int first{1};
      int second{2};
      int third{3};
      outfile << " The sum of values read from infiles is "
              << (first + second + third) << '\n';
      outfile.close();
    } else {
      throw std::runtime_error("File not opened\n");
    }
    std::string outfile_data(fs::file_size(path), '\0');
    std::ifstream infile{path};
    std::cout << "Content of " << path << " \n";
    infile.read(outfile_data.data(), fs::file_size(path));
    infile >> outfile_data;
    std::cout << outfile_data << std::endl;
    //    for (auto content{std::string{}}; !infile.eof();
    //         std::getline(infile, content))
    //    { std::cout << content << std::endl; }
    infile.close();
  } catch (const std::exception &e) {
    std::cerr << " an exception has been thrown " << e.what() << '\n';
  }
}
