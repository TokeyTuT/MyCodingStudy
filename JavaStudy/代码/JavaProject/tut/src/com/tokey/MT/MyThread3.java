package com.tokey.MT;

import java.util.concurrent.Callable;

public class MyThread3 implements Callable<Integer> {
    @Override
    public Integer call() throws Exception {
        return 100;
    }
}
