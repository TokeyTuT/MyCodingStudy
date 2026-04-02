package com.tokey.LotteryBox;

import java.util.ArrayList;
import java.util.Collections;
import java.util.concurrent.Callable;

public class MyThread2 implements Callable<ArrayList<Integer>> {

    static private ArrayList<Integer> box = new ArrayList<Integer>();

    static{
        Collections.addAll(box,1000,800,700,500,400,600,100,50,10,900);
    }

    @Override
    public ArrayList<Integer> call() throws Exception {
        ArrayList<Integer> list = new ArrayList<>();
        while(true){
            synchronized (MyThread2.class){
                if(box.isEmpty()){
                    break;
                }else{
                    Collections.shuffle(box);
                    int num = box.removeFirst();
                    list.add(num);
                }
            }
            Thread.sleep(10);
        }
        return list;
    }
}
