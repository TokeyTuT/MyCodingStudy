package com.tokey.MT;

public class test5 {
    public static void main(String[] args) {
        MyThread myThread = new MyThread("Thread1");
        MyThread4 myThread4 = new MyThread4("Thread2");
        Thread t1 = new Thread(myThread);
        Thread t2 = new Thread(myThread4);

        t1.setDaemon(true);
        t1.start();
        t2.start();
    }
}
