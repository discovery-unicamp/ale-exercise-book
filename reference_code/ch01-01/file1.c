extern void write(int __fd, const void *__buf, int __n);

int main(void) {
  const char str[] = "Hello World!\n";
  write(1, str, 13);
  return 0;
}
