package com.tokey.demo2;

import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLConnection;
import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Main {
    public static void main(String[] args) throws IOException {
        //获取姓氏
        String familyNameNet = "https://hanyu.baidu.com/shici/detail?from=aladdin&pid=0b2f26d4c0ddb3ee693fdb1137ee1b0d&smp_names=termBrand2%2Cpoem1";
        String boyNameNet = "http://www.haoming8.cn/baobao/10881.html";
        String girlNameNet = "http://www.haoming8.cn/baobao/7641.html";

        //爬取
        String familyName = webCrawler(familyNameNet);
        String boyName = webCrawler(boyNameNet);
        String girlName = webCrawler(girlNameNet);
        //^[\u4E00-\u9FA5]+$/
        ArrayList<String> familyTempListName = getName(familyName, "([\\u4E00-\\u9FA5]{4})(，|。)", 1);
        ArrayList<String> boyTempListName = getName(boyName, "([\\u4E00-\\u9FA5]{2})(、|。)", 1);
        ArrayList<String> girlTempListName = getName(girlName, "(.. ){4}..", 0);

        ArrayList<String> familyNameList = new ArrayList<>();
        ArrayList<String> boyNameList = new ArrayList<>();
        ArrayList<String> girlNameList = new ArrayList<>();

        for (String s : familyTempListName) {
            for (int i = 0; i < s.length(); i++) {
                familyNameList.add(s.charAt(i) + "");
            }
        }

        for (String s : boyTempListName) {
            if(boyNameList.contains(s)){
                continue;
            }else{
                boyNameList.add(s);
            }
        }

        for (String s : girlTempListName) {
            String[] split = s.split(" ");
            girlNameList.addAll(Arrays.asList(split));
        }

        ArrayList<String> list = getInfo(familyNameList, boyNameList, girlNameList, 70, 50);
        Collections.shuffle(list);
        System.out.println(list);


    }
    private static ArrayList<String> getInfo(ArrayList<String> familyNameList, ArrayList<String> boyNameList, ArrayList<String> girlNameList, int boycnt, int girlcnt){
        ArrayList<String> list = new ArrayList<>();
        HashSet<String> boyhs = new HashSet<>();
        HashSet<String> girlhs = new HashSet<>();

        while(boyhs.size() < boycnt){
            Collections.shuffle(familyNameList);
            Collections.shuffle(boyNameList);
            String newName = familyNameList.getFirst() + boyNameList.getLast();
            boyhs.add(newName);
        }
        while(girlhs.size() < girlcnt){
            Collections.shuffle(familyNameList);
            Collections.shuffle(girlNameList);
            String newName = familyNameList.getFirst() + girlNameList.getLast();
            girlhs.add(newName);
        }

        //设置年龄与性别
        Random r = new Random();
        for (String boy : boyhs) {
            list.add(boy + "-男-" + (r.nextInt(10) + 18));
        }
        for (String girl : girlhs) {
            list.add(girl + "-女-" + (r.nextInt(8) + 18));
        }

        return list;
    }
    private static ArrayList<String> getName(String name,String regex,int index){
        ArrayList<String> arr = new ArrayList<>();
        Pattern p = Pattern.compile(regex);
        Matcher matcher = p.matcher(name);
        while(matcher.find()){
            arr.add(matcher.group(index));
        }
        return arr;
    }
    private static String webCrawler(String name) throws IOException {
        URL url = new URL(name);
        //将 url 链接到这个网址
        URLConnection uconn = url.openConnection();//字节输入流
        //将字节输入流转换为字符输入流
        InputStreamReader isr = new InputStreamReader(uconn.getInputStream());
        //获取内容
        StringBuilder sb = new StringBuilder();
        int ch;
        while((ch = isr.read()) != -1){
            sb.append((char)ch);
        }
        isr.close();
        return sb.toString();
    }
}
