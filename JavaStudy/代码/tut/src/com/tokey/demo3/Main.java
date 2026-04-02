package com.tokey.demo3;

import cn.hutool.core.io.FileUtil;
import cn.hutool.core.util.ReUtil;
import cn.hutool.http.HttpUtil;

import java.util.*;

public class Main {
    public static void main(String[] args) {
        //获取姓氏
        String familyNameNet = "https://hanyu.baidu.com/shici/detail?from=aladdin&pid=0b2f26d4c0ddb3ee693fdb1137ee1b0d&smp_names=termBrand2%2Cpoem1";
        String boyNameNet = "http://www.haoming8.cn/baobao/10881.html";
        String girlNameNet = "http://www.haoming8.cn/baobao/7641.html";

        //利用 hutool 包完成爬取
        String familyName = HttpUtil.get(familyNameNet);
        String boyName = HttpUtil.get(boyNameNet);
        String girlName = HttpUtil.get(girlNameNet);
        //利用 hutool 包进行正则匹配
        List<String> familyTempListName = ReUtil.findAll("([\\u4E00-\\u9FA5]{4})(，|。)", familyName, 1);
        List<String> boyTempListName = ReUtil.findAll("([\\u4E00-\\u9FA5]{2})(、|。)", boyName, 1);
        List<String> girlTempListName = ReUtil.findAll("(.. ){4}..", girlName, 0);
        //处理爬取数据
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

        //创建随机人物 姓名-性别-年龄
        ArrayList<String> list = getInfo(familyNameList, boyNameList, girlNameList, 70, 50);
        Collections.shuffle(list);
        System.out.println(list);

        //利用 hutool 包进行写入
        FileUtil.writeLines(list,"names.txt","UTF-8");
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
}
