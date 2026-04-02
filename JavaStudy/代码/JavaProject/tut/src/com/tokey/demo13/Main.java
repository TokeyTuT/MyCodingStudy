package com.tokey.demo13;

public class Main {
    public static void main(String[] args) {
        MyThread my1 = new MyThread();
        MyThread my2 = new MyThread();

        Thread t1 = new Thread(my1);
        Thread t2 = new Thread(my2);

        t1.start();
        t2.start();
    }
}
