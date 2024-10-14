/*
 * @Brief        : 
 * @Author       : dmjcb
 * @Date         : 2024-09-24 20:03:51
 * @LastEditors  : dmjcb@outlook.com
 * @LastEditTime : 2024-09-28 22:25:34
 */

package main

import (
    "fmt"
    "os"
)

func main() {
    for i := 1; i < len(os.Args); i++ {
        fmt.Println(os.Args[i])
    }
}
