#include <list>
#include <string>
#include <fstream>
#include <cstring>
#include <iostream>

class File {
public:
  File(std::string name, size_t size)
    : m_size(size)
    , m_name(name)
    {}

  size_t size() { return m_size; }
private:
  size_t m_size;
  std::string m_name;
};

class Directory {
public:
  Directory(std::string name, Directory* parent)
    : m_name(name)
    , m_subdirs()
    , m_files()
    , m_known_size(0)
    , m_parent(parent)
    {}

  size_t size() const { return m_known_size; }
  void add_file(std::string name, size_t size);
  void add_dir(std::string name);
  Directory* change_dir(std::string dir);
  std::string name() const {return m_name; }
  const std::list<Directory>& subdirs() const {return m_subdirs; }

private:
  const std::string m_name;
  std::list<Directory> m_subdirs;
  std::list<File> m_files;
  size_t m_known_size;
  Directory *m_parent;
};

Directory* Directory::change_dir(std::string dir) {
  if (dir == "..") {
    return m_parent;
  }

  for (auto& d : m_subdirs) {
    if (d.m_name == dir) {
      return &d;
    }
  }

  return nullptr;
}

void Directory::add_file(std::string name, size_t size) {
  m_files.push_back(File(name, size));
  m_known_size += size;

  // travel up to the base node and update the size
  Directory* parent = m_parent;
  while (parent != nullptr) {
    parent->m_known_size += size;
    parent = parent->m_parent;
  }
}

void Directory::add_dir(std::string name) {
  m_subdirs.push_back(Directory(name, this));
}

void find_dirs_at_most(const size_t max_size, const Directory& base, size_t& total) {
  if (base.size() <= max_size) {
    total += base.size();
  }

  for (auto& sd : base.subdirs()) {
    find_dirs_at_most(max_size, sd, total);
  }
}

// assumes it exists, or will return base
void find_smallest_at_least(const size_t min_size, const Directory& base, Directory** smallest) {
  if (base.size() >= min_size && base.size() < (*smallest)->size()) {
    *smallest = const_cast<Directory*>(&base);
    std::cout << (*smallest)->name() << " " << (*smallest)->size() << std::endl;
  }

  for (const auto& sd : base.subdirs()) {
    find_smallest_at_least(min_size, sd, smallest);
  }
}

int main() {
  Directory base = Directory("/", nullptr);
  Directory* current = &base;

  std::ifstream input("input.txt");
  std::string line;

  // assumes first command is "cd /"
  // also does EXTREMELY janky assumptional parsing

  while (std::getline(input, line)) {
    if (line[0] == '$') {
      if (line[2] == 'c') {
        std::string dir = line.substr(5);
        current = current->change_dir(dir);
      } else if (line[2] == 'l') {
        continue;
      }
    } else {
      char* linech = new char[line.length() + 1];
      std::strcpy(linech, line.c_str());


      // file listing
      if (std::isdigit(linech[0])) {
        auto file_size = std::atoi(std::strtok(linech, " "));
        std::string file_name = std::string(std::strtok(NULL, " "));
        current->add_file(file_name, file_size);
      } else {
        current->add_dir(line.substr(4));
      }

      delete[] linech;
    }
  }

  size_t total = 0;
  find_dirs_at_most(100000, base, total);
  Directory* smallest = &base;

  std::cout << "finding smallest dir with min size... " << 30000000 - (70000000  - base.size()) << std::endl;
  find_smallest_at_least(30000000 - (70000000  - base.size()), base, &smallest);

  std::cout << "Part1: " << total << std::endl;
  std::cout << "Part2: " << smallest->name() << " : " << smallest->size() << std::endl;

  return 0;
}