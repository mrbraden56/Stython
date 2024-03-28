#include <cstddef>    // For size_t
#include <cstring>    // For strerror
#include <fcntl.h>    // For open, O_RDONLY
#include <sys/mman.h> // For mmap, munmap
#include <sys/stat.h> // For fstat
#include <unistd.h>   // For close

class FileMap {
  char const *m_begin = nullptr;
  char const *m_end = nullptr;

public:
  // Deleted copy constructor and assignment operator.
  FileMap(FileMap const &) = delete;
  FileMap &operator=(FileMap const &) = delete;

  // Move constructor and assignment operator remain unchanged.

  explicit FileMap(const char *filename) {
    // Open file
    int file = open(filename, O_RDONLY);
    if (file == -1)
      return;

    // Get file size
    struct stat sb;
    if (fstat(file, &sb) == -1) {
      close(file);
      return;
    }

    // Map file to memory
    m_begin = static_cast<char *>(
        mmap(nullptr, sb.st_size, PROT_READ, MAP_PRIVATE, file, 0));
    if (m_begin == MAP_FAILED) {
      m_begin = nullptr;
      close(file);
      return;
    }

    m_end = m_begin + sb.st_size;

    // Close file descriptor, as it's no longer needed after mmap
    close(file);
  }

  ~FileMap() {
    if (m_begin) {
      munmap((void *)m_begin, Size());
    }
  }

  explicit operator bool() const { return m_begin != nullptr; }
  size_t Size() const { return m_end - m_begin; }
  char const *Begin() const { return m_begin; }
  char const *End() const { return m_end; }
};
