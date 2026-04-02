package www.tokeytut.test;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class test {
    public static void main(String[] args) {
        JFrame jf = new JFrame();
        jf.setSize(500,500);
        jf.setTitle("测试按钮");
        jf.setAlwaysOnTop(true);
        jf.setLocationRelativeTo(null);
        jf.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        jf.setLayout(null);

        JButton jb1 = new JButton("按钮 1");
        jb1.setBounds(0,0,100,100);
        //添加监听事件
        //动作监听 右键或者空格
        jb1.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                System.out.println("Buttion1 is clicked");
            }
        });

        jf.getContentPane().add(jb1);

        jf.setVisible(true);
    }
}
