#include <bits/stdc++.h>
using namespace std;

string compile(string code) {
  int pos = code.rfind('.');
  string name = code.substr(0, pos),
         lang = code.substr(pos + 1, code.size() - pos - 1);
  if (lang == "cpp") {
    string cmd = "g++ -O2 -std=c++17 -Wno-unused-result -o tmp " + code;
#ifdef withsan
    cmd += " -fsanitize=address,undefined";
#endif
    if (system(cmd.c_str())) {
      cout << code + " Compile Error :(\n";
      exit(1);
    }
#ifdef withsan
    cout << code + " Successfully compiled\n";
#endif
    return "./tmp";
  }
  if (lang == "py") {
#ifdef withsan
    cout << code + " No need to compile :/\n";
#endif
    assert(!system(("cat " + code + ">tmp.py").c_str()));
    return "python tmp.py";
  }
  cout << code + "Unknown language: " + lang;
  exit(1);
}

int main(int ac, char** av) {
  if (ac ^ 4) {
    cout << "usage: code in out\n";
    exit(1);
  }
  string code(av[1]), in(av[2]), out(av[3]);
  string cmd = compile(code);
  cmd += "<" + in + ">" + out;
  cmd = "timeout 10s " + cmd;
#ifndef withsan
  cmd = "ulimit -v 1048576\ntime -f \'%Us %MKB\' " + cmd;
#endif
  int returnvalue = system(cmd.c_str());
  if (returnvalue == 124 || returnvalue == 124 << 8) {
    cout << code + " Time Out :(\n";
    exit(1);
  }
  if (returnvalue) {
    cout << code + " Runtime Error or Memory Limit Exceeded :(\n";
    exit(1);
  }
  return 0;
}
