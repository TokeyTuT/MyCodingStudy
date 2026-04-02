package com.tokey.MT;

import java.util.concurrent.ExecutionException;
import java.util.concurrent.FutureTask;

public class test3 {
    public static void main(String[] args) throws ExecutionException, InterruptedException {
        MyThread3 myThread3 = new MyThread3();
        FutureTask<Integer> ft = new FutureTask<>(myThread3);
        Thread t = new Thread(ft);
        t.start();
        Integer res = ft.get();
        System.out.println(res);
    }
}
