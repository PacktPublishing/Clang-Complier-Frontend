int fib(int a) {
  if (a <= 1) {
    return 1;
  }
  return fib(a - 1) + fib(a - 2);
}
