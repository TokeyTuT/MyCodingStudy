package com.tokey.demo1;
import java.io.*;
import java.util.*;
import java.util.zip.ZipEntry;
import java.util.zip.ZipOutputStream;

public class Main {
    public static void main(String[] args) throws IOException, ClassNotFoundException {
        File src = new File("/Users/tuttokey/aaa");
        File parent = src.getParentFile();
        File dest = new File(parent,"aaa.zip");
        ZipOutputStream zop = new ZipOutputStream(new FileOutputStream(dest));
        toZip(zop,src,src.getName());

    }
    public static void toZip(ZipOutputStream zop,File src,String name) throws IOException {
        File[] files = src.listFiles();
        if(files == null){
            return;
        }
        for (File file : files) {
            if(file.isFile()){
                ZipEntry entry = new ZipEntry(name + "/" + file.getName());
                zop.putNextEntry(entry);
                FileInputStream fis = new FileInputStream(file);
                byte[] bytes = new byte[1024];
                int len;
                while((len = fis.read(bytes))!=-1){
                    zop.write(bytes,0,len);
                }
                zop.closeEntry();
            }else{
                toZip(zop,file,name + "/" + file.getName());
            }
        }
    }

}