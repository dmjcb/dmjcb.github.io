/*
 * @Brief        : 
 * @Author       : dmjcb
 * @Date         : 2024-09-24 20:03:51
 * @LastEditors  : dmjcb@outlook.com
 * @LastEditTime : 2024-09-28 22:25:53
 */

package main

import "fmt"

type Student struct {
    id int
    name string
    school string
}

func main() {
    stu := new(Student)

    stu.id = 1000
    stu.name = "wang"
    stu.school = "MIT"

    fmt.Println(stu)
}