package com.tokey.util;

import java.util.Random;

public class CodeUtil {
    private final static char[] ch = new char[62];
    static{
        for(int i = 0;i < 26;i++){
            ch[i] = (char)(i + 'a');
        }
        for(int i = 26;i < 52;i++){
            ch[i] = (char)(i - 26 + 'A');
        }
        for(int i = 52;i < 62;i++){
            ch[i] = (char)(i - 52 + '0');
        }
    }
    public static String getCode(){
        Random r = new Random();
        StringBuilder sb = new StringBuilder();
        for(int i = 0;i < 4;i++){
            sb.append(ch[r.nextInt(62)]);
        }
        return sb.toString();
    }
}
