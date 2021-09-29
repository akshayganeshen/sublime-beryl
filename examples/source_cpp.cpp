#include <stdio.h>

#include <iostream>
#include <string>

struct message_t {
  const char *msg;
  size_t      len;
};

class Printer {
public:
  Printer(FILE *stream);
  void print(struct message_t message);

private:
  FILE *stream_;
};

Printer::Printer(FILE *stream) : stream_(stream) {}

void Printer::print(struct message_t message) {
  fprintf(stream_, "%.*s", (int)message.len, message.msg);
}

std::ostream &operator<<(std::ostream &os, const struct message_t &message) {
  std::string message_string(message.msg, message.len);
  return os << message_string;
}

static void print_on_printer() {
  Printer printer(stdout);

  struct message_t message = { .msg = "hello from printer\n", .len = 19 };
  printer.print(message);
}

static void print_on_stream() {
  struct message_t message = { .msg = "hello from stream\n", .len = 18 };
  std::cout << message;
}

int main(int argc, char const *argv[]) {
  print_on_printer();
  print_on_stream();
  return 0;
}
