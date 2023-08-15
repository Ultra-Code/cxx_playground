#include <filesystem>
#include <span>
#include <fstream>
#include <cstdlib>
#include <iostream>
// import<cstdlib>;
// import<filesystem>;
// import<span>;
// import<fstream>;
// import<iostream>;

namespace fs = std::filesystem;

auto check_filesystems(int argc, char *argv[]) noexcept -> void;
auto create_files_directory() noexcept -> void;
auto the_main(int argc, char *argv[]) -> int;

auto
the_main(int argc, char *argv[]) -> int {
  check_filesystems(argc, argv);
  create_files_directory();
};

auto
check_filesystems(int argc, char *argv[]) noexcept -> void {
  const std::span argv_span{argv, 1};
  if (argc < 2) {
    std::cout << "Usage : " << *(argv_span.begin()) << " <path> \n";
  }
  switch (fs::path path{*(argv_span.begin() + 1)}; fs::status(path).type()) {
  case fs::file_type::not_found: {
    std::cout << path << " doesn't exits \n";
    break;
  }
  case fs::file_type::directory: {
    std::cout << path << " is a directory conataining \n";
    for (const auto &directory_entries : fs::directory_iterator(path)) {
      std::cout << directory_entries.path() << '\n';
    }
    break;
  }
  case fs::file_type::regular: {
    constexpr auto kibi   = double{1024};
    auto &&fsize_kibibyte = static_cast<double>(fs::file_size(path)) / kibi;
    std::cout << path << " already exist with file size " << fsize_kibibyte
              << " kiB \n";
    break;
  }
  case fs::file_type::block: {
    std::cout << path << " is a block file/device \n";
    break;
  }
  case fs::file_type::symlink: {
    std::cout << path << " is a symlink file \n";
    break;
  }
  case fs::file_type::none: {
    std::cout << path << " is a special file \n";
  }
  }
  // fs::path path{*(argv_span.begin() + 1)};
  // std::cout << " path is " << path << '\n';
  /*if (fs::is_regular_file(path))
  {
      auto&& fsize = fs::file_size(path);
      constexpr auto kibi = double{1024};
      auto&& fsize_kibibyte = static_cast<double>(fsize) / kibi;
      std::cout << path << " already exist with file size " << fsize_kibibyte
                << " kiB \n";
  }
  else if (fs::is_directory(path))
  {
      std::cout << path << " is a directory conataining \n";
      for (const auto& files : fs::directory_iterator(path))
      {
          std::cout << files.path() << '\n';
      }
  }
  else if (fs::exists(path))
  {
      std::cout << path << " is a special file \n";
  }
  else
  {
      std::cout << path << " doesn't exits \n";
  }*/
}

auto
create_files_directory() noexcept -> void {
  try {
    // create directories tmp/test/ (if they don’t exist yet):
    fs::path directory{"/tmp/fs/test"};
    if (!fs::create_directories(directory)) {
      std::cerr << " Directory " << directory << " exits already \n";
    } else {
      fs::create_directories(directory);
    }
    // create data file tmp/test/data.txt:
    const auto &&data_txt = directory / "data.txt";
    auto &&data_file      = std::ofstream(data_txt);
    if (!data_file.is_open()) {
      std::cerr << " OOPS , can't open " << data_txt.filename() << " \n";
      std::exit(EXIT_FAILURE);
    } else {
      data_file << " My Beautifull portable file ";
      data_file.close();
    }
    // create symbolic link from tmp/slink/ to tmp/test/:
    std::cout << directory.relative_path() << '\n';
    const auto &&symlink_path = directory.parent_path() / "data_symlink";
    if (fs::is_symlink(symlink_path)) {
      std::cerr << " Symlink path " << symlink_path << " already exist \n";
    } else {
      fs::create_directory_symlink("test", symlink_path);
    }

    // recursively list all files (also following symlinks)
    std::cout << fs::current_path() << " :\n";
    {
      const auto &&dir_option{fs::directory_options::follow_directory_symlink};
      for (const auto &entries :
           fs::recursive_directory_iterator(directory, dir_option)) {
        std::cout << "  " << entries.path().lexically_normal() << '\n';
      }
    }
  } catch (const fs::filesystem_error &exception) {
    std::cerr << " EXCEPTION what(): " << exception.what() << '\n';
    std::cerr << " EXCEPTION path1(): " << exception.path1() << '\n';
    std::cerr << " EXCEPTION path2(): " << exception.path2() << '\n';
    std::cerr << " EXCEPTION error_code() : " << exception.code() << '\n';
  }
}
