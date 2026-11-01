#include <iostream>
#include <streambuf>

class LineCounter : public std::streambuf {
 public:
  int lines = 0;

 protected:
  int_type overflow(int_type ch) override {
    if (traits_type::eq_int_type(ch, traits_type::eof()))
      return traits_type::not_eof(ch);
    if (traits_type::to_char_type(ch) == '\n') ++lines;
    return ch;
  }
};

int main() {
  LineCounter output;
  auto* original = std::cout.rdbuf(&output);
  // --8<-- [start:core]
  constexpr int N = 100000;
  for (int i = 0; i < N; ++i) {
    std::cout << "hello world\n";
  }
  // --8<-- [end:core]
  std::cout.rdbuf(original);
  std::cout << output.lines << "\n";
}
