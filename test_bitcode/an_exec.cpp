
int plus(int a, int b) { return a + b; }

int main(int argc, char *argv[]) {
  if (argc != 2) return 1;
  auto bad_stuff = reinterpret_cast<int**>(argv);
  return plus(*bad_stuff[0], *bad_stuff[1]);
}