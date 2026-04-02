package com.tokey.LotteryBox;

import java.util.ArrayList;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.FutureTask;

public class Main {
    public static void main(String[] args) {
        MyThread2 my1 = new MyThread2();
        MyThread2 my2 = new MyThread2();

        FutureTask ft1 = new FutureTask(my1);
        FutureTask ft2 = new FutureTask(my2);

        Thread t1 = new Thread(ft1);
        Thread t2 = new Thread(ft2);

        t1.setName("box1");
        t2.setName("box2");

        t1.start();
        t2.start();

        try {
            ArrayList<Integer> list1 = (ArrayList<Integer>) ft1.get();
            ArrayList<Integer> list2 = (ArrayList<Integer>) ft2.get();

            System.out.println("box1" + list1);
            System.out.println("box2" + list2);
        } catch (InterruptedException | ExecutionException e) {
            throw new RuntimeException(e);
        }
    }
}
