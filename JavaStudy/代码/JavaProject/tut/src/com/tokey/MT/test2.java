package com.tokey.MT;

public class test2 {
    public static void main(String[] args) {
        MyThread2 my = new MyThread2();
        Thread t1 = new Thread(my);
        Thread t2 = new Thread(my);

        t1.setName("Thread1");
        t2.setName("Thread2");

        t1.start();
        t2.start();
    }

}
