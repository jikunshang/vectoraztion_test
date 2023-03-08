
#include <chrono>
#include <memory>
#include <iostream>

void do_lower(char *out, const char *in, int str_len)
{
  for (int i = 0; i < str_len; ++i)
  {
    if (in[i] >= 'A' && in[i] <= 'Z')
    {
      out[i] = in[i] + 0x20;
    }
    else
    {
      out[i] = in[i];
    }
  }
}

void do_lower_hint(char *out, const char *in, int str_len)
{
#pragma clang loop vectorize(enable)
  for (int i = 0; i < str_len; ++i)
  {
    if (in[i] >= 'A' && in[i] <= 'Z')
    {
      out[i] = in[i] + 0x20;
    }
    else
    {
      out[i] = in[i];
    }
  }
}

int main()
{

  int loop_count = 100000;
  int str_len = 100;
  char *in = (char *)std::malloc(str_len);
  for (int i = 0; i < 25; i++)
  {
    in[i] = 'a' + (char)i;
    in[i + 50] = 'a' + (char)i;
    in[i + 25] = 'A' + (char)i;
    in[i + 75] = 'A' + (char)i;
  }
  char *out = (char *)std::malloc(str_len);

  {
    auto start = std::chrono::system_clock::now();
    for (int i = 0; i < loop_count; i++)
    {
      do_lower_hint(out, in, str_len);
    }
    auto duration = (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start)).count();
    std::cout << "ramp up duration: " << duration << " ms" << std::endl;
  }

  {
    auto start = std::chrono::system_clock::now();
    for (int i = 0; i < loop_count; i++)
    {
      do_lower_hint(out, in, str_len);
    }
    auto duration = (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start)).count();
    std::cout << "do_lower_hint(W/ hint) duration: " << duration << " ms" << std::endl;
  }

  {
    auto start = std::chrono::system_clock::now();
    for (int i = 0; i < loop_count; i++)
    {
      do_lower(out, in, str_len);
    }
    auto duration = (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start)).count();
    std::cout << "do_lower(Wo/ hint) duration: " << duration << " ms" << std::endl;
  }

  return 0;
}
