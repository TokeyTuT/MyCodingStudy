package com.tokey.MT;

public class MyThread4 extends Thread {
    public MyThread4() {
    }

    public MyThread4(String name) {
        super(name);
    }

    @Override
    public void run() {
        for (int i = 0; i < 10; i++) {
            System.out.println(this.getName() + " is running");
        }
    }
}
