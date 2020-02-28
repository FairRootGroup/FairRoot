#include <sstream>

void load_all_libs(string libdir)
{
  bool success(true);

  TString cmd(Form("ls -1 %s/* | grep -e '\\.so$' -e '\\.dylib'", libdir.c_str()));
  string libs(gSystem->GetFromPipe(cmd));

  istringstream islibs(libs);
  string lib;
  while(getline(islibs, lib)) {
    string name;
    istringstream islib(lib);
    while(getline(islib, name, '/')) {}
    int res(gSystem->Load(name.c_str()));
    cout << name << " -> " << res << endl;
    success = success && (res >= 0);
  }

  if (success) {
    cout << "Macro finished successfully." << endl;
  }
}
