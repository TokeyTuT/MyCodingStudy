package com.tokey.demo8;

public class test1 {
    public static void main(String[] args) {
        MyThread my1 = new MyThread();
        MyThread my2 = new MyThread();
        MyThread my3 = new MyThread();

        Thread t1 = new Thread(my1);
        Thread t2 = new Thread(my2);
        Thread t3 = new Thread(my3);


        t1.start();
        t2.start();
        t3.start();
    }
}
