#include <stdio.h>
#include <math.h>

int reverse(int x)
{
  int num_of_digits = 0;
  int x_copy = x;
  do {
    x_copy /= 10;
    ++num_of_digits;
  } while (x_copy != 0);
  int divisor = pow(10, num_of_digits);
  int divisor_2 = pow(10, num_of_digits - 1);
  int digits[num_of_digits];
  int index = 0;
  int exponent = num_of_digits;

  while (divisor > 1) {
    int digit = (x % divisor - x % divisor_2)/divisor_2;
    digits[index] = digit;
    exponent--;
    divisor = pow(10, exponent);
    divisor_2 = pow(10, exponent - 1);
    index++;
  }

  for (int i = 0; i < num_of_digits / 2; i++) {
    char index_1 = i;
    char index_2 = num_of_digits - i - 1;
    char temp = digits[index_1];
    digits[index_1] = digits[index_2];
    digits[index_2] = temp;
  }

  double result;
  for (int i = 0; i < num_of_digits; i++) {
    float num = digits[i] * (pow(10, num_of_digits - 1 - i));
    printf("%d\n", num);
    result += num;
  }

  return result;
}

int main()
{
  int result = reverse(1534236469);
  printf("%i\n", result);

  return 0;
}
