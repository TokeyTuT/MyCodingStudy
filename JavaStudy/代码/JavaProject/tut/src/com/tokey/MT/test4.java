package com.tokey.MT;

public class test4 {
    public static void main(String[] args) {
        MyThread my1 = new MyThread("dapao");
        MyThread my2 = new MyThread("feiji");

        Thread t1 = new Thread(my1);
        Thread t2 = new Thread(my2);

        t1.setPriority(Thread.MAX_PRIORITY);
        t2.setPriority(Thread.MIN_PRIORITY);

        t1.start();
        t2.start();
    }
}
