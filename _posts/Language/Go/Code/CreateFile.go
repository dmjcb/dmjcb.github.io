/*
 * @Brief        : 
 * @Author       : dmjcb
 * @Date         : 2024-09-24 20:03:51
 * @LastEditors  : dmjcb@outlook.com
 * @LastEditTime : 2024-09-28 22:25:34
 */

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
