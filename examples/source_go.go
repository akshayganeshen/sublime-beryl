package main

import (
	"io"
	"os"
	"sync"
)

type Printer interface {
	Print(message string)
}

type PrintWriter struct {
	io.Writer
}

func (pw PrintWriter) Print(message string) {
	_, err := pw.Writer.Write([]byte(message))
	if err != nil {
		panic(err)
	}
}

func NewPrintWriter(w io.Writer) PrintWriter {
	return PrintWriter{
		Writer: w,
	}
}

var _ Printer = PrintWriter{}

func main() {
	var wg sync.WaitGroup
	defer wg.Wait()

	wg.Add(1)
	go func() {
		defer wg.Done()
		pw := NewPrintWriter(os.Stdout)
		pw.Print("hello from goroutine 1\n")
	}()

	wg.Add(1)
	go func() {
		defer wg.Done()
		pw := NewPrintWriter(os.Stdout)
		pw.Print("hello from goroutine 2\n")
	}()
}
