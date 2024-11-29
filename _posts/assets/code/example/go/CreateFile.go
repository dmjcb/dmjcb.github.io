package main

import (
    "log"
    "os"
)

func main() {
    f, err := os.Create("test.txt")

    defer f.Close()

    if err != nil {
        log.Fatal(err)
    }

    log.Println(f)
}
