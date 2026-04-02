package com.tokey.RedEnvelope;

public class RedEnvelope {
    //红包金额
    static int totalMoney = 1000;
    //红包个数
    static int  number = 3;

    //共享的锁
    static Object lock = new Object();

}
