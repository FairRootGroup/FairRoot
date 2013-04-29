class  X
{
 public:
  int i_;
  X(int i) : i_(i) {}
  X() : X(42) {}
};

int main(void)
{
  X val;
  return (val.i_-42) ? 1 : 0;
}