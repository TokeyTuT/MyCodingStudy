package com.tokey.demo10;

public class SharedData {
    //一共要吃多少碗面
    static int count = 10;
    //是否还有面 —— 0 代表没了、1代表有一碗面
    static int isOver = 0;
    //共享的锁
    final static Object lock = new Object();
}
