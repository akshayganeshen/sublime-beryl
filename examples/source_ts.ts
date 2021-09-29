import { Writable } from "stream";
const { setTimeout } = require("timers/promises");

interface Printer {
  print(message: string): void;
}

class ConsolePrinter implements Printer {
  #stream_: Writable;

  constructor(stream: Writable) {
    this.#stream_ = stream;
  }

  print(message: string): void {
    this.#stream_.write(message);
  }
}

const isError = (err: unknown): err is Error =>
  err !== null && typeof err === "object";

const main = async (): Promise<void> => {
  try {
    const printer = new ConsolePrinter(process.stdout);
    printer.print("hello from printer\n");

    await setTimeout(1000);

    printer.print("hello again after a second\n");
  } catch (err: unknown) {
    if (isError(err)) {
      console.error(err);
    } else {
      console.log("Unknown error encountered:", err);
    }
  }
};

if (require.main === module) {
  main();
}

export default main;
export { main, ConsolePrinter };
export type { Printer };
