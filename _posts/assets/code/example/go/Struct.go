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